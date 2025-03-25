section .text
    displayFrame:
        call clearScreen
        call printPacman
        ret

    displayItem:
        ; calculate the position of the item
        mov ax, [item_y_pos]
        mov bx, 320
        mul bx
        add ax, [item_x_pos]
        mov di, ax
        add si, [item_frame_selection]

        ; draw the item
        mov dx, [item_height]
        .eachRow:
            mov cx, [item_width]
            .eachLine:
                rep movsb
            add di, 320
            sub di, [item_width]
            dec dx
            jnz .eachRow
        ret

    clearScreen:
        mov ax, 0xA000
        mov es, ax
        mov di, 0
        mov cx, 320*200
        rep stosb
        ret

    printPacman:
        ; set size and coordinates
        mov word [item_width], 10
        mov word [item_height], 10
        mov ax, [pacman_x_pos]
        mov word [item_x_pos], ax
        mov ax, [pacman_y_pos]
        mov word [item_y_pos], ax
        ; choose animation frame
        mov ax, [item+0]
        mov bx, 100
        mul bx
        mov [item_frame_selection], ax 
        mov si, pacman
    
        call displayItem
        ret

