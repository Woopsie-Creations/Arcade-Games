; --------------------------------------------------
; Physic handling.
; Applies gravity and velocity for the players.
; --------------------------------------------------

section .data
    gravity db 2

section .bss
    ; the .bss section will create uninitialized data
    ; - we only reserve the amount of data of a variable we could attribute it (resb = reserve byte, resw = reserve word)
    ; - 0 is attributed to those variables as soon as the program runs
    jumping_1: resb 1
    x_velocity_1: resw 1
    y_velocity_1: resw 1

    jumping_2: resb 1
    x_velocity_2: resw 1
    y_velocity_2: resw 1

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
        setPixelPosition [x_pos_2], [y_pos_2]
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
            setPixelPosition [x_pos_2], [y_pos_2]
            setPixelPosition [x_pos_1], [y_pos_1]
            jmp .endApplyGravityPlayer1

        .repositionPlayer1: ; reposition the player 
            clearOldPosition [x_pos_1], [y_pos_1]
            mov word [y_pos_1], WINDOW_DOWN_BORDER - SPRITE_HEIGHT
            mov byte [jumping_1], 0
            setPixelPosition [x_pos_2], [y_pos_2]
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
        setPixelPosition [x_pos_1], [y_pos_1]
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
            setPixelPosition [x_pos_1], [y_pos_1]
            setPixelPosition [x_pos_2], [y_pos_2]
            jmp .endApplyGravityPlayer2

        .repositionPlayer2: ; reposition the player 
            clearOldPosition [x_pos_2], [y_pos_2]
            mov word [y_pos_2], WINDOW_DOWN_BORDER - SPRITE_HEIGHT
            mov byte [jumping_2], 0
            setPixelPosition [x_pos_1], [y_pos_1]
            setPixelPosition [x_pos_2], [y_pos_2]
        .endApplyGravityPlayer2:
        ret
        