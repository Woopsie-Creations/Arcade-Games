org 100h

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"

section .data
    %define FRAME_RATE 30

    clock_save dd 0

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------

    call clearScreen

    gameLoop:
        call waitForNextFrame
        call clearScreen
        call pacmanMovement
        call pacmanAnimation
        call displayFrame
        jmp readKeyboard

; ------------------------------
    waitForNextFrame:
        ; will not stay like this, it works for now by being kind of a 30 fps loop, but it is juts a sleep function, not even dynamic
        mov dx, 30000
        mov ah, 0x86
        int 0x15
        ret
        ; cmp dword [clock_save], 0
        ; je .initClock
        ; .wait:
        ;     mov ah, 0x00
        ;     int 0x1A
        ;     mov ebx, [clock_save]
        ;     mov eax, edx
        ;     sub eax, ebx
        ;     cmp eax, 1
        ;     jb .wait
        ; .initClock:
        ; mov ah, 0x00
        ; int 0x1A
        ; mov dword [clock_save], edx
        ; ret

    resetRegisters:
        xor ax, ax
        xor bx, bx
        xor cx, cx
        xor dx, dx
        ret

    exitProgram:
        mov ah, 4Ch
        xor al, al
        int 21h

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