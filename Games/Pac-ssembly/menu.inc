%macro loadMessage 4
    mov si, %1
    mov [message], si
    mov al, %2
    mov [message_x_pos], al
    mov al, %3
    mov [message_y_pos], al
    mov al, %4
    mov [message_color], al
    call printMessage 
%endmacro

section .data
    pacssembly_message db 'Pac-ssembly', 0
    pacssembly_message_x_pos db 7
    pacssembly_message_y_pos db 35

    key_action_message_ret db 'RET to play', 0
    key_action_message_ret_x_pos db 8
    key_action_message_ret_y_pos db 39

    key_action_message_esc db 'ESC to exit', 0
    key_action_message_esc_x_pos db 20
    key_action_message_esc_y_pos db 47

    one_player_mode_message db '1P', 0
    one_player_mode_message_x_pos db 12
    one_player_mode_message_y_pos db 42

    two_player_mode_message db '2P', 0
    two_player_mode_message_x_pos db 12
    two_player_mode_message_y_pos db 44

section .bss
    message resw 1
    message_x_pos resb 1
    message_y_pos resb 1
    message_color resb 1

section .text
    mainmenu:
        call placeEntities
        call displayEntities
        loadMessage pacssembly_message, [pacssembly_message_x_pos], [pacssembly_message_y_pos], 0x2C
        loadMessage one_player_mode_message, [one_player_mode_message_x_pos], [one_player_mode_message_y_pos], 0x0F
        loadMessage two_player_mode_message, [two_player_mode_message_x_pos], [two_player_mode_message_y_pos], 0x0F
        loadMessage key_action_message_esc, [key_action_message_esc_x_pos], [key_action_message_esc_y_pos], 0x0F

        call waitForMenuKeyPress
        ret

    placeEntities:
        call initLevel
        cmp byte [current_mode], 1
        je .placeFor2P
        sub word [pacmanStruc + entity.y_pos], 7
        jmp .next

        .placeFor2P:
        add word [pacmanStruc + entity.y_pos], 7

        .next:
        sub word [pacmanStruc + entity.x_pos], 20
        inc word [blinkyStruc + entity.x_pos]
        add word [pinkyStruc + entity.y_pos], 3
        add word [inkyStruc + entity.y_pos], 3
        add word [clydeStruc + entity.y_pos], 3
        ret

    displayEntities:
        call clearViewport
        printEntities
        mov si, topleft
        displayItem TITLE_Y_POS, TITLE_X_POS, TITLE_HEIGHT, TITLE_WIDTH
        mov si, topright
        displayItem TEAM_Y_POS, TEAM_X_POS, TEAM_HEIGHT, TEAM_WIDTH
        mov si, smalWoopsie
        displayItem SMAL_WOOPSIE_Y_POS, SMAL_WOOPSIE_X_POS, SMAL_WOOPSIE_HEIGHT, SMAL_WOOPSIE_WIDTH
        call displayViewport 
        ret

    ; -----------------------------------------------
    clearScreen:
        mov ax, 0xA000
        mov es, ax
        mov di, 0
        mov al, 0x00
        mov cx, 320*200
        rep stosb
        ret

    ; -----------------------------------------------
    printMessage:
        ; Set position
        mov ah, 02h
        mov bh, 0
        mov dh, [message_y_pos]
        mov dl, [message_x_pos]
        int 10h

        ; Print string
        mov ah, 0x0E
        mov bh, 0x00
        mov bl, [message_color]
        mov si, [message]
        .printLoop:
            lodsb
            or al, al
            int 10h
            jnz .printLoop
            ret

    ; -----------------------------------------------
    waitForMenuKeyPress:
        mov ah, 00h
        int 16h
        cmp ah, 01h
        je exitProgram
        cmp ah, 1Ch
        je enterGameMode
        cmp ah, 48h
        je changeCurrentMode
        cmp ah, 50h 
        je changeCurrentMode
        jmp waitForMenuKeyPress

    ; -----------------------------------------------
    enterGameMode:
        jmp initFromMenu

    changeCurrentMode:
        ; change current mode
        cmp byte [current_mode], 0
        je .moveTo2P
        dec byte [current_mode]
        jmp mainmenu
        .moveTo2P:
        inc byte [current_mode]
        jmp mainmenu