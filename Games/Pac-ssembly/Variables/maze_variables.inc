section .data
    WALL_WIDTH equ 6
    WALL_HEIGHT equ 6

    COLUMN_NUMBER equ 28
    ROW_NUMBER equ 31

    MAZE_X_POS equ (320 - COLUMN_NUMBER * WALL_WIDTH) / 2
    MAZE_Y_POS equ 0

    MAZE_AMOUNT_OF_GUMS equ 246
    
section .bss
    maze_remaining_gums resb 1
    wall_x_pos resw 1
    wall_y_pos resw 1