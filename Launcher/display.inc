section .data
    welcome_to_message db 'Welcome to', 0
    welcome_to_message_x_pos db 7
    welcome_to_message_y_pos db 37

    arcade_launcher_message db 'GAME HUB', 0
    arcade_launcher_message_x_pos db 8
    arcade_launcher_message_y_pos db 39

    arrow_left db '<', 0
    arrow_left_x_pos db 0
    arrow_left_y_pos db 38

    arrow_right db '>', 0
    arrow_right_x_pos db 23
    arrow_right_y_pos db 38

    ps_game db 'Pacssembly', 0
    ps_game_x_pos db 7
    ps_game_y_pos db 38

    sf_game db 'Street-Fighssembly', 0
    sf_game_x_pos db 3
    sf_game_y_pos db 38

    press_enter_message db 'Press  ENTER', 0
    press_enter_message_x_pos db 6
    press_enter_message_y_pos db 45

section .bss
    message resw 1
    message_x_pos resb 1
    message_y_pos resb 1
    message_color resb 1

section .text
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
    titleScreen:
        call clearScreen

        ; Load first message
        mov si, welcome_to_message
        mov [message], si
        mov al, [welcome_to_message_x_pos]
        mov [message_x_pos], al
        mov al, [welcome_to_message_y_pos]
        mov [message_y_pos], al
        mov al, 0x2E
        mov [message_color], al
        call printMessage

        ; Load second message
        mov si, arcade_launcher_message
        mov [message], si
        mov al, [arcade_launcher_message_x_pos]
        mov [message_x_pos], al
        mov al, [arcade_launcher_message_y_pos]
        mov [message_y_pos], al
        mov al, 0x21
        mov [message_color], al
        call printMessage

        call waitForKeyPress
        ret

    ; -----------------------------------------------
    mainMenu:
        call clearScreen

        mov si, arcade_launcher_message
        mov [message], si
        mov al, [arcade_launcher_message_x_pos]
        mov [message_x_pos], al
        mov al, [arcade_launcher_message_y_pos]
        sub al, 8 ; Put it to the top
        mov [message_y_pos], al
        mov al, 0x2E
        mov [message_color], al
        call printMessage

        mov si, arrow_left
        mov [message], si
        mov al, [arrow_left_x_pos]
        mov [message_x_pos], al
        mov al, [arrow_left_y_pos]
        mov [message_y_pos], al
        mov al, 0x2E
        mov [message_color], al
        call printMessage

        mov si, arrow_right
        mov [message], si
        mov al, [arrow_right_x_pos]
        mov [message_x_pos], al
        mov al, [arrow_right_y_pos]
        mov [message_y_pos], al
        mov al, 0x2E
        mov [message_color], al
        call printMessage

        mov si, press_enter_message
        mov [message], si
        mov al, [press_enter_message_x_pos]
        mov [message_x_pos], al
        mov al, [press_enter_message_y_pos]
        mov [message_y_pos], al
        mov al, 0x0F
        mov [message_color], al
        call printMessage

        mov si, [current_game]
        mov [message], si
        mov al, [current_game_x_pos]
        mov [message_x_pos], al
        mov al, [current_game_y_pos]
        mov [message_y_pos], al
        mov al, 0x21
        mov [message_color], al
        call printMessage

        call checkForKeyPress

    ps_game_setup:
        mov si, ps_game
        mov al, [ps_game_x_pos]
        mov bl, [ps_game_y_pos]
        jmp set_current_game
    sf_game_setup:
        mov si, sf_game
        mov al, [sf_game_x_pos]
        mov bl, [sf_game_y_pos]
        jmp set_current_game

    set_current_game:
        mov [current_game], si
        mov [current_game_x_pos], al
        mov [current_game_y_pos], bl
        jmp mainMenu

%include "input.inc"