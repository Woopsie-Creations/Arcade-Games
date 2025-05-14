section .data
    TITLE_X_POS equ MAZE_X_POS - 8 - TITLE_WIDTH
    TITLE_Y_POS equ 4
    TITLE_WIDTH equ 62
    TITLE_HEIGHT equ 14

    TEAM_X_POS equ (MAZE_X_POS + (COLUMN_NUMBER * WALL_WIDTH)) + 8
    TEAM_Y_POS equ 4
    TEAM_WIDTH equ 62
    TEAM_HEIGHT equ 14

    PRESS_ARROWS_X_POS equ MAZE_X_POS - 8 - (5 * FONT_WIDTH + 4)
    PRESS_ARROWS_Y_POS equ (ROW_NUMBER * WALL_HEIGHT) - 4 - (PRESS_ARROWS_HEIGHT + FONT_HEIGHT + 4)
    PRESS_ARROWS_WIDTH equ 26
    PRESS_ARROWS_HEIGHT equ 5

    PRESS_ENTER_X_POS equ (MAZE_X_POS + (COLUMN_NUMBER * WALL_WIDTH)) + 8
    PRESS_ENTER_Y_POS equ (ROW_NUMBER * WALL_HEIGHT) - 4 - (PRESS_ARROWS_HEIGHT + FONT_HEIGHT + 4)

    SCORE_TEXT_X_POS equ MAZE_X_POS - 8 - SCORE_TEXT_TITLE_WIDTH
    SCORE_TEXT_Y_POS equ 28
    SCORE_TEXT_TITLE_WIDTH equ 39
    SCORE_TEXT_TITLE_HEIGHT equ 10
    
    SCORE_BOX_X_POS equ MAZE_X_POS - 8 - SCORE_BOX_WIDTH
    SCORE_BOX_Y_POS equ 41
    SCORE_BOX_WIDTH equ 58

    FRUIT_TITLE_X_POS equ (MAZE_X_POS + (COLUMN_NUMBER * WALL_WIDTH)) + 8
    FRUIT_TITLE_Y_POS equ 28
    FRUIT_TITLE_WIDTH equ 39
    FRUIT_TITLE_HEIGHT equ 10
    FRUIT_BANK_X_POS equ (MAZE_X_POS + (COLUMN_NUMBER * WALL_WIDTH)) + 8
    FRUIT_BANK_Y_POS equ FRUIT_TITLE_Y_POS + FRUIT_TITLE_HEIGHT + 5
    FRUIT_HEIGHT equ 9
    FRUIT_WIDTH equ 11
    SELECT_FRUIT_BOX_HEIGHT equ 14
    SELECT_FRUIT_BOX_WIDTH equ 14

    LEVEL_X_POS equ (MAZE_X_POS + (COLUMN_NUMBER * WALL_WIDTH)) + 8
    LEVEL_Y_POS equ (ROW_NUMBER * WALL_HEIGHT) - 32 - (LEVEL_TITLE_HEIGHT + LEVEL_NUMBER_HEIGHT + 2)
    LEVEL_BOX_Y_POS equ LEVEL_Y_POS + 11
    LEVEL_TITLE_WIDTH equ 39
    LEVEL_TITLE_HEIGHT equ 10
    LEVEL_NUMBER_WIDTH equ 22
    LEVEL_NUMBER_HEIGHT equ 10

    pressText dw P, R, E, S, S
    enterText dw E, N, T, E, R
    escText dw E, S, C, A, P, E

    displayNumbersFont dw font0
                       dw font1
                       dw font2
                       dw font3
                       dw font4
                       dw font5
                       dw font6
                       dw font7
                       dw font8
                       dw font9
    
    fruit_table:
                db 0      ; Offset of 1 (cannot be level 0), default cherry
                db 0      ; Level 1 - Cherry
                db 1      ; Level 2 - Strawberry
                db 2      ; Level 3 - Orange
                db 2      ; Level 4 - Orange
                db 3      ; Level 5 - Apple
                db 3      ; Level 6 - Apple
                db 4      ; Level 7 - Melon
                db 4      ; Level 8 - Melon
                db 5      ; Level 9 - Galaxian
                db 5      ; Level 10 - Galaxian
                db 6      ; Level 11 - Bell
                db 6      ; Level 12 - Bell
                db 7      ; Level 13 - Key

    
section .bss
    current_fruit_case_index resb 1
    isPause resb 1
    letter_x_pos resw 1
    letter_y_pos resw 1
    displayedNumbers resw 9
    displayedLevel resw 3
