org 100h


%macro setPixelPosition 2
    mov bx, %1  ; x
    mov ax, %2  ; y
    mov si, sprite
    drawSprite %1, %2
%endmacro

%macro clearOldPosition 2
    mov bx, %1 ; x
    mov ax, %2 ; y
    mov si, backgroundSpriteData
    drawSprite %1, %2
%endmacro

%macro drawSprite 2
    mov ax, %2       
    mov bx, 320            
    mul bx                 
    add ax, %1
    mov di, ax

    mov dx, SPRITE_HEIGHT ; sprite drawing loop
    call eachLine
%endmacro


section .data
    ; constant initialization
    %define WINDOW_TOP_BORDER 10
    %define WINDOW_LEFT_BORDER 10
    %define WINDOW_RIGHT_BORDER 310
    %define WINDOW_DOWN_BORDER 190

    delay_waitloop dw 2000

    %define INIT_X_POS_1 11
    %define INIT_X_POS_2 240
    %define INIT_Y_POS_1 100
    %define INIT_Y_POS_2 100

    %define SPRITE_WIDTH 64
    %define SPRITE_HEIGHT 92
    backgroundSpriteData db 64 * 92 dup(00h)

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
    setPixelPosition [x_pos_1], [y_pos_1]
    setPixelPosition [x_pos_2], [y_pos_2]

gameLoop:
    call applyGravity1
    call applyGravity2
    jmp readKeyboard

; -------------------------
eachLine:
    mov cx, SPRITE_WIDTH
    rep movsb
    add di, 320 - SPRITE_WIDTH
    dec dx
    jnz eachLine
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

exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h


%include "KeyboardInput.inc"
%include "Physic.inc"
%include "sprite.inc"