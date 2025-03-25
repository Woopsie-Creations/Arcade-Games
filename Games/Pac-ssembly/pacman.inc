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
            cmp word [pacman_y_pos], 0
            je .endMovement
            dec word [pacman_y_pos]
            ret
        .goRight:
            cmp word [pacman_x_pos], 319 - 10
            je .endMovement
            inc word [pacman_x_pos]
            ret
        .goDown:
            cmp word [pacman_y_pos], 199 - 10
            je .endMovement
            inc word [pacman_y_pos]
            ret
        .goLeft:
            cmp word [pacman_x_pos], 0
            je .endMovement
            dec word [pacman_x_pos]
            ret
        .endMovement:
        ret

    pacmanAnimation:
        inc byte [pacman_animation_frame]
        cmp byte [pacman_animation_frame], 4
        je .pacmanFrame1
        cmp byte [pacman_animation_frame], 8
        je .pacmanFrame2
        cmp byte [pacman_animation_frame], 12
        je .pacmanFrame3
        cmp byte [pacman_animation_frame], 16
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