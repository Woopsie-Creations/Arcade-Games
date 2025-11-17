org 100h

section .text
    mov ax, 13h
    int 10h

    call reset_file

    call titleScreen

    mov si, sf_game
    mov [current_game], si
    mov al, [sf_game_x_pos]
    mov [current_game_x_pos], al
    mov al, [sf_game_y_pos]
    mov [current_game_y_pos], al
    call mainMenu



exit_launcher:
    mov ah, 4Ch
    xor al, al
    int 21h

%include "display.inc"