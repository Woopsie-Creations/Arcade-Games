%macro applyKeyPress 4
    cmp word [pacmanStruc + entity.%1], %2
    je gameLoop

    mov word [pacmanStruc + entity.x_speed_buffer], %3
    mov word [pacmanStruc + entity.y_speed_buffer], %4
    mov byte [pacmanStruc + entity.movement_buffered], TRUE
    jmp gameLoop
%endmacro

%define LEFT_ARROW 4Bh
%define RIGHT_ARROW 4Dh
%define UP_ARROW 48h
%define DOWN_ARROW 50h

%define W_KEY 11h
%define A_KEY 1Eh
%define S_KEY 1Fh
%define D_KEY 20h

%define ESCAPE_KEY 01h
%define ENTER_KEY 1Ch

section .text
    pauseMenu:
        cmp ah, ESCAPE_KEY
        je waitForEnterPress
        ret

    waitForEnterPress:
        ; change display to 'press enter'
        mov byte [isPause], TRUE
        call displayFrame
        mov ah, 00h
        int 16h
        cmp ah, ESCAPE_KEY
        je exitProgram
        cmp ah, ENTER_KEY 
        jne waitForEnterPress
        ; change display to 'press esc'
        mov byte [isPause], FALSE
        ret
    
    readKeyboard:
        ; is key pressed ?
        mov ah, 01h 
        int 16h
        jz gameLoop ; if no, skip

        ; which key is pressed
        mov ah, 00h
        int 16h
        call pauseMenu
        
        cmp ah, UP_ARROW 
        je upKey
        cmp ah, RIGHT_ARROW
        je rightKey
        cmp ah, DOWN_ARROW
        je downKey
        cmp ah, LEFT_ARROW
        je leftKey
        
        jmp gameLoop

    upKey:
        applyKeyPress y_speed, -2, 0, -2

    rightKey:
        applyKeyPress x_speed, 2, 2, 0

    downKey:
        applyKeyPress y_speed, 2, 0, 2

    leftKey:
        applyKeyPress x_speed, -2, -2, 0