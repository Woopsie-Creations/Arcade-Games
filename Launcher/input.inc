section .data:
    %define ESC_KEY 01h

    %define LEFT_ARROW 4Bh
    %define RIGHT_ARROW 4Dh

section .bss

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
        
        cmp ah, ESC_KEY
        je exitProgram
        cmp ah, LEFT_ARROW
        je check_current_game
        cmp ah, RIGHT_ARROW
        je check_current_game
        jmp checkForKeyPress

    check_current_game:
        mov ax, [current_game]
        mov bx, ps_game
        cmp ax, bx
        je sf_game_setup
        jmp ps_game_setup