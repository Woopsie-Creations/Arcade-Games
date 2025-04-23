section .data
    ; Sprite files (paths)
    ryuIdle0 db "Sprites/Idle0.bin", 0
    ryuIdleLeft0 db "Sprites/LIdle0.bin", 0

    ryuJump5 db "Sprites/Jump5.bin", 0
    ryuJumpLeft5 db "Sprites/LJump5.bin", 0
    ryuFall5 db "Sprites/Jump5.bin", 0
    ryuFallLeft5 db "Sprites/LJump5.bin", 0

    ryuCrouch db "Sprites/Crouch.bin", 0
    ryuCrouchLeft db "Sprites/LCrouch.bin", 0

section .bss
    ; For both players
    player_current_sprite1: resw 1
    player_current_sprite2: resw 1

section .text
    animatePlayers:
        call animatePlayer2
        call animatePlayer1

        jmp gameLoop

    animatePlayer1:
        ; Should be left sprite?
        mov ax, [x_pos_1]
        mov bx, [x_pos_2]
        cmp ax, bx
        jg .left

        ; In air
        mov ax, [y_pos_1]
        add ax, SPRITE_HEIGHT
        cmp ax, WINDOW_DOWN_BORDER
        jl .midair

        ; Grounded
        ; TO-DO: add special grounded animations conditions here

        ; Default: idle
        mov word [player_current_sprite1], ryuIdle0
        ret

        .midair:
            ; TO-DO: add special midair animations conditions here
            mov ax, [jumping_1]
            cmp ax, 1
            je .jumping

            ; Default: fall
            mov word [player_current_sprite1], ryuFall5
            ret
        .jumping:
            mov word [player_current_sprite1], ryuJump5
            ret
        .crouch:
            ; Default crouch:
            mov word [player_current_sprite1], ryuCrouch
            ret
            
        .left:
            ; In air
            mov ax, [y_pos_1]
            add ax, SPRITE_HEIGHT
            cmp ax, WINDOW_DOWN_BORDER
            jl .leftMidair

            ; Grounded
            ; TO-DO: add special grounded animations conditions here

            ; Default: idle
            mov word [player_current_sprite1], ryuIdleLeft0
            ret
        .leftMidair:
            ; TO-DO: add special midair animations conditions here
            mov ax, [jumping_1]
            cmp ax, 1
            je .leftJumping

            ; Default: fall
            mov word [player_current_sprite1], ryuFallLeft5
            ret
        .leftJumping:
            mov word [player_current_sprite1], ryuJumpLeft5
            ret
        .leftCrouch:
            ; Default crouch
            mov word [player_current_sprite1], ryuCrouchLeft
            ret
    
    animatePlayer2:
        ; Should be left sprite?
        mov ax, [x_pos_2]
        mov bx, [x_pos_1]
        cmp ax, bx
        jg .left

        ; In air
        mov ax, [y_pos_2]
        add ax, SPRITE_HEIGHT
        cmp ax, WINDOW_DOWN_BORDER
        jl .midair

        ; Grounded
        ; TO-DO: add special grounded animations conditions here

        ; Default: idle
        mov word [player_current_sprite2], ryuIdle0
        ret

        .midair:
            ; TO-DO: add special midair animations conditions here
            mov ax, [jumping_2]
            cmp ax, 1
            je .jumping

            ; Default: fall
            mov word [player_current_sprite2], ryuFall5
            ret
        .jumping:
            mov word [player_current_sprite2], ryuJump5
            ret
        .crouch:
            ; Default crouch:
            mov word [player_current_sprite2], ryuCrouch
            ret
            
        .left:
            ; In air
            mov ax, [y_pos_2]
            add ax, SPRITE_HEIGHT
            cmp ax, WINDOW_DOWN_BORDER
            jl .leftMidair

            ; Grounded
            ; TO-DO: add special grounded animations conditions here

            ; Default: idle
            mov word [player_current_sprite2], ryuIdleLeft0
            ret
        .leftMidair:
            ; TO-DO: add special midair animations conditions here
            mov ax, [jumping_2]
            cmp ax, 1
            je .leftJumping

            ; Default: fall
            mov word [player_current_sprite2], ryuFallLeft5
            ret
        .leftJumping:
            mov word [player_current_sprite2], ryuJumpLeft5
            ret
        .leftCrouch:
            ; Default crouch
            mov word [player_current_sprite2], ryuCrouchLeft
            ret
