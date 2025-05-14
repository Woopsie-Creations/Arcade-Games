org 100h

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"

%define FRAME_RATE 30

%macro initGhosts 0-* 0, 1, 2, 3
    %rep %0
        mov word [ghost_x_speed+%1*2], 0
        mov word [ghost_y_speed+%1*2], 0
        mov word [ghost_x_speed_buffer+%1*2], 0
        mov word [ghost_y_speed_buffer+%1*2], 0
        mov byte [ghost_movement_buffered+%1], 0
        %rotate 1
    %endrep
%endmacro

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------

    init:
        call initLevel

    gameLoop:
        cmp byte [MAZE_AMOUNT_OF_GUMS], 0
        je goToNextLevel

        call waitForNextFrame
        call pacmanMovement
        call pacmanAnimation
        call displayFrame
        ; call ghostBehavior
        call ghostAnimation
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
        mov byte [MAZE_AMOUNT_OF_GUMS], 246
        ; pacman
        mov word [pacman_x_pos], PACMAN_INITIAL_X_POS
        mov word [pacman_y_pos], PACMAN_INITIAL_Y_POS
        mov word [pacman_x_speed], 2
        mov word [pacman_y_speed], 0
        mov word [pacman_x_speed_buffer], 0
        mov word [pacman_y_speed_buffer], 0
        mov byte [movement_buffered], 0
        mov byte [item+0], 3
        ; ghosts
        mov word [ghost_x_pos], BLINKY_INITIAL_X_POS
        mov word [ghost_x_pos+2], PINKY_INITIAL_X_POS
        mov word [ghost_x_pos+4], INKY_INITIAL_X_POS
        mov word [ghost_x_pos+6], CLYDE_INITIAL_X_POS
        mov word [ghost_y_pos], BLINKY_INITIAL_Y_POS
        mov word [ghost_y_pos+2], PINKY_INITIAL_Y_POS
        mov word [ghost_y_pos+4], INKY_INITIAL_Y_POS
        mov word [ghost_y_pos+6], CLYDE_INITIAL_Y_POS
        mov byte [cage_amount_of_ghosts], 3
        mov byte [ghost_waiting_in_cage], 0 
        mov byte [ghost_waiting_in_cage+1], 1
        mov byte [ghost_waiting_in_cage+2], 1
        mov byte [ghost_waiting_in_cage+3], 1
        mov byte [item+2], 6
        mov byte [item+3], 4
        mov byte [item+4], 0
        mov byte [item+5], 0

        initGhosts

        call clearScreen
        call initViewport
        call waitForEnterPress
        call initTimer
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

%include "score.inc"
%include "display.inc"
%include "key_input.inc"
%include "collisions.inc"
%include "pacman.inc"
%include "ghosts.inc"
%include "timer.inc"



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