section .data
    PACMAN_WIDTH equ 12
    PACMAN_HEIGHT equ 12

    pacman_direction db 1

    pacman_x_pos dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 7
    pacman_y_pos dw MAZE_Y_POS + WALL_HEIGHT * 23 - 3

    pacman_x_speed dw 2
    pacman_y_speed dw 0

    pacman_x_speed_buffer dw 0
    pacman_y_speed_buffer dw 0

    col_test_nb db 1

    pacman_animation_frame db 0