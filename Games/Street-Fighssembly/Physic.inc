; --------------------------------------------------
; Physic handling.
; Applies gravity and velocity for the players.
; --------------------------------------------------

section .data
    gravity db 1

    jumping_1 db 0
    jumping_2 db 0
    x_velocity_1 dw 0
    y_velocity_1 dw 0

    x_velocity_2 dw 0
    y_velocity_2 dw 0

    %define JUMP_HEIGHT 50

section .text 
    applyGravity:
        xor ax, ax 

        ; gravity for player 1
        clearOldPosition [x_pos_1], [y_pos_1]
        mov ax, [gravity]
        cmp byte [jumping_1], 1
        jne .fall1 ; if jumping, apply jump velocity. if not, jump to fall velocity
        cmp word [y_velocity_1], 0
        jle .fall1 
        jmp .jumpLoop1 ; if the player's jumping and his velocity > 0, then he jumps
        ; gravity for player 2
        clearOldPosition [x_pos_2], [y_pos_2]
        mov ax, [gravity]
        cmp byte [jumping_2], 1
        jne .fall2 ; if jumping, apply jump velocity. if not, jump to fall velocity
        cmp word [y_velocity_2], 0
        jle .fall2 
        jmp .jumpLoop2 ; if the player's jumping and his velocity > 0, then he jumps
        
        .fall1: ; falling
        cmp word [y_pos_1], WINDOW_DOWN_BORDER ; can gravity be applied ?
        jg .repositionPlayer1
        je .skipApplyGravityPlayer1
        mov byte [jumping_1], 0
        add word [y_velocity_1], ax
        mov ax, [y_velocity_1]
        add word [y_pos_1], ax
        jmp .skipApplyGravityPlayer1
        .fall2: ; falling
        cmp word [y_pos_2], WINDOW_DOWN_BORDER ; can gravity be applied ?
        jg .repositionPlayer2
        je .skipApplyGravityPlayer2
        mov byte [jumping_2], 0
        add word [y_velocity_2], ax
        mov ax, [y_velocity_2]
        add word [y_pos_2], ax
        jmp .skipApplyGravityPlayer2
        
        .repositionPlayer1: ; avoid player going outside of the box (I don't like overflow :))
            clearOldPosition [x_pos_1], [y_pos_1]
            mov word [y_pos_1], WINDOW_DOWN_BORDER
        .repositionPlayer2: ; avoid player going outside of the box (I don't like overflow :))
            clearOldPosition [x_pos_2], [y_pos_2]
            mov word [y_pos_2], WINDOW_DOWN_BORDER

        .jumpLoop1:
            ; checks if the player is at his jump peak
            ; - if yes, he ain't jumping anymore
            ; - if no, his y_pos decreases
            cmp word [y_velocity_1], JUMP_HEIGHT
            jge .jmpReset1
            mov ax, [y_velocity_1]
            sub word [y_pos_1], ax
            add word [y_velocity_1], 10
            jmp .skipApplyGravityPlayer1
        .jumpLoop2:
            ; checks if the player is at his jump peak
            ; - if yes, he ain't jumping anymore
            ; - if no, his y_pos decreases
            cmp word [y_velocity_2], JUMP_HEIGHT
            jge .jmpReset2
            mov ax, [y_velocity_2]
            sub word [y_pos_2], ax
            add word [y_velocity_2], 10
            jmp .skipApplyGravityPlayer2

        .jmpReset1:
            ; resets the jump variable to apply gravity
            mov byte [jumping_1], 0
            jmp .skipApplyGravityPlayer1
        .jmpReset2:
            ; resets the jump variable to apply gravity
            mov byte [jumping_2], 0
            jmp .skipApplyGravityPlayer2

        .skipApplyGravityPlayer1:
            setPixelPosition [x_pos_1], [y_pos_1], [color_1]
        .skipApplyGravityPlayer2:
            setPixelPosition [x_pos_2], [y_pos_2], [color_2]
        
        ret