org 100h

%define TRUE 1
%define FALSE 0

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"
%include "collisions.inc"
%include "animations.inc"
%include "timer.inc"

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------

    createGhostsTimers
    call initViewport

    init:
        call getHighScore
        call initLevel

    gameLoop:
        call events
        call ghostBehavior
        movements
        colBetweenEntities
        pacman_animations
        ghosts_animations
        call displayFrame
        cmp byte [pacmanStruc + entity.is_dead], TRUE
        je pacDeath
        jmp readKeyboard

; ------------------------------
    goToNextLevel:
        call increaseLevel
        call initLevel
        jmp gameLoop

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

    ; deallocate the memory used for the viewport (so it's more clean)
    deallocationViewport:
        mov ax, [viewport_memory_block_pos]
        mov es, ax
        xor ax, ax
        mov ah, 49h
        int 21h
        jc gameLoop ; return to the gameloop in case of failure (just to verify for now, will probably change)
        ret

%include "init.inc"
%include "score.inc"
%include "display.inc"
%include "key_input.inc"
%include "pacman.inc"
%include "ghosts.inc"