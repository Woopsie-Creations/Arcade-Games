section .data
    ps_game_file db 'Games/Pac-ssembly/Bin/PS.com', 0
    sf_game_file db 'Games/Street-Fighssembly/Bin/SF.com', 0
    program_to_execute_bytes db 35

    file_name db 'file.txt', 0

section .bss
    file_handle dw ?
    program_to_execute resw 1

    current_game resw 1
    current_game_x_pos resb 1
    current_game_y_pos resb 1

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
        jmp execute_game

    sf_game_setup_execute:
        mov si, sf_game_file
        mov [program_to_execute], si
        jmp execute_game

    execute_game:
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

    ; -----------------------------------------------
    exitProgram:
        mov ah, 4Ch
        xor al, al
        int 21h