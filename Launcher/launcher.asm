org 100h

global _start

section .data
    welcome_to_message db 'Welcome to', 0
    welcome_to_message_x_pos db 7
    welcome_to_message_y_pos db 36

    arcade_launcher_message db 'GAME HUB', 0
    arcade_launcher_message_x_pos db 8
    arcade_launcher_message_y_pos db 38

section .text
    mov ax, 13h
    int 10h        

    call titleScreen

    call mainMenu
    
    call exitProgram

; -----------------------------------------------
exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h

%include "display.inc"