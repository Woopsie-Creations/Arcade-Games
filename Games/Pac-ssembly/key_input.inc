%macro applyKeyPress 6
    cmp word [%1Struc + entity.%2], %3
    je gameLoop

    mov word [%1Struc + entity.x_speed_buffer], %4
    mov word [%1Struc + entity.y_speed_buffer], %5
    mov byte [%1Struc + entity.movement_buffered], TRUE
    jmp %6
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
        je mainmenu
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

        cmp byte [current_mode], 0
        je .firstPlayer

        ; second player
        cmp ah, W_KEY 
        je wKey
        cmp ah, D_KEY
        je dKey
        cmp ah, S_KEY
        je sKey
        cmp ah, A_KEY
        je aKey
        
        .firstPlayer:
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
        applyKeyPress pacman, y_speed, -2, 0, -2, gameLoop

    rightKey:
        applyKeyPress pacman, x_speed, 2, 2, 0, gameLoop

    downKey:
        applyKeyPress pacman, y_speed, 2, 0, 2, gameLoop

    leftKey:
        applyKeyPress pacman, x_speed, -2, -2, 0, gameLoop

    wKey:
        cmp word [blinkyStruc + entity.y_speed], 2
        je readKeyboard.firstPlayer
        applyKeyPress blinky, y_speed, -2, 0, -2, readKeyboard.firstPlayer

    dKey:
        cmp word [blinkyStruc + entity.x_speed], -2
        je readKeyboard.firstPlayer
        applyKeyPress blinky, x_speed, 2, 2, 0, readKeyboard.firstPlayer

    sKey:
        cmp word [blinkyStruc + entity.y_speed], -2
        je readKeyboard.firstPlayer
        applyKeyPress blinky, y_speed, 2, 0, 2, readKeyboard.firstPlayer

    aKey:
        cmp word [blinkyStruc + entity.x_speed], 2
        je readKeyboard.firstPlayer
        applyKeyPress blinky, x_speed, -2, -2, 0, readKeyboard.firstPlayer
