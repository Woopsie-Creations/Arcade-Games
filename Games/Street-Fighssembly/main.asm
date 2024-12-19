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
;   ax = x position
;   bl = y position
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
    mov ax, [xpos]  ; x
    mov bl, [ypos]  ; y
    mov bh, [color]  ; color
    call setPixelValue
    jmp cyclePixelTest
