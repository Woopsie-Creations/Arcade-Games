%macro applyKeyPress 4
    cmp byte [%1], %2
    je gameLoop

    mov word [pacman_x_speed_buffer], %3
    mov word [pacman_y_speed_buffer], %4
    jmp gameLoop
%endmacro

section .data
    %define LEFT_ARROW 4Bh
    %define RIGHT_ARROW 4Dh
    %define UP_ARROW 48h
    %define DOWN_ARROW 50h

    %define W_KEY 11h
    %define A_KEY 1Eh
    %define S_KEY 1Fh
    %define D_KEY 20h

    %define ESCAPE_KEY 01h

section .text
    readKeyboard:
        ; is key pressed ?
        mov ah, 01h 
        int 16h
        jz gameLoop ; if no, skip

        ; which key is pressed
        mov ah, 00h
        int 16h
        cmp ah, UP_ARROW 
        je upKey
        cmp ah, RIGHT_ARROW
        je rightKey
        cmp ah, DOWN_ARROW
        je downKey
        cmp ah, LEFT_ARROW
        je leftKey

        cmp ah, ESCAPE_KEY
        je exitProgram
        jmp gameLoop

    upKey:
        applyKeyPress pacman_y_speed, -2, 0, -2
        mov byte [item+0], 1
        mov byte [pacman_animation_frame], 0

    rightKey:
        applyKeyPress pacman_x_speed, 2, 2, 0
        mov byte [item+0], 3
        mov byte [pacman_animation_frame], 0

    downKey:
        applyKeyPress pacman_y_speed, 2, 0, 2
        mov byte [item+0], 5
        mov byte [pacman_animation_frame], 0

    leftKey:
        applyKeyPress pacman_x_speed, -2, -2, 0
        mov byte [item+0], 7
        mov byte [pacman_animation_frame], 0
