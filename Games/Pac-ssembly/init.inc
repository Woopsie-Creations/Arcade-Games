%macro initGhosts 0-* blinky, pinky, inky, clyde
    %rep %0
        mov word ax, [%1Struc + entity.initial_x_pos]
        mov word [%1Struc + entity.x_pos], ax
        mov word ax, [%1Struc + entity.initial_y_pos]
        mov word [%1Struc + entity.y_pos], ax

        mov word [%1Struc + entity.x_speed], -2
        mov word [%1Struc + entity.y_speed], 0
        mov word [%1Struc + entity.x_speed_buffer], 0
        mov word [%1Struc + entity.y_speed_buffer], 0
        mov byte [%1Struc + entity.movement_buffered], FALSE
        mov byte [%1_in_fright_mode], FALSE
        mov byte [ghosts_eaten_in_a_row], 0
        %rotate 1
    %endrep
%endmacro

%macro updateCurrentStateText 1
    mov bx, 0
    %rep 5
        mov word ax, [%1+bx]
        mov word [current_state_text+bx], ax
        add bx, 2
    %endrep
%endmacro

    initLevel:
        ; maze
        mov bx, ROW_NUMBER * COLUMN_NUMBER
        .eachCells:
            mov al, [mazesave+bx]
            mov [maze+bx], al
            dec bx
            jnz .eachCells
        ; gums
        mov byte [maze_remaining_gums], MAZE_AMOUNT_OF_GUMS
        ; pacman
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
        ; ghosts
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

        call clearViewport
        call initUIAndTimer
        ret

    initUIAndTimer:
        updateCurrentStateText readyText
        call waitForEnterPress
        updateCurrentStateText pauseText
        initGhostTimers
        ret