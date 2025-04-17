section .data
    viewport_memory_block_pos dw 0

    SCREEN_WIDTH equ 320
    SCREEN_HEIGHT equ 200

    save_color db 0

    item_width dw 0
    item_height dw 0
    
    item_x_pos dw 0
    item_y_pos dw 0

    item_frame_selection dw 0

    item db 3 ; Pacman
         db 0 ; Scared ghosts
         db 0 ; Blinky
         db 0 ; Pinky
         db 0 ; Inky
         db 0 ; Clyde