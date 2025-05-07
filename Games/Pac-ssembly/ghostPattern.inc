section .text
    ghostPattern:
        call blinkyPattern
        ; call pinkyPattern
        ret
    
    blinkyPattern:
        ; --- BLINKY ---
        cmp byte [ghost_waiting_in_cage+0], 1
        je .earlyExit

        mov bx, 0
        mov ax, MAZE_Y_POS + WALL_HEIGHT * 20 - 3
        cmp word [ghost_y_pos+bx], ax
        je goToLeft
        mov ax, MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2 - 3) - 3
        cmp word [ghost_x_pos+bx], ax
        je goToBottom
        call goToLeft
        .earlyExit:
        ret

    pinkyPattern:
        ; --- PINKY ---
        cmp byte [ghost_waiting_in_cage+1], 1
        je .earlyExit

        mov bx, 2
        mov ax, MAZE_Y_POS + WALL_HEIGHT * 20 - 3
        cmp word [ghost_y_pos+bx], ax
        je goToRight
        mov ax, MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2 + 3) + 3
        cmp word [ghost_x_pos+bx], ax
        je goToBottom
        call goToRight
        .earlyExit:
        ret
    
    goToTop:
        mov word [ghost_x_speed+bx], 0
        mov word [ghost_y_speed+bx], -2
        ret
    goToBottom:
        mov word [ghost_x_speed+bx], 0
        mov word [ghost_y_speed+bx], 2
        ret
    goToRight:
        mov word [ghost_x_speed+bx], 2
        mov word [ghost_y_speed+bx], 0
        ret
    goToLeft:
        mov word [ghost_x_speed+bx], -2
        mov word [ghost_y_speed+bx], 0
        ret
