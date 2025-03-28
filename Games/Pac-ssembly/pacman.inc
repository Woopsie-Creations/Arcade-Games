section .text
    pacmanMovement:
        cmp byte [pacman_direction], 0
        je .goUp
        cmp byte [pacman_direction], 1
        je .goRight
        cmp byte [pacman_direction], 2
        je .goDown
        cmp byte [pacman_direction], 3
        je .goLeft
        .goUp:
            mov ax, [pacman_y_pos]
            sub ax, MAZE_Y_POS
            add ax, WALL_HEIGHT / 2 - 1
            mov bx, WALL_HEIGHT
            xor dx, dx
            div bx
            mov bx, COLUMN_NUMBER
            xor dx, dx
            mul bx
            push ax

            mov ax, [pacman_x_pos]
            sub ax, MAZE_X_POS
            add ax, PACMAN_WIDTH / 2
            mov bx, WALL_WIDTH
            xor dx, dx
            div bx
            mov bx, ax
            pop ax

            add bx, ax
            shl bx, 1
            mov ax, [maze+bx]
            cmp ax, 35
            je .moveUp
            cmp ax, 36
            je .moveUp
            cmp ax, 37
            je .moveUp
            jmp .endMovement
            .moveUp:
            sub word [pacman_y_pos], 2
            ret
        .goRight:
            mov ax, [pacman_y_pos]
            sub ax, MAZE_Y_POS
            add ax, PACMAN_HEIGHT / 2
            mov bx, WALL_HEIGHT
            xor dx, dx
            div bx
            mov bx, COLUMN_NUMBER
            xor dx, dx
            mul bx
            push ax

            mov ax, [pacman_x_pos]
            sub ax, MAZE_X_POS
            add ax, PACMAN_WIDTH / 2 + WALL_WIDTH / 2
            mov bx, WALL_WIDTH
            xor dx, dx
            div bx
            mov bx, ax
            pop ax

            add bx, ax
            shl bx, 1
            mov ax, [maze+bx]
            cmp ax, 35
            je .moveRight
            cmp ax, 36
            je .moveRight
            cmp ax, 37
            je .moveRight
            jmp .endMovement
            .moveRight:
            add word [pacman_x_pos], 2
            ret
        .goDown:
            mov ax, [pacman_y_pos]
            sub ax, MAZE_Y_POS
            add ax, PACMAN_HEIGHT / 2 + WALL_HEIGHT / 2
            mov bx, WALL_HEIGHT
            xor dx, dx
            div bx
            mov bx, COLUMN_NUMBER
            xor dx, dx
            mul bx
            push ax

            mov ax, [pacman_x_pos]
            sub ax, MAZE_X_POS
            add ax, PACMAN_WIDTH / 2
            mov bx, WALL_WIDTH
            xor dx, dx
            div bx
            mov bx, ax
            pop ax

            add bx, ax
            shl bx, 1
            mov ax, [maze+bx]
            cmp ax, 35
            je .moveDown
            cmp ax, 36
            je .moveDown
            cmp ax, 37
            je .moveDown
            jmp .endMovement
            .moveDown:
            add word [pacman_y_pos], 2
            ret
        .goLeft:
            mov ax, [pacman_y_pos]
            sub ax, MAZE_Y_POS
            add ax, PACMAN_HEIGHT / 2
            mov bx, WALL_HEIGHT
            xor dx, dx
            div bx
            mov bx, COLUMN_NUMBER
            xor dx, dx
            mul bx
            push ax

            mov ax, [pacman_x_pos]
            sub ax, MAZE_X_POS
            add ax, WALL_WIDTH / 2 - 1
            mov bx, WALL_WIDTH
            xor dx, dx
            div bx
            mov bx, ax
            pop ax

            add bx, ax
            shl bx, 1
            mov ax, [maze+bx]
            cmp ax, 35
            je .moveLeft
            cmp ax, 36
            je .moveLeft
            cmp ax, 37
            je .moveLeft
            jmp .endMovement
            .moveLeft:
            sub word [pacman_x_pos], 2
            ret
        .endMovement:
        ret

    pacmanAnimation:
        inc byte [pacman_animation_frame]
        cmp byte [pacman_animation_frame], 2
        je .pacmanFrame1
        cmp byte [pacman_animation_frame], 4
        je .pacmanFrame2
        cmp byte [pacman_animation_frame], 6
        je .pacmanFrame3
        cmp byte [pacman_animation_frame], 8
        je .pacmanFrame4
        ret
        .pacmanFrame1:
            inc byte [item+0]
            ret
        .pacmanFrame2:
            dec byte [item+0]
            ret
        .pacmanFrame3:
            mov byte [item+0], 0
            ret
        .pacmanFrame4:
            cmp byte [pacman_direction], 0
            je .firstFrameUp
            cmp byte [pacman_direction], 1
            je .firstFrameRight
            cmp byte [pacman_direction], 2
            je .firstFrameDown
            cmp byte [pacman_direction], 3
            je .firstFrameLeft
            .firstFrameUp:
                mov byte [item+0], 1
                jmp .endAnimation
            .firstFrameRight:
                mov byte [item+0], 3
                jmp .endAnimation
            .firstFrameDown:
                mov byte [item+0], 5
                jmp .endAnimation
            .firstFrameLeft:
                mov byte [item+0], 7
                jmp .endAnimation
            .endAnimation:
            mov byte [pacman_animation_frame], 0
            ret