section .data
    PACMAN_WIDTH equ 12
    PACMAN_HEIGHT equ 12

    pacman_direction db 1

    pacman_x_pos dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 7
    pacman_y_pos dw MAZE_Y_POS + WALL_HEIGHT * 23 - 3

    pacman_animation_frame db 0

    bludtest dw 0