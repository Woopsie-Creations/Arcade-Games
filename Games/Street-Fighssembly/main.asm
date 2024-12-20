org 100h


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

section .text
    ; set video mode
    mov ax, 13h
    int 10h
    jmp cyclePixelTest

; -----------------------------------------------
; Set a pixel value.
;   bx = x position
;   ax = y position
;   cx = palette index
setPixelValue:
    mov dx, 320
    mul dx
    add ax, bx
    mov di, ax
    mov bx, 0a000h
    mov es, bx
    mov [es:di], cl
    ret

; -----------------------------------------------
cyclePixelTest:
    call clearScreen
    mov bx, [x_pos_1]  ; x
    mov ax, [y_pos_1]  ; y
    mov cl, [color_1]  ; color
    call setPixelValue
    mov bx, [x_pos_2]  ; x
    mov ax, [y_pos_2]  ; y
    mov cl, [color_2]  ; color
    call setPixelValue
    jmp readKeyboard

; ---------------------------------------------------------
clearScreen:
    mov ax, 0xA000
    mov es, ax
    mov di, 0
    mov cx, 320*200
    rep stosb
    ret

exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h


%include "KeyboardInput.inc"