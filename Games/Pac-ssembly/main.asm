org 100h

%define TRUE 1
%define FALSE 0

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"

%define FRAME_RATE 30

%macro initGhosts 0-* blinky, pinky, inky, clyde
    %rep %0
        mov word ax, [%1Struc + entity.initial_x_pos]
        mov word [%1Struc + entity.x_pos], ax
        mov word ax, [%1Struc + entity.initial_y_pos]
        mov word [%1Struc + entity.y_pos], ax

        mov word [%1Struc + entity.x_speed], 0
        mov word [%1Struc + entity.y_speed], 0
        mov word [%1Struc + entity.x_speed_buffer], 0
        mov word [%1Struc + entity.y_speed_buffer], 0
        mov byte [%1Struc + entity.movement_buffered], FALSE
        %rotate 1
    %endrep
%endmacro

%macro updateCurrentStateText 1  
    mov word ax, [%1]
    mov word [current_state_text], ax
    mov word ax, [%1+2]
    mov word [current_state_text+2], ax
    mov word ax, [%1+4]
    mov word [current_state_text+4], ax
    mov word ax, [%1+6]
    mov word [current_state_text+6], ax
    mov word ax, [%1+8]
    mov word [current_state_text+8], ax
%endmacro

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------

    init:
        call initLevel

    gameLoop:
        call events
        call waitForNextFrame
        call pacmanMovement
        call pacmanAnimation
        call displayFrame
        ; call ghostBehavior
        ; call ghostAnimation
        jmp readKeyboard

; ------------------------------
    goToNextLevel:
        call increaseLevel
        call deallocationViewport
        call initLevel
        jmp gameLoop
        
    initLevel:
        ; maze
        mov bx, ROW_NUMBER * COLUMN_NUMBER
        .eachCells:
            mov al, [mazesave+bx]
            mov [maze+bx], al
            dec bx
            jnz .eachCells
        ; gums
        mov byte [maze_remaining_gums], MAZE_AMOUNT_OF_GUMS
        ; pacman
        mov word ax, [pacmanStruc + entity.initial_x_pos]
        mov word [pacmanStruc + entity.x_pos], ax
        mov word ax, [pacmanStruc + entity.initial_y_pos]
        mov word [pacmanStruc + entity.y_pos], ax
        mov word [pacmanStruc + entity.x_speed], 2
        mov word [pacmanStruc + entity.y_speed], 0
        mov word [pacmanStruc + entity.x_speed_buffer], 0
        mov word [pacmanStruc + entity.y_speed_buffer], 0
        mov byte [pacmanStruc + entity.movement_buffered], FALSE
        mov byte [pacmanStruc + entity.sprite_nb], 3
        mov byte [pacmanStruc + entity.animation_frame], 1
        ; ghosts
        initGhosts
        ; mov byte [cage_amount_of_ghosts], 3
        ; mov byte [ghost_waiting_in_cage], 0 
        ; mov byte [ghost_waiting_in_cage+1], 1
        ; mov byte [ghost_waiting_in_cage+2], 1
        ; mov byte [ghost_waiting_in_cage+3], 1
        mov byte [blinkyStruc + entity.sprite_nb], 6
        mov byte [pinkyStruc + entity.sprite_nb], 4
        mov byte [inkyStruc + entity.sprite_nb], 0
        mov byte [clydeStruc + entity.sprite_nb], 0

        call clearScreen
        call initViewport
        updateCurrentStateText readyText
        call waitForEnterPress
        updateCurrentStateText pauseText
        ; call initTimer ; for ghosts but for now it conflicts with the one for ghosts :)
        ret

    waitForNextFrame:
        ; will not stay like this, it works for now by being kind of a 30 fps loop, but it is juts a sleep function, not even dynamic
        mov dx, 10000
        mov ah, 0x86
        int 0x15
        ret

    clearScreen:
        mov ax, 0xA000
        mov es, ax
        mov di, 0
        mov cx, 320*200
        rep stosb
        ret

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

%include "timer.inc"
%include "score.inc"
%include "display.inc"
%include "key_input.inc"
%include "collisions.inc"
%include "pacman.inc"
; %include "ghosts.inc"



; jmp initMaze
        ; initAll:
        ;     call initFruits
        ;     call initLives
        ;     call initPac
        ;     mov word [frameFromStart], 0

        ;     mov word [ghostIndex], blinkyIndex
        ;     call initGhost

        ;     mov word [ghostIndex], pinkyIndex
        ;     call initGhost

        ;     mov word [ghostIndex], inkyIndex
        ;     call initGhost

        ;     mov word [ghostIndex], clydeIndex
        ;     call initGhost

        ;     call readyDraw
        ;     call initScore
        ;     call initLevelNb
        ;     jmp selectFruit
        ;     isGameStarted:
        ;     cmp byte [started], 1
        ;     je keyBottomLeft
        ;     jmp extraUI
            ; jmp readyClear