section .data
    ; Sprite buffers for both players 
    buffer1 db 6042 dup(0x00)
    ; buffer2 db 6042 dup(0x00)
    filehandle dw 0

    ; Sprite files
    ryuIdle0 db "ryuIdle0.bin", 0
    ryuJump5 db "ryuJump5.bin", 0

    ; Debug error messages
    open_msg db "Failed to open file!$"
    read_msg db "Failed to read file!$"

section .bss
    ; For both players
    fileToLoad1: resw 1
    fileToLoad2: resw 1

section .text
    loadBuffer:
        ; ----- FIRST PLAYER -----
        ; Open file
        mov ah, 3Dh
        mov al, 0
        mov dx, [fileToLoad1] ; dynamically load a specific file
        int 21h
        jc openFailed ; error handling
        mov [filehandle], ax

        mov ah, 3Fh
        mov bx, [filehandle]
        mov cx, SPRITE_SIZE
        mov dx, buffer1
        int 21h
        jc readFailed ; error handling

        mov ah, 3Eh
        mov bx, [filehandle]
        int 21h

        ; ----- SECOND PLAYER -----
        ; Open file
        mov ah, 3Dh
        mov al, 0
        mov dx, [fileToLoad2] ; dynamically load a specific file
        int 21h
        jc openFailed ; error handling
        mov [filehandle], ax

        mov ah, 3Fh
        mov bx, [filehandle]
        mov cx, SPRITE_SIZE
        ; mov dx, buffer2
        mov dx, buffer1
        int 21h
        jc readFailed ; error handling

        mov ah, 3Eh
        mov bx, [filehandle]
        int 21h

        jmp gameLoop

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