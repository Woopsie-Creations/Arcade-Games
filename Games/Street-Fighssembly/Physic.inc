; --------------------------------------------------
; Physic handling.
; Applies gravity and velocity for the players.
; --------------------------------------------------

section .data
    gravity db 2

    jumping_1 db 0
    x_velocity_1 dw 0
    y_velocity_1 dw 0

    jumping_2 db 0
    x_velocity_2 dw 0
    y_velocity_2 dw 0

section .text 
    applyGravity1:
        xor ax, ax

        cmp byte [jumping_1], 0
        je .fall1
        cmp word [y_velocity_1], 0
        jle .fall1  ; if jumping and still going up, apply jump physic
        ; apply jump physic
        clearOldPosition [x_pos_1], [y_pos_1]   
        mov ax, [gravity]
        mov cx, [y_pos_1]
        sub cx, [y_velocity_1]                  
        mov word [y_pos_1], cx
        sub word [y_velocity_1], ax
        setPixelPosition [x_pos_1], [y_pos_1]
        jmp .endApplyGravityPlayer1

        .fall1:
            mov ax, [y_pos_1]
            add ax, SPRITE_HEIGHT
            cmp ax, WINDOW_DOWN_BORDER ; verify if the player isn't out of border or on the border, if yes :
            jg .repositionPlayer1                                                                 ;     - reposition the player
            je .endApplyGravityPlayer1                                                            ;     - skip the gravity
            ; apply fall physic
            clearOldPosition [x_pos_1], [y_pos_1]
            mov ax, [gravity]
            mov cx, [y_pos_1]
            add cx, [y_velocity_1]
            mov word [y_pos_1], cx
            add word [y_velocity_1], ax
            mov byte [jumping_1], 0
            setPixelPosition [x_pos_1], [y_pos_1]
            jmp .endApplyGravityPlayer1

        .repositionPlayer1: ; reposition the player 
            clearOldPosition [x_pos_1], [y_pos_1]
            mov word [y_pos_1], WINDOW_DOWN_BORDER - SPRITE_HEIGHT
            mov byte [jumping_1], 0
            setPixelPosition [x_pos_1], [y_pos_1]
        .endApplyGravityPlayer1:
        ret

    applyGravity2:
        xor ax, ax

        cmp byte [jumping_2], 0
        je .fall2
        cmp word [y_velocity_2], 0
        jle .fall2  ; if jumping and still going up, apply jump physic
        ; apply jump physic
        clearOldPosition [x_pos_2], [y_pos_2]   
        mov ax, [gravity]
        mov cx, [y_pos_2]
        sub cx, [y_velocity_2]                  
        mov word [y_pos_2], cx
        sub word [y_velocity_2], ax
        setPixelPosition [x_pos_2], [y_pos_2]
        jmp .endApplyGravityPlayer2

        .fall2:
            mov ax, [y_pos_2]
            add ax, SPRITE_HEIGHT
            cmp ax, WINDOW_DOWN_BORDER ; verify if the player isn't out of border or on the border, if yes :
            jg .repositionPlayer2                                                                 ;     - reposition the player
            je .endApplyGravityPlayer2                                                            ;     - skip the gravity
            ; apply fall physic
            clearOldPosition [x_pos_2], [y_pos_2]
            mov ax, [gravity]
            mov cx, [y_pos_2]
            add cx, [y_velocity_2]
            mov word [y_pos_2], cx
            add word [y_velocity_2], ax
            mov byte [jumping_2], 0
            setPixelPosition [x_pos_2], [y_pos_2]
            jmp .endApplyGravityPlayer2

        .repositionPlayer2: ; reposition the player 
            clearOldPosition [x_pos_2], [y_pos_2]
            mov word [y_pos_2], WINDOW_DOWN_BORDER - SPRITE_HEIGHT
            mov byte [jumping_2], 0
            setPixelPosition [x_pos_2], [y_pos_2]
        .endApplyGravityPlayer2:
        ret
        