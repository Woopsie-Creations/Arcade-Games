section .data:
    %define ESC_KEY 01h

    %define LEFT_ARROW 4Bh
    %define RIGHT_ARROW 4Dh
    %define ENTER_KEY 1Ch

section .text:
    ; -----------------------------------------------
    waitForKeyPress:
        mov ah, 00h
        int 16h  ; Wait for key press
        ret

    ; -----------------------------------------------
    checkForKeyPress:
        ; which key is pressed
        mov ah, 00h
        int 16h
        
        cmp ah, LEFT_ARROW
        je change_current_game
        cmp ah, RIGHT_ARROW
        je change_current_game
        cmp ah, ENTER_KEY
        je choose_current_game
        jmp checkForKeyPress

%include "gameSetup.inc"