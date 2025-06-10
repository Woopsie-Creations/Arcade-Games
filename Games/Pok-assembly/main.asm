org 100h

%define TRUE 1
%define FALSE 0
%define NULL 0

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"
%include "init_pokemon.inc"

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256 colors
    int 10h         ;--------------------------------

    call initViewport
    initPokes first_trainerStruc, first_onepokemonStruc, first_twopokemonStruc
    initPokes second_trainerStruc, second_onepokemonStruc, second_twopokemonStruc
    call displayFrame

    gameLoop:
        jmp readKeyboard

; ------------------------------
    resetRegisters:
        xor ax, ax
        xor bx, bx
        xor cx, cx
        xor dx, dx
        ret

    exitProgram:
        call deallocationViewport
        mov ah, 4Ch
        xor al, al
        int 21h

%include "loadFromFile.inc"
%include "display.inc"
%include "events.inc"
%include "key_input.inc"