section .data:
    %define ESC_KEY 01h

    %define LEFT_ARROW 4Bh
    %define RIGHT_ARROW 4Dh
    %define ENTER_KEY 1Ch

    ps_game_file db 'Games/Pac-ssembly/Bin/PS.com', 0
    sf_game_file db 'Games/Street-Fighssembly/Bin/SF.com', 0
    program_to_execute_bytes db 35

    file_name db 'file.txt', 0

section .bss
    file_handle dw ?
    program_to_execute resw 1

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
        je change_current_game
        cmp ah, RIGHT_ARROW
        je change_current_game
        cmp ah, ENTER_KEY
        je choose_current_game
        ; je execute_game
        jmp checkForKeyPress

    change_current_game:
        mov ax, [current_game]
        mov bx, ps_game
        cmp ax, bx
        je sf_game_setup
        jmp ps_game_setup

    choose_current_game:
        mov ax, [current_game]
        mov bx, ps_game
        cmp ax, bx 
        je ps_game_setup_execute
        jmp sf_game_setup_execute

    ps_game_setup_execute:
        mov si, ps_game_file
        mov [program_to_execute], si
        jmp execute_game

    sf_game_setup_execute:
        mov si, sf_game_file
        mov [program_to_execute], si
        jmp execute_game

    execute_game:
        ; Execute from assembly hub
        ; mov ah, 4Bh
        ; mov al, 0
        ; lea dx, [program_to_execute]
        ; mov bx, 0
        ; int 21h ; Load and execute program

        ; Open (or create) the file
        mov ah, 3Ch
        mov cx, 0
        mov dx, file_name  
        int 21h

        mov [file_handle], ax

        ; Write to file
        mov bx, [file_handle]        
        mov ah, 40h ; Write file
        mov cx, program_to_execute_bytes
        mov dx, [program_to_execute]
        int 21h

        ; Close the file
        mov bx, [file_handle]
        mov ah, 3Eh ; Close file
        int 21h

        jmp exitProgram