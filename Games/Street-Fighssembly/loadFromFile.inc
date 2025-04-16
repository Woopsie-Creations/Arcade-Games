section .data
    ; Sprite files (paths)
    ryuIdle0 db "ryuIdle0.bin", 0
    ryuJump5 db "ryuJump5.bin", 0

    ; Debug error messages
    open_msg db "Failed to open file!$"
    read_msg db "Failed to read file!$"

section .bss
    buffer resb SPRITE_SIZE
    filehandle resw 1
    ; For both players
    player_current_sprite1: resw 1
    player_current_sprite2: resw 1

section .text
    loadBuffer:
        ; Open file
        mov ah, 3Dh
        mov al, 0
        ; dx (containing the file to load) is assigned outside of the function
        int 21h
        jc openFailed ; error handling
        mov [filehandle], ax

        mov ah, 3Fh
        mov bx, [filehandle]
        mov cx, SPRITE_SIZE
        mov dx, buffer
        int 21h
        jc readFailed ; error handling

        mov ah, 3Eh
        mov bx, [filehandle]
        int 21h

        ret

    openFailed:
        mov dx, open_msg
        call printString
        jmp $

    readFailed:
        mov dx, read_msg
        call printString
        jmp $

    ; Reusable printString function for error handling purposes
    printString:
        mov ah, 09h
        int 21h
        ret