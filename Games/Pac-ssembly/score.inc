%macro addDigitWithoutOverflow 2
    %%checking:
    cmp byte [%1+bx], 9
    jne %%skip
    mov byte [%1+bx], 0
    dec bx
    ; recheck the overflow to be sure
    jmp %%checking
    %%skip: 
    ; update
    inc byte [%1+bx]
    sub ax, %2
%endmacro

%macro addToScore 5
    ; increment number in ax
    mov ax, %2
    %%start:
    cmp ax, 0
    je %%end
    cmp ax, 1000
    jae %%thousands
    cmp ax, 100
    jae %%hundreds
    cmp ax, 10
    jae %%tens

    %%thousands:
        mov bx, %3
        addDigitWithoutOverflow %1, 1000
        jmp %%start

    %%hundreds:
        mov bx, %4
        addDigitWithoutOverflow %1, 100
        jmp %%start

    %%tens:
        mov bx, %5
        addDigitWithoutOverflow %1, 10
        jmp %%start
    %%end:
%endmacro

%macro checkSpawnFruit 1
    cmp byte [maze_remaining_gums], MAZE_AMOUNT_OF_GUMS-%1
    jne %%skip
    mov byte [fruit_should_be_displayed], TRUE
    init_timer 5, time_start_fruit, interval_ticks_fruit, expected_time_fruit, [has_init_timer_fruit]
    %%skip:
%endmacro

%macro updateDisplayedScore 4
    xor dx, dx ; score' count (7)
    xor cx, cx ; displayedNumbers' count (7 + 2 dots)
    %%loop:
        cmp cx, %3
        jge %%done
        mov bx, TRUE
        cmp bx, %4
        je %%noNeedDot
        cmp cx, 1
        je %%insertDot
        cmp cx, 5
        je %%insertDot

        %%noNeedDot:

        mov bx, dx ; get high_score' count
        
        movzx ax, byte [%1 + bx] ; get the number
        shl ax, 1
        mov bx, ax
        mov ax, [displayNumbersFont + bx] ; use the number as an index to get sprite
        mov bx, cx
        shl bx, 1
        mov [%2 + bx], ax ; put the sprite

        inc cx
        inc dx
        jmp %%loop

    %%insertDot: ; when needed, insert a `.` instead of a number
        mov bx, cx ; get displayedNumbers' count

        mov ax, fontDot
        shl bx, 1
        mov [%2 + bx], ax

        inc cx
        jmp %%loop
    %%done:
%endmacro

%macro ascii_to_digits 1
    mov si, %1
    mov cx, 7
    .to_digit_loop:
        mov al, [si]
        sub al, '0'
        mov [si], al
        inc si
        loop .to_digit_loop
%endmacro

%macro digits_to_ascii 1
    mov si, %1
    mov cx, 7
    .to_ascii_loop:
        mov al, [si]
        add al, '0'
        mov [si], al
        inc si
        loop .to_ascii_loop
%endmacro

section .data
    level db 0,0,1
    fruit_spawn_table:
                db 0      ; Offset of 1 (cannot be level 0), default cherry
                db 0      ; Level 1 - Cherry
                db 1      ; Level 2 - Strawberry
                db 2      ; Level 3 - Orange
                db 2      ; Level 4 - Orange
                db 3      ; Level 5 - Apple
                db 3      ; Level 6 - Apple
                db 4      ; Level 7 - Melon
                db 4      ; Level 8 - Melon
                db 5      ; Level 9 - Galaxian
                db 5      ; Level 10 - Galaxian
                db 6      ; Level 11 - Bell
                db 6      ; Level 12 - Bell
                db 7      ; Level 13 - Key

    fruit_score_table:
                dw 100      ; Cherry
                dw 300      ; Strawberry
                dw 500      ; Orange
                dw 700      ; Apple
                dw 1000     ; Melon
                dw 2000     ; Galaxian
                dw 3000     ; Bell
                dw 5000     ; Key

    high_score_file db "hscore.bin", 0

section .bss
    current_score resb 7
    high_score resb 7
    hscore_file_handle resw 1

section .text
    increaseLevel:
        mov bx, 2
        addDigitWithoutOverflow level, 0
        ; update fruit to spawn
        mov bx, [level+2]
        cmp byte [level+0], 1
        jge .isKey
        cmp byte [level+1], 1
        jg .isKey
        je .moreThanTen
        mov bx, [fruit_spawn_table+bx]
        jmp .end
        .moreThanTen:
            cmp bx, 3
            jge .isKey
            add bx, 10
            mov bx, [fruit_spawn_table+bx]
            jmp .end
        .isKey:
            mov bx, 7 ; default if > 13: key
        .end:
            mov [current_fruit_case_index], bx
            mov byte [fruits_eaten], 0      
            ret

    updateDisplayedLevel:
        xor cx, cx ; displayedLevel' count (3)
        mov bx, 2
        .eachLevelDigit:
            cmp cx, 3
            jge .done

            mov bx, cx ; get level' count
            movzx ax, byte [level + bx] ; get the number
            shl ax, 1
            mov bx, ax
            mov ax, [displayNumbersFont + bx] ; use the number as an index to get sprite
            mov bx, cx
            shl bx, 1
            mov [displayedLevel + bx], ax ; put the sprite

            inc cx
            jmp .eachLevelDigit
        .done:
            ret
    events:
        ; gums
        cmp byte [maze_remaining_gums], 0
        je goToNextLevel
        cmp byte [got_a_bonus_life], TRUE
        je .checkForFruits
        cmp byte [current_score+2], 1
        jne .checkForFruits
        mov byte [got_a_bonus_life], TRUE
        inc byte [pacman_lives]
        .checkForFruits:
        ; fruits
        cmp byte [has_init_timer_fruit], TRUE
        je .checkForFruitTimer

        .checkForSpawn:
        cmp byte [fruits_eaten], 2
        jl .checkFruit
        mov byte [fruit_should_be_displayed], FALSE
        jmp .checkFrightMode

        .checkFruit:
            cmp byte [fruits_eaten], 1
            jl .checkFruit1
            checkSpawnFruit 170
            jmp .checkFrightMode
            .checkFruit1:
            checkSpawnFruit 70
            jmp .checkFrightMode
        
        .checkForFruitTimer:
            checkTimer current_time_fruit, expected_time_fruit, eraseFruit, [has_init_timer_fruit]
            ret
        .checkFrightMode:
            call checkForFrightMode
            ret

    resetDynamicScore:
        mov word [expected_time_score], -1
        mov byte [dynamic_score_amount], 0
        mov byte [dynamic_score_amount+1], 0
        mov byte [dynamic_score_amount+2], 0
        mov byte [dynamic_score_amount+3], 0
        ret
    
    eraseFruit:
        inc byte [fruits_eaten]
        mov byte [fruit_should_be_displayed], FALSE
        mov byte [has_init_timer_fruit], FALSE
        ret

%include "highscore.inc"