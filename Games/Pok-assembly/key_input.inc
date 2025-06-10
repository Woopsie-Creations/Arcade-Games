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
        
        ; testing purposes
        cmp ah, LEFT_ARROW
        je changePoke_first
        cmp ah, RIGHT_ARROW
        je changePoke_first
        cmp ah, UP_ARROW
        je hit_second

        ; testing purposes
        cmp ah, A_KEY
        je changePoke_second
        cmp ah, D_KEY
        je changePoke_second
        cmp ah, W_KEY
        je hit_first
        
        jmp gameLoop