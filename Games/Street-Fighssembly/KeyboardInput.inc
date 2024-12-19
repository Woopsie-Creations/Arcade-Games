section .data
    %define LEFT_ARROW 4Bh
    %define RIGHT_ARROW 4Dh
    %define UP_ARROW 48h
    %define DOWN_ARROW 50h

    %define ESCAPE_KEY 01h

section .text
    readKeyboard:
        ; Read next key in buffer:
        mov ah, 00h 
        int 16h

        cmp ah, LEFT_ARROW
        je left
        cmp ah, RIGHT_ARROW
        je right
        cmp ah, UP_ARROW 
        je up 
        cmp ah, DOWN_ARROW
        je down
        cmp ah, ESCAPE_KEY
        je exitProgram
        jmp cyclePixelTest

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