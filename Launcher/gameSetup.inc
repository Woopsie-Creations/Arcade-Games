section .data
    sf_game_file dw 'Games/Street-Fighssembly/Bin/SF.com', 0
    ps_game_file dw 'Games/Pac-ssembly/Bin/PS.com', 0
    ps_game_file_actual_len db 28
    sf_game_file_actual_len db 35
    
    program_to_execute dw 0
    program_to_execute_len db 0

    current_game dw '', 0
    current_game_x_pos db 0
    current_game_y_pos db 0

    file_name db 'file.txt', 0

section .bss
    file_handle dw ?

section .text
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
        mov al, [ps_game_file_actual_len]
        mov byte [program_to_execute_len], al
        jmp execute_game

    sf_game_setup_execute:
        mov si, sf_game_file
        mov [program_to_execute], si
        mov al, [sf_game_file_actual_len]
        mov byte [program_to_execute_len], al
        jmp execute_game

    execute_game:
        ; Recreate file
        mov ah, 3ch
        mov cx, 0
        mov dx, file_name
        int 21h
        mov word [file_handle], ax

        ; Write onto file
        mov si, [program_to_execute]
        mov dx, si
        movzx cx, byte [program_to_execute_len]
        mov ah, 40h
        mov bx, [file_handle]
        int 21h

        ; Close file
        mov bx, [file_handle]
        mov ah, 3Eh
        int 21h

        jmp exitProgram

    ; -----------------------------------------------
    exitProgram:
        mov ah, 4Ch
        xor al, al
        int 21h