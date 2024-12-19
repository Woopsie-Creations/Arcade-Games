; --------------------------------------------------
; Keyboard input handling. 
; Each key used are listed in section .data.
; --------------------------------------------------

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
        ; Read next key in buffer:
        mov ah, 00h 
        int 16h

        cmp ah, LEFT_ARROW
        je left1
        cmp ah, RIGHT_ARROW
        je right1
        cmp ah, UP_ARROW 
        je up1
        cmp ah, DOWN_ARROW
        je down1

        cmp ah, A_KEY
        je left2
        cmp ah, D_KEY
        je right2
        cmp ah, W_KEY 
        je up2
        cmp ah, S_KEY
        je down2

        cmp ah, ESCAPE_KEY
        je exitProgram
        jmp cyclePixelTest

    ; ------------------------
    up1:
        sub byte [y_pos_1], 10
        jmp cyclePixelTest
    
    left1:
        sub byte [x_pos_1], 10
        jmp cyclePixelTest
    
    right1:
        add byte [x_pos_1], 10
        jmp cyclePixelTest
    
    down1:
        add byte [y_pos_1], 10
        jmp cyclePixelTest

    up2:
        sub byte [y_pos_2], 10
        jmp cyclePixelTest
    
    left2:
        sub byte [x_pos_2], 10
        jmp cyclePixelTest
    
    right2:
        add byte [x_pos_2], 10
        jmp cyclePixelTest
    
    down2:
        add byte [y_pos_2], 10
        jmp cyclePixelTest