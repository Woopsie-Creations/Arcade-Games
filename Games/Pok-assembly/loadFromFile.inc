%macro loadBuffer 2
    ; Open file
    mov ah, 3Dh
    mov al, 0
    ; dx (containing the file to load) is assigned outside of the function
    int 21h
    jc openFailed ; error handling
    mov [filehandle], ax

    mov ah, 3Fh
    mov bx, [filehandle]
    mov cx, %2
    mov dx, %1
    int 21h
    jc readFailed ; error handling

    mov ah, 3Eh
    mov bx, [filehandle]
    int 21h
%endmacro

section .data
    ; Debug error messages
    open_msg db "Failed to open file!$"
    read_msg db "Failed to read file!$"

section .bss
    buffer1 resb BACK_SPRITE_SIZE
    buffer2 resb FRONT_SPRITE_SIZE
    filehandle resw 1

section .text
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