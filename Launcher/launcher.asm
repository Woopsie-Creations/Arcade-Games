org 100h

section .data
    welcome_to_message db 'Welcome to', 0
    welcome_to_message_x_pos db 7
    welcome_to_message_y_pos db 30

    arcade_launcher_message db 'GAME HUB', 0
    arcade_launcher_message_x_pos db 8
    arcade_launcher_message_y_pos db 32

section .bss
    message resw 1
    message_x_pos resb 1
    message_y_pos resb 1

section .text
    mov ax, 13h
    int 10h        

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

    mov ah, 4Dh
    int 10h

    call waitForKeyPress
    call exitProgram

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
waitForKeyPress:
    mov ah, 00h
    int 16h  ; Wait for key press
    ret

; -----------------------------------------------
exitProgram:
    mov ah, 4Ch
    xor al, al
    int 21h
