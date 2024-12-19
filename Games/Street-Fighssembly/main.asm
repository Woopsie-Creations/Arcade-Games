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
    call readKeyboard
    jmp cyclePixelTest

; -----------------------------------------------
readKeyboard:
    ; Read next key in buffer:
    mov ah, 00h 
    int 16h

    cmp ah, 4Bh     ; left arrow key 
    je left
    cmp ah, 4Dh     ; right arrow key 
    je right
    cmp ah, 48h     ; up arrow key    
    je up 
    cmp ah, 50h     ; down arrow key
    je down
    ; Compare the input with ESCAPE
    cmp ah, 01h
    jne cyclePixelTest ; Loop while not "escape".

    jmp exitProgram

up:
    sub byte [ypos], 10
    jmp cyclePixelTest

left:
    sub byte [xpos], 10
    jmp cyclePixelTest

right:
    add byte [xpos], 10
    jmp cyclePixelTest

down:
    add byte [ypos], 10
    jmp cyclePixelTest

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
