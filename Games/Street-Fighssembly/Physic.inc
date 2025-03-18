; --------------------------------------------------
; Physic handling.
; Applies gravity and velocity for the players.
; --------------------------------------------------

section .data
    GRAVITY equ  2

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
    applyGravity:
        ; --------------
        ; first player
        cmp byte [jumping_1], 0
        je .fall1
        cmp word [y_velocity_1], 0
        jle .fall1  ; if jumping and still going up, apply jump physic
        ; apply jump physic
        mov cx, [y_pos_1]
        sub cx, [y_velocity_1]                  
        mov word [y_pos_1], cx
        sub word [y_velocity_1], GRAVITY
        jmp .endApplyGravityPlayer1

        .fall1:
            mov ax, [y_pos_1]
            add ax, SPRITE_HEIGHT
            cmp ax, WINDOW_DOWN_BORDER ; verify if the player isn't out of border or on the border, if yes :
            jg .repositionPlayer1                                                                 ;     - reposition the player
            je .endApplyGravityPlayer1                                                            ;     - skip the gravity
            ; apply fall physic
            mov cx, [y_pos_1]
            add cx, [y_velocity_1]
            mov word [y_pos_1], cx
            add word [y_velocity_1], GRAVITY
            mov byte [jumping_1], 0
            jmp .endApplyGravityPlayer1

        .repositionPlayer1: ; reposition the player 
            mov word [y_pos_1], WINDOW_DOWN_BORDER - SPRITE_HEIGHT
            mov byte [jumping_1], 0
        .endApplyGravityPlayer1:
        
        ; --------------
        ; second player
        cmp byte [jumping_2], 0
        je .fall2
        cmp word [y_velocity_2], 0
        jle .fall2  ; if jumping and still going up, apply jump physic
        ; apply jump physic
        mov cx, [y_pos_2]
        sub cx, [y_velocity_2]                  
        mov word [y_pos_2], cx
        sub word [y_velocity_2], GRAVITY
        jmp .endApplyGravityPlayer2

        .fall2:
            mov ax, [y_pos_2]
            add ax, SPRITE_HEIGHT
            cmp ax, WINDOW_DOWN_BORDER ; verify if the player isn't out of border or on the border, if yes :
            jg .repositionPlayer2                                                                 ;     - reposition the player
            je .endApplyGravityPlayer2                                                            ;     - skip the GRAVITY
            ; apply fall physic
            mov cx, [y_pos_2]
            add cx, [y_velocity_2]
            mov word [y_pos_2], cx
            add word [y_velocity_2], GRAVITY
            mov byte [jumping_2], 0
            jmp .endApplyGravityPlayer2

        .repositionPlayer2: ; reposition the player 
            mov word [y_pos_2], WINDOW_DOWN_BORDER - SPRITE_HEIGHT
            mov byte [jumping_2], 0
        .endApplyGravityPlayer2:
        ret
        