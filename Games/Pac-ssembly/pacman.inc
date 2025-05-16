%macro colVerifier 1
    cmp al, 32
    je pacmanMovement.tunnelTeleport
    cmp al, 33
    je pacmanMovement.tunnelTeleport
    cmp al, 35 ; super gum
    je %1
    cmp al, 36 ; gum
    je %1
    cmp al, 37
    je %1
    cmp al, 38
    je %1
    jmp pacmanMovement.skipMovement
%endmacro

%macro pacmanAnimationSide 2
    %1:
        cmp byte [pacman_animation_frame], 1
        je %%pacmanFrame1
        cmp byte [pacman_animation_frame], 2
        je %%pacmanFrame2
        cmp byte [pacman_animation_frame], 3
        je %%pacmanFrame3
        cmp byte [pacman_animation_frame], 4
        je %%pacmanFrame4
        ret
        %%pacmanFrame1:
            mov byte [item+0], %2 + 1
            ret
        %%pacmanFrame2:
            mov byte [item+0], %2
            ret
        %%pacmanFrame3:
            mov byte [item+0], 0
            ret
        %%pacmanFrame4:
            mov byte [item+0], %2
            mov byte [pacman_animation_frame], 0
            ret
%endmacro

section .text
    secondCollisionTest:
        cmp byte [buffered_col_test], 0
        je pacmanMovement.continueDirection
    pacmanMovement:
        cmp word [pacman_x_pos], MAZE_X_POS
        jbe .doMovement
        cmp word [pacman_x_pos], MAZE_X_POS+COLUMN_NUMBER*WALL_WIDTH-PACMAN_WIDTH
        jae .doMovement
        cmp byte [movement_buffered], 0
        je .continueDirection
        mov byte [buffered_col_test], 1
        colCalculations [pacman_y_pos], [pacman_y_speed_buffer], [pacman_x_pos], [pacman_x_speed_buffer], pacmanCol

        .continueDirection:
        mov byte [buffered_col_test], 0
        colCalculations [pacman_y_pos], [pacman_y_speed], [pacman_x_pos], [pacman_x_speed], pacmanCol

        .doMovement:
            call pacmanEating
            inc byte [pacman_animation_frame]
            cmp byte [buffered_col_test], 0
            je .normalMovement
            mov byte [movement_buffered], 0
            mov ax, [pacman_x_speed_buffer]
            mov word [pacman_x_speed], ax
            mov ax, [pacman_y_speed_buffer]
            mov word [pacman_y_speed], ax
            .normalMovement:
            mov ax, [pacman_x_speed]
            add word [pacman_x_pos], ax
            mov ax, [pacman_y_speed]
            add word [pacman_y_pos], ax
            ret
        .skipMovement:
            mov byte [col_test_nb], 1
            cmp byte [buffered_col_test], 1
            je .continueDirection
            mov byte [pacman_animation_frame], 4
            ret
        .tunnelTeleport:
            inc byte [pacman_animation_frame]
            cmp word [pacman_x_speed], -2
            je .tpToRight
            sub word [pacman_x_pos], WALL_WIDTH * 25
            cmp word [pacman_x_pos], 0
            jg .skipFixTp
            add word [pacman_x_pos], 320
            ret
            .tpToRight:
            add word [pacman_x_pos], WALL_WIDTH * 25
            cmp word [pacman_x_pos], 320
            jl .skipFixTp
            sub word [pacman_x_pos], 320
            ret
            .skipFixTp:
            ret

    pacmanAnimation:
        cmp word [pacman_y_speed], -2
        je animationUp
        cmp word [pacman_x_speed], 2
        je animationRight
        cmp word [pacman_y_speed], 2
        je animationDown
        cmp word [pacman_x_speed], -2
        je animationLeft
            pacmanAnimationSide animationUp, 1
            pacmanAnimationSide animationRight, 3
            pacmanAnimationSide animationDown, 5
            pacmanAnimationSide animationLeft, 7
    
    pacmanEating:
        cmp al, 38 ; fruit
        je .eraseFruit
        cmp al, 35 ; super gum
        je .eraseSuperGum
        cmp al, 36 ; gum
        je .eraseGum
        jmp .exit
        .eraseFruit:
            cmp byte [fruit_should_be_displayed], 0
            je .exit
            inc byte [fruits_eaten]
            mov byte [fruit_should_be_displayed], 0
            ; -- WHICH FRUIT --
            mov bx, [current_fruit_case_index]
            shl bx, 1
            addToScore [fruit_score_table+bx]
            jmp .exit
        .eraseSuperGum:
            dec byte [maze_remaining_gums]
            mov byte [maze+bx], 37
            addToScore 50
            jmp .exit
        .eraseGum:
            dec byte [maze_remaining_gums]
            mov byte [maze+bx], 37
            addToScore 10
        .exit:
            ret
