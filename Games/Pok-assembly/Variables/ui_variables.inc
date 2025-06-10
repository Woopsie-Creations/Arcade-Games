section .data
    

    HP_BAR_HEIGHT equ 6
    HP_BAR_WIDTH equ 68
    FIRST_PLAYER_HP_BAR_X_POS equ 200
    FIRST_PLAYER_HP_BAR_Y_POS equ 100
    SECOND_PLAYER_HP_BAR_X_POS equ 13
    SECOND_PLAYER_HP_BAR_Y_POS equ 10

    HP_ARROW_HEIGHT equ 23
    HP_ARROW_WIDTH equ 80
    FIRST_PLAYER_HP_ARROW_X_POS equ 196
    FIRST_PLAYER_HP_ARROW_Y_POS equ 100
    SECOND_PLAYER_HP_ARROW_X_POS equ 5
    SECOND_PLAYER_HP_ARROW_Y_POS equ 10

    hp_color_table:
        db 0x2F
        db 0x2C
        db 0x28

section .bss
    current_hp_width resb 1
    current_hp_color resb 1