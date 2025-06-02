org 100h

%define TRUE 1
%define FALSE 0

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"
%include "collisions.inc"
%include "animations.inc"
%include "timer.inc"

%define FRAME_RATE 30

%macro initGhosts 0-* blinky, pinky, inky, clyde
    %rep %0
        mov word ax, [%1Struc + entity.initial_x_pos]
        mov word [%1Struc + entity.x_pos], ax
        mov word ax, [%1Struc + entity.initial_y_pos]
        mov word [%1Struc + entity.y_pos], ax

        mov word [%1Struc + entity.x_speed], -2
        mov word [%1Struc + entity.y_speed], 0
        mov word [%1Struc + entity.x_speed_buffer], 0
        mov word [%1Struc + entity.y_speed_buffer], 0
        mov byte [%1Struc + entity.movement_buffered], FALSE
        mov byte [%1_in_fright_mode], FALSE
        mov byte [ghosts_eaten_in_a_row], 0
        %rotate 1
    %endrep
%endmacro

%macro updateCurrentStateText 1
    mov bx, 0
    %rep 5
        mov word ax, [%1+bx]
        mov word [current_state_text+bx], ax
        add bx, 2
    %endrep
%endmacro

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
        call waitForNextFrame
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
        mov byte [pacmanStruc + entity.is_dead], FALSE
        ; ghosts
        initGhosts
        mov byte [blinkyStruc + entity.sprite_nb], 7
        mov byte [pinkyStruc + entity.sprite_nb], 5
        mov byte [inkyStruc + entity.sprite_nb], 0
        mov byte [clydeStruc + entity.sprite_nb], 0

        mov byte [cage_amount_of_ghosts], 3
        mov byte [ghost_waiting_in_cage+0], FALSE
        mov byte [ghost_waiting_in_cage+1], TRUE
        mov byte [ghost_waiting_in_cage+2], TRUE
        mov byte [ghost_waiting_in_cage+3], TRUE

        call clearViewport
        call initUIAndTimer
        ret

    initUIAndTimer:
        updateCurrentStateText readyText
        call waitForEnterPress
        updateCurrentStateText pauseText
        initGhostTimers
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
%include "pacman.inc"
%include "ghosts.inc"