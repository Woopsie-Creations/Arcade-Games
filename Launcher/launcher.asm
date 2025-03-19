org 100h

section .data
    welcome_to_message db 'Welcome to', 0
    welcome_to_message_x_pos db 7
    welcome_to_message_y_pos db 37

    arcade_launcher_message db 'GAME HUB', 0
    arcade_launcher_message_x_pos db 8
    arcade_launcher_message_y_pos db 39

    arrow_left db '<', 0
    arrow_left_x_pos db 0
    arrow_left_y_pos db 38

    arrow_right db '>', 0
    arrow_right_x_pos db 23
    arrow_right_y_pos db 38

    ps_game db 'Pacssembly', 0
    ps_game_x_pos db 7
    ps_game_y_pos db 38

    sf_game db 'Street-Fighssembly', 0
    sf_game_x_pos db 3
    sf_game_y_pos db 38

section .bss
    current_game resw 1
    current_game_x_pos resb 1
    current_game_y_pos resb 1

section .text
    mov ax, 13h
    int 10h        

    call titleScreen

    mov si, sf_game
    mov [current_game], si
    mov al, [sf_game_x_pos]
    mov [current_game_x_pos], al
    mov al, [sf_game_y_pos]
    mov [current_game_y_pos], al
    call mainMenu

; -----------------------------------------------
exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h

%include "display.inc"