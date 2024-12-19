org 100h

; -----------------------------------------------
section .data
    color db 0x28
    xpos dw 10
    ypos dw 10

; -----------------------------------------------
section .text
    ; set video mode
    mov ax, 13h
    int 10h
    jmp cyclePixelTest

; -----------------------------------------------
; Set a pixel value.
;   bl = x position
;   ax = y position
;   bh = palette index
setPixelValue:
    mov cx, 320
    mul cx
    mov cl, bh
    xor bh, bh
    add ax, bx
    mov di, ax
    mov bx, 0a000h
    mov es, bx
    mov [es:di] ,cl
    ret

; -----------------------------------------------
cyclePixelTest:
    call clearScreen
    mov bl, [xpos]  ; x
    mov ax, [ypos]  ; y
    mov bh, [color]  ; color
    call setPixelValue
    jmp readKeyboard

; CLEAR SCREEN ---------------------------------------------------------
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