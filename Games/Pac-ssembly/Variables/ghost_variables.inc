section .data
    GHOST_WIDTH equ 12
    GHOST_HEIGHT equ 12

    ghost_sprite dw blinky
                 dw pinky
                 dw inky
                 dw clyde

    %define BLINKY_INITIAL_X_POS MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 7
    %define PINKY_INITIAL_X_POS MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - WALL_WIDTH
    %define INKY_INITIAL_X_POS MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - (GHOST_WIDTH + WALL_WIDTH)
    %define CLYDE_INITIAL_X_POS MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) + WALL_WIDTH

    %define BLINKY_INITIAL_Y_POS MAZE_Y_POS + WALL_HEIGHT * 11 - 3
    %define PINKY_INITIAL_Y_POS MAZE_Y_POS + WALL_HEIGHT * 14 - 3
    %define INKY_INITIAL_Y_POS MAZE_Y_POS + WALL_HEIGHT * 14 - 3
    %define CLYDE_INITIAL_Y_POS MAZE_Y_POS + WALL_HEIGHT * 14 - 3

    ghost_col_test_nb db 1
                      db 1
                      db 1
                      db 1

section .bss
    ghost_x_pos resw 4
    ghost_y_pos resw 4
    ghost_x_speed resw 4
    ghost_y_speed resw 4
    ghost_x_speed_buffer resw 4
    ghost_y_speed_buffer resw 4

    ghost_movement_buffered resb 4
    ghost_buffered_col_test resb 4

    ghost_animation_frame resb 4
