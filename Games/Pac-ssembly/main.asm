org 100h

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"

section .data
    %define FRAME_RATE 30

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------

    call clearScreen
    call initViewport

    gameLoop:
        call waitForNextFrame
        call pacmanMovement
        call pacmanAnimation
        call displayFrame
        jmp readKeyboard

; ------------------------------
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

%include "display.inc"
%include "key_input.inc"
%include "pacman.inc"





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