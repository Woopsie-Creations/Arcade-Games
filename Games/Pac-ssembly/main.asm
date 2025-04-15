org 100h

%include "Sprites/include_sprites.inc"
%include "Variables/include_variables.inc"

section .data
    %define FRAME_RATE 30

    ; clock_save dd 0

    memory_block_pos dw 0

    test_var db 0

section .text
    mov ah, 00h     ;--------------------------------
    mov al, 13h     ; set screen 320x200 256colours
    int 10h         ;--------------------------------

    call clearScreen

    call testfunc
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

    testfunc:
        call resetRegisters ; yea can be useful, for now i leave him here in case
        mov bx, 1           ; nb of 16bits sections we want to allocate
        ; interrupt
        mov ah, 48h
        int 21h
        ; if failed to allocate, exit
        jc exitProgram
        ; save the pos of the block allocated
        mov word [memory_block_pos], ax
        ; write whatever we want in the memory, by sections of 8bits (don't ask why why not 16, it's made like that so follow :))
        mov es, ax
        mov byte [es:0], 0x20
        ret
        

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