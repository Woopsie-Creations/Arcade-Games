; --------------------------------------------------
; Physic handling.
; Applies gravity and velocity for the players.
; --------------------------------------------------

section .data
    gravity db 1

    jumping_1 db 0
    x_velocity_1 dw 0
    y_velocity_1 dw 0

    x_velocity_2 dw 0
    y_velocity_2 dw 0

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
        sub word [y_velocity_1], ax
        mov ax, [y_velocity_1]
        sub word [y_pos_1], ax
        jmp .skipApplyGravityPlayer1
        
        .fall1: ; falling
        cmp word [y_pos_1], WINDOW_DOWN_BORDER ; can gravity be applied ?
        jg .repositionPlayer1
        je .skipApplyGravityPlayer1
        mov byte [jumping_1], 0
        add word [y_velocity_1], ax
        mov ax, [y_velocity_1]
        add word [y_pos_1], ax
        jmp .skipApplyGravityPlayer1
        
        .repositionPlayer1: ; avoid player going outside of the box (I don't like overflow :))
        clearOldPosition [x_pos_1], [y_pos_1]
        mov word [y_pos_1], WINDOW_DOWN_BORDER
        .skipApplyGravityPlayer1:
        setPixelPosition [x_pos_1], [y_pos_1], [color_1]
        
        ret