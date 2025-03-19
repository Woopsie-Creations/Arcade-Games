section .bss
    message resw 1
    message_x_pos resb 1
    message_y_pos resb 1

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
        mov bl, 0x03
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
        call printMessage

        ; Load second message
        mov si, arcade_launcher_message
        mov [message], si
        mov al, [arcade_launcher_message_x_pos]
        mov [message_x_pos], al
        mov al, [arcade_launcher_message_y_pos]
        mov [message_y_pos], al
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
        sub al, 6
        mov [message_y_pos], al
        call printMessage

        ; That's where the magic should be displayed
        call waitForKeyPress ; placeholder
        ret

%include "input.inc"