section .text:
    ; -----------------------------------------------
    waitForKeyPress:
        mov ah, 00h
        int 16h  ; Wait for key press
        ret