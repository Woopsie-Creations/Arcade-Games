org 100h

%define TRUE 1
%define FALSE 0

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"
%include "collisions.inc"
%include "animations.inc"
%include "timer.inc"

section .bss
    current_mode resb 1 ; 0 = 1P / 1 = 2P --- default 1P

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------
    call initViewport
    jmp mainmenu
    
    initFromMenu:
        mov word [current_player_ghost], blinkyStruc
        mov byte [pacman_lives], 3
        mov byte [level+0], 0
        mov byte [level+1], 0
        mov byte [level+2], 1
        mov byte [current_score+0], 0
        mov byte [current_score+1], 0
        mov byte [current_score+2], 0
        mov byte [current_score+3], 0
        mov byte [current_score+4], 0
        mov byte [current_score+5], 0
        mov byte [current_score+6], 0
        mov byte [fruits_eaten], 0
        mov byte [isPause], 0
        mov byte [fruit_should_be_displayed], 0
        mov byte [current_fruit_case_index], 0

        createGhostsTimers

    init:
        call getHighScore
        call initLevel
        call initUIAndTimer

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
        jmp init

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
%include "menu.inc"
%include "key_input.inc"
%include "pacman.inc"
%include "ghosts.inc"