section .text    
    pacmanEating:
        cmp al, 38 ; fruit
        je .eraseFruit
        cmp al, 35 ; super gum
        je .eraseSuperGum
        cmp al, 36 ; gum
        je .eraseGum
        jmp .exit
        .eraseFruit:
            cmp byte [fruit_should_be_displayed], FALSE
            je .exit
            call eraseFruit
            ; -- WHICH FRUIT --
            mov bx, [current_fruit_case_index]
            shl bx, 1
            addToScore [fruit_score_table+bx]
            jmp .exit
        .eraseSuperGum:
            dec byte [maze_remaining_gums]
            mov byte [maze+bx], 37
            call setFrightMode
            addToScore 50
            jmp .exit
        .eraseGum:
            dec byte [maze_remaining_gums]
            mov byte [maze+bx], 37
            addToScore 10
        .exit:
            ret

    pacDeath:
        call deathAnimation
        cmp byte [pacman_lives], 0
        jne .skipGameOver
        textDisplay gameOverText, 9, STATE_TEXT_Y_POS, STATE_TEXT_X_POS - 12, FONT_HEIGHT, FONT_WIDTH
        call displayViewport
        %rep 40
            mov dx, 50000
            mov ah, 0x86
            int 0x15
        %endrep
        ; update highscore
        call compareScores
        mov bx, 0
        %rep 7
            mov byte [current_score+bx], 0
            inc bx
        %endrep
        mov byte [level+0], 0
        mov byte [level+1], 0
        mov byte [level+2], 1
        mov byte [current_fruit_case_index], 0
        mov byte [pacman_lives], 3
        jmp init
        .skipGameOver:
        mov word ax, [pacmanStruc + entity.initial_x_pos]
        mov word [pacmanStruc + entity.x_pos], ax
        mov word ax, [pacmanStruc + entity.initial_y_pos]
        mov word [pacmanStruc + entity.y_pos], ax
        mov word [pacmanStruc + entity.x_speed], 2
        mov word [pacmanStruc + entity.y_speed], 0
        mov word [pacmanStruc + entity.x_speed_buffer], 0
        mov word [pacmanStruc + entity.y_speed_buffer], 0
        mov byte [pacmanStruc + entity.movement_buffered], FALSE
        mov byte [pacmanStruc + entity.sprite_nb], 3
        mov byte [pacmanStruc + entity.animation_frame], 1
        mov byte [pacmanStruc + entity.is_dead], FALSE
        dec byte [pacman_lives]

        initGhosts
        mov byte [blinkyStruc + entity.sprite_nb], 7
        mov byte [pinkyStruc + entity.sprite_nb], 5
        mov byte [inkyStruc + entity.sprite_nb], 0
        mov byte [clydeStruc + entity.sprite_nb], 0

        mov byte [cage_amount_of_ghosts], 3
        mov byte [ghost_waiting_in_cage+0], FALSE
        mov byte [ghost_waiting_in_cage+1], TRUE
        mov byte [ghost_waiting_in_cage+2], TRUE
        mov byte [ghost_waiting_in_cage+3], TRUE

        call initUIAndTimer
        jmp readKeyboard

    deathAnimation:
        %rep 20
            mov dx, 50000
            mov ah, 0x86
            int 0x15
        %endrep
        mov byte [pacmanStruc + entity.sprite_nb], 0
        %rep 12
            call clearViewport
            call printMaze
            mov al, [pacmanStruc + entity.sprite_nb]
            xor ah, ah ; make sure we read only 1 byte of item

            mov bx, ENTITY_SPRITE_WIDTH * ENTITY_SPRITE_HEIGHT
            mul bx

            mov si, pacmanDeath
            add si, ax

            displayItem [pacmanStruc + entity.y_pos], [pacmanStruc + entity.x_pos], ENTITY_SPRITE_HEIGHT, ENTITY_SPRITE_WIDTH
            call printUI
            call displayViewport
            inc byte [pacmanStruc + entity.sprite_nb]
            mov dx, 50000
            mov ah, 0x86
            int 0x15
        %endrep
        %rep 20
            mov dx, 50000
            mov ah, 0x86
            int 0x15
        %endrep
        ret