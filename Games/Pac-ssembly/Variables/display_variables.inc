section .data
    item_width dw 10
    item_height dw 90
    
    item_x_pos dw 20
    item_y_pos dw 20

    item_frame_selection dw 0

    item db 3 ; Pacman
         db 0 ; Scared ghosts
         db 0 ; Blinky
         db 0 ; Pinky
         db 0 ; Inky
         db 0 ; Clyde