org 100h

section .data
    ; constant initialization
    WINDOW_TOP_BORDER equ 10
    WINDOW_LEFT_BORDER equ 10
    WINDOW_RIGHT_BORDER equ 310
    WINDOW_DOWN_BORDER equ 190

    DELAY_WAITLOOP equ 2000

    INIT_X_POS_1 equ 20
    INIT_X_POS_2 equ 240
    INIT_Y_POS_1 equ 50
    INIT_Y_POS_2 equ 50

    SPRITE_WIDTH equ 64
    SPRITE_HEIGHT equ 92

section .bss
    x_pos_1: resw 1
    y_pos_1: resw 1

    x_pos_2: resw 1
    y_pos_2: resw 1

section .text
    ; set video mode
    mov ax, 13h
    int 10h
    jmp init


; -----------------------------------------------
init:
    call clearScreen
    call positionSetup

gameLoop:
    call applyGravity
    call setViewport
    call displayViewport
    jmp readKeyboard

; -------------------
positionSetup:
    mov word [x_pos_1], INIT_X_POS_1
    mov word [x_pos_2], INIT_X_POS_2
    mov word [y_pos_1], INIT_Y_POS_1
    mov word [y_pos_2], INIT_Y_POS_2
    ret

; ---------------------------------------------------------
clearScreen:
    mov ax, 0xA000
    mov es, ax
    mov di, 0
    mov cx, 320*200
    rep stosb
    ret

waitLoop:
    loop waitLoop
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


%include "KeyboardInput.inc"
%include "Physic.inc"
%include "Display.inc"
%include "sprite.inc"