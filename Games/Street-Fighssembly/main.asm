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

    SPRITE_WIDTH equ 57
    SPRITE_HEIGHT equ 106

    %define FRAME_RATE 30

    buffer db 6042 dup(0x00)
    filehandle dw 0
    filename db "sprite.bin", 0

    open_msg db "Failed to open file!$"
    read_msg db "Failed to read file!$"

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
    ; Open file
    mov ah, 3Dh
    mov al, 0
    mov dx, filename
    int 21h
    jc open_failed         ; error handling
    mov [filehandle], ax

    mov ah, 3Fh
    mov bx, [filehandle]
    mov cx, SPRITE_WIDTH * SPRITE_HEIGHT
    mov dx, buffer
    int 21h
    jc read_failed         ; error handling

    mov ah, 3Eh
    mov bx, [filehandle]
    int 21h

    call clearScreen
    call positionSetup


gameLoop:
    call applyGravity
    call setViewport
    call displayViewport

    call waitForNextFrame  ; Delay for consistent frame timing

    jmp readKeyboard

; ----------------------------------------------
waitForNextFrame:
    push ax
    push bx
    push cx
    push dx

    mov ah, 0x00          ; Get current timer ticks
    int 0x1A
    mov bx, dx            ; Store current tick count

    .wait:
        int 0x1A              ; Get new timer ticks
        sub dx, bx            ; Check elapsed ticks
        cmp dx, 32 / FRAME_RATE  ; 18.2 ticks per second / FRAME_RATE
        jb .wait              ; Loop until enough time passes

        pop dx
        pop cx
        pop bx
        pop ax
        ret

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

open_failed:
    mov dx, open_msg
    call print_string
    jmp $

read_failed:
    mov dx, read_msg
    call print_string
    jmp $

; Reusable print_string function using int 21h/ah=09h
print_string:
    mov ah, 09h
    int 21h
    ret

exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h


%include "KeyboardInput.inc"
%include "Physic.inc"
%include "Display.inc"