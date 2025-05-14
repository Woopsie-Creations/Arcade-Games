%macro addDigitWithoutOverflow 1
    %%checking:
    cmp byte [%1+bx], 9
    jne %%skip
    mov byte [%1+bx], 0
    dec bx
    ; recheck the overflow to be sure
    cmp byte [%1+bx], 9
    je %%checking
    %%skip: 
    ; update
    inc byte [%1+bx] 
%endmacro

%macro addToScore 1
    ; increment number in ax
    ; if number too big (10,000 or more):
    ;   - dx = ten thousand digits and more
    ; else dx must be = 0
    mov ax, %1

    %%start:
    cmp dx, 0
    je %%noDx
    cmp dx, 100
    jae %%millions
    cmp dx, 10
    jae %%hundredthousands
    cmp dx, 1
    jae %%tenthousands
    
    %%noDx:
    cmp ax, 0
    je %%end
    cmp ax, 1000
    jae %%thousands
    cmp ax, 100
    jae %%hundreds
    cmp ax, 10
    jae %%tens

    %%millions:
        mov bx, 0
        addDigitWithoutOverflow current_score
        sub dx, 100
        jmp %%start

    %%hundredthousands:
        mov bx, 1
        addDigitWithoutOverflow current_score
        sub dx, 10
        jmp %%start

    %%tenthousands:
        mov bx, 2
        addDigitWithoutOverflow current_score
        sub dx, 1
        jmp %%start

    %%thousands:
        mov bx, 3
        addDigitWithoutOverflow current_score
        sub ax, 1000
        jmp %%start

    %%hundreds:
        mov bx, 4
        addDigitWithoutOverflow current_score
        sub ax, 100
        jmp %%start

    %%tens:
        mov bx, 5
        addDigitWithoutOverflow current_score
        sub ax, 10
        jmp %%start
    %%end:
        xor cx, cx
%endmacro

section .data
    level db 0,0,1

section .bss
    current_score resb 7

section .text
    updateDisplayedScore:
        xor dx, dx ; current_score' count (7)
        xor cx, cx ; displayedNumbers' count (7 + 2 dots)
        ; addToScore 10 ; testing purpose
        .loop:
            cmp cx, 9
            jge .done
            cmp cx, 1
            je .insertDot
            cmp cx, 5
            je .insertDot

            mov bx, dx ; get current_score' count
            
            movzx ax, byte [current_score + bx] ; get the number
            shl ax, 1
            mov bx, ax
            mov ax, [displayNumbersFont + bx] ; use the number as an index to get sprite
            mov bx, cx
            shl bx, 1
            mov [displayedNumbers + bx], ax ; put the sprite

            inc cx
            inc dx
            jmp .loop

        .insertDot: ; when needed, insert a `.` instead of a number
            mov bx, cx ; get displayedNumbers' count

            mov ax, fontDot
            shl bx, 1
            mov [displayedNumbers + bx], ax

            inc cx
            jmp .loop
        .done:
            ret

    increaseLevel:
        mov bx, 2
        addDigitWithoutOverflow level
        inc byte [current_fruit_case_index]
        ret

    updateDisplayedLevel:
        xor cx, cx ; displayedLevel' count (3)
        mov bx, 2
        ; addDigitWithoutOverflow level ; testing purpose
        .loop:
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
            jmp .loop
        .done:
            ret
