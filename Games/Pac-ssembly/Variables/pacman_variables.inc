section .data
    PACMAN_WIDTH equ 12
    PACMAN_HEIGHT equ 12

    %define PACMAN_INITIAL_X_POS MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 5
    %define PACMAN_INITIAL_Y_POS MAZE_Y_POS + WALL_HEIGHT * 23 - 3

    col_test_nb db 1

section .bss
    pacman_x_pos resw 1
    pacman_y_pos resw 1
    pacman_x_speed resw 1
    pacman_y_speed resw 1
    pacman_x_speed_buffer resw 1
    pacman_y_speed_buffer resw 1
    movement_buffered resb 1
    buffered_col_test resb 1

    pacman_animation_frame resb 1
