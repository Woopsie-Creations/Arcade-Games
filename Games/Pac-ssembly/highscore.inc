section .text
    getHighScore:
        call openFile
        call readFile
        call closeFile
        ret

    compareScores:
        mov si, current_score
        mov di, high_score
        mov cx, 7

        .compare_loop:
            mov al, [si]
            mov bl, [di]
            cmp al, bl
            ; if current_score > high_score, then update high_score
            ja updateHighscore
            ; if not equal, we skip because we already know current_score < high_score
            jb .early

            inc si
            inc di
            loop .compare_loop
            .early:
            ret

    updateHighscore:
        ; update high_score
        mov si, current_score
        mov di, high_score
        mov cx, 7
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
        jc exitProgram ; error handling
        mov word [hscore_file_handle], ax ; ax contains the file handle
        ret

    writeFile:
        digits_to_ascii high_score
        mov bx, [hscore_file_handle]
        mov dx, high_score ; the buffer containing the content to write
        mov cx, 7 ; the number of bytes to write
        mov ah, 40h
        int 21h
        jc exitProgram ; error handling
        ascii_to_digits high_score
        ret

    readFile:
        mov bx, [hscore_file_handle]
        mov dx, high_score ; buffer to contain read content
        mov cx, 7 ; number of bytes to read
        mov ah, 3fh
        int 21h
        jc exitProgram ; error handling
        ascii_to_digits high_score
        ret

    closeFile:
        mov bx, [hscore_file_handle]
        mov ah, 3eh
        int 21h
        jc exitProgram ; error handling
        ret