org 100h


%macro setPixelPosition 3
    mov bx, %1  ; x
    mov ax, %2  ; y
    mov cl, %3  ; color
    call drawPixel
%endmacro

%macro clearOldPosition 2
    mov bx, %1  ; x
    mov ax, %2  ; y
    mov cl, 00h  ; color
    call drawPixel
%endmacro


section .data
    color_1 db 0x28
    x_pos_1 dw 10
    y_pos_1 dw 10

    color_2 db 0x2F
    x_pos_2 dw 20
    y_pos_2 dw 20

    %define WINDOW_TOP_BORDER 10
    %define WINDOW_LEFT_BORDER 10
    %define WINDOW_RIGHT_BORDER 310
    %define WINDOW_DOWN_BORDER 190

    delay_waitloop dw 1000

section .text
    ; set video mode
    mov ax, 13h
    int 10h
    call clearScreen
    jmp init

; -----------------------------------------------
; Set a pixel value.
;   bx = x position
;   ax = y position
;   cx = palette index
drawPixel:
    mov dx, 320
    mul dx
    add ax, bx
    mov di, ax
    mov bx, 0a000h
    mov es, bx
    mov [es:di], cl
    ret

; -----------------------------------------------
init:
    setPixelPosition [x_pos_1], [y_pos_1], [color_1]
    setPixelPosition [x_pos_2], [y_pos_2], [color_2]

gameLoop:
    ; call applyGravity
    jmp readKeyboard

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

exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h


%include "KeyboardInput.inc"
%include "Physic.inc"