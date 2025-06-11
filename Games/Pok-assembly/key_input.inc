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
    readKeyboard:
        ; is key pressed ?
        mov ah, 01h 
        int 16h
        jz gameLoop ; if no, skip

        ; which key is pressed
        mov ah, 00h
        int 16h

        cmp ah, ESCAPE_KEY
        je exitProgram
        
        cmp ah, LEFT_ARROW
        je changeTab_first
        cmp ah, RIGHT_ARROW
        je changeTab_first

        events first_trainerStruc, UP_ARROW

        cmp ah, A_KEY
        je changeTab_second
        cmp ah, D_KEY
        je changeTab_second
        
        events second_trainerStruc, W_KEY

        jmp gameLoop