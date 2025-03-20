org 100h

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

%include "display.inc"