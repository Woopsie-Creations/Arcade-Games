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
        mov cx, 100
        mov ax, dx
        call checkScoreDigitOverflow
        mov dx, ax
        jmp %%start

    %%hundredthousands:
        mov bx, 1
        mov cx, 10
        mov ax, dx
        call checkScoreDigitOverflow
        mov dx, ax
        jmp %%start

    %%tenthousands:
        mov bx, 2
        mov cx, 1
        mov ax, dx
        call checkScoreDigitOverflow
        mov dx, ax
        jmp %%start

    %%thousands:
        mov bx, 3
        mov cx, 1000
        call checkScoreDigitOverflow
        jmp %%start

    %%hundreds:
        mov bx, 4
        mov cx, 100
        call checkScoreDigitOverflow
        jmp %%start

    %%tens:
        mov bx, 5
        mov cx, 10
        call checkScoreDigitOverflow
        jmp %%start
    %%end:
        xor cx, cx
%endmacro

section .data
    level db 1

section .bss
    current_score resb 7

section .text
    checkScoreDigitOverflow:
        cmp byte [current_score+bx], 9
        jne .skip
        mov byte [current_score+bx], 0
        dec bx
        ; recheck the overflow to be sure
        cmp byte [current_score+bx], 9
        je checkScoreDigitOverflow
        .skip: 
        ; update
        inc byte [current_score+bx]
        sub ax, cx
        ret

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
