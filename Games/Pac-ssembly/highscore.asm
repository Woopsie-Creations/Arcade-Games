org 100h

%macro ascii_to_digits 1
    mov si, %1
    mov cx, 6
    .to_digit_loop:
        mov al, [si]
        sub al, '0'
        mov [si], al
        inc si
        loop .to_digit_loop
%endmacro

%macro digits_to_ascii 1
    mov si, %1
    mov cx, 6
    .to_ascii_loop:
        mov al, [si]
        add al, '0'
        mov [si], al
        inc si
        loop .to_ascii_loop
%endmacro

%macro updateScore 1
    ; increment number in ax
    ; if number too big:
    ;   - dx = hundred thousand digits 
    ;   - cx = ten thousand digits 
    ; else dx AND cx should be = 0
    mov ax, %1
    cmp dx, 1
    jae .hundredthousands
    cmp cx, 1
    jae .tenthousands
    cmp ax, 100
    jb .tens
    cmp ax, 1000
    jb .hundreds
    cmp ax, 10000
    jb .thousands

    .hundredthousands:
        inc byte [current_score]
        dec dx
        cmp dx, 1
        jae .hundredthousands

    .tenthousands:
        inc byte [current_score+1]
        dec cx
        cmp cx, 1
        jae .tenthousands

    .thousands:
        inc byte [current_score+2]
        sub ax, 1000
        cmp ax, 1000
        jae .thousands

    .hundreds:
        inc byte [current_score+3]
        sub ax, 100
        cmp ax, 100
        jae .hundreds

    .tens:
        inc byte [current_score+4]
        sub ax, 10
        cmp ax, 0
        jne .tens
    .end:
%endmacro

section .data
    current_score times 6 db 0
    high_score times 6 db 0
    high_score_file db "hscore.bin", 0

section .bss
    file_handle resw 1
    
section .text
    start:
        mov dx, 6
        mov cx, 9
        updateScore 6990
        
        ; get high_score from file
        call getHighScore
        ; then compare it with current_score
        call compareScores

        jmp exit
    
    getHighScore:
        call openFile
        call readFile
        call closeFile
        ret

    compareScores:
        mov si, current_score
        mov di, high_score
        mov cx, 6

        .compare_loop:
            mov al, [si]
            mov bl, [di]
            cmp al, bl
            ; if current_score > high_score, then update high_score
            ja updateHighscore

            inc si
            inc di
            loop .compare_loop
            ret

    updateHighscore:
        ; update high_score
        mov si, current_score
        mov di, high_score
        mov cx, 6
        .update_loop:
            mov al, [si]
            mov bl, al
            mov [di], bl

            inc si
            inc di
            loop .update_loop

        ; and update the file
        call openFile
        call writeFile
        call closeFile

        ret

    openFile:
        mov dx, high_score_file
        mov ah, 3dh
        mov al, 2
        int 21h
        jc exit ; error handling
        mov word [file_handle], ax ; ax contains the file handle
        ret

    writeFile:
        digits_to_ascii high_score
        mov bx, [file_handle]
        mov dx, high_score ; the buffer containing the content to write
        mov cx, 6 ; the number of bytes to write
        mov ah, 40h
        int 21h
        jc exit ; error handling
        ascii_to_digits high_score
        ret

    readFile:
        mov bx, [file_handle]
        mov dx, high_score ; buffer to contain read content
        mov cx, 6 ; number of bytes to read
        mov ah, 3fh
        int 21h
        jc exit ; error handling
        ascii_to_digits high_score
        ret

    closeFile:
        mov bx, [file_handle]
        mov ah, 3eh
        int 21h
        jc exit ; error handling
        ret

    exit:
        mov ah, 4ch
        int 21h
