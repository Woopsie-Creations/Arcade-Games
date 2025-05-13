section .bss
    current_score resb 7

section .text
    updateDisplayedScore:
        xor dx, dx ; current_score' count (7)
        xor cx, cx ; displayedNumbers' count (7 + 2 dots)
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
