section .data
    viewport_memory_block_pos dw 0

    SCREEN_WIDTH equ 320
    SCREEN_HEIGHT equ 200

    save_color db 0

    item db 3 ; Pacman
         db 0 ; Scared ghosts
         db 7 ; Blinky
         db 5 ; Pinky
         db 0 ; Inky
         db 0 ; Clyde