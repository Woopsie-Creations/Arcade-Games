section .data
    GHOST_WIDTH equ 12
    GHOST_HEIGHT equ 12

    ghost_direction db 1
                    db 1
                    db 1
                    db 1

    ghost_sprite dw blinky
                 dw pinky
                 dw inky
                 dw clyde

    ghost_x_pos dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 5
                dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 5
                dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 16
                dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) + 6

    ghost_y_pos dw MAZE_Y_POS + WALL_HEIGHT * 11 - 2
                dw MAZE_Y_POS + WALL_HEIGHT * 14 - 2
                dw MAZE_Y_POS + WALL_HEIGHT * 14 - 2
                dw MAZE_Y_POS + WALL_HEIGHT * 14 - 2

    ghost_x_speed dw -2
                  dw 0
                  dw 0
                  dw 0

    ghost_y_speed dw 0
                  dw -2
                  dw 2
                  dw -2

    ghost_col_test_nb db 1
                      db 1
                      db 1
                      db 1

    ghost_animation_frame db 0
                          db 0
                          db 0
                          db 0