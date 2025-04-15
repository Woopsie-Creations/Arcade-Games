section .text
    displayFrame:
        call printMaze
        call printPacman
        call drawPixel
        ret

    displayItem:
        ; calculate the position of the item
        mov ax, [item_y_pos]
        mov bx, 320
        mul bx
        add ax, [item_x_pos]
        mov di, ax
        ; draw the item
        mov dx, [item_height]
        .eachRow:
            mov cx, [item_width]
            .eachLine:
                lodsb
                cmp al, 0
                je .skipDraw
                stosb
                jmp .nextPixel
                .skipDraw:
                add di, 1
                .nextPixel:
                loop .eachLine
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
        mov word [item_width], PACMAN_WIDTH
        mov word [item_height], PACMAN_HEIGHT
        mov ax, [pacman_x_pos]
        mov word [item_x_pos], ax
        mov ax, [pacman_y_pos]
        mov word [item_y_pos], ax
        ; choose animation frame
        mov ax, [item+0]
        mov bx, PACMAN_WIDTH * PACMAN_HEIGHT
        mul bx
        mov si, pacman
        add si, ax
    
        call displayItem
        ret

    printMaze:
        ; set size and coordinates
        mov word [item_width], WALL_WIDTH
        mov word [item_height], WALL_HEIGHT
        mov word [item_x_pos], MAZE_X_POS
        mov word [item_y_pos], MAZE_Y_POS
        ; draw maze
        mov bx, maze
        mov dx, 0
        .eachMazeRow:
            push dx
            mov dx, 0
            .eachMazeColumn:
                push dx
                mov ax, [bx]
                push bx
                mov bx, WALL_WIDTH * WALL_HEIGHT
                mul bx
                mov si, walls
                add si, ax
                call displayItem
                add word [item_x_pos], WALL_WIDTH
                pop bx
                pop dx
                add bx, 2
                inc dx
                cmp dx, COLUMN_NUMBER
                jne .eachMazeColumn
            add word [item_y_pos], WALL_HEIGHT
            mov word [item_x_pos], MAZE_X_POS
            pop dx
            inc dx
            cmp dx, ROW_NUMBER
            jne .eachMazeRow
        ret

        drawPixel:
            mov word [item_width], 1
            mov word [item_height], 1
            mov ax, 2
            mov word [item_x_pos], ax
            mov ax, 2
            mov word [item_y_pos], ax

            ; yeay now funny part, first get the value we want from the memory block allocated
            mov es, [memory_block_pos] ; memory_block_pos being the thing used to save the pos in the memory of the memory block
            mov al, [es:0]
            mov byte [test_var], al ; then store the color somewhere (i used a variable, but i could use the stack, might also work)
            ; then set the es register to the correct pos of the video memory block (fixed, it cannot be something else)(or can it?)
            mov ax, 0xA000
            mov es, ax
            ; calculate the precise pos of the pixel we want to draw
            mov ax, [item_y_pos]
            mov bx, 320
            mul bx
            add ax, [item_x_pos]
            mov di, ax
            ; draw it :D
            mov al, [test_var] ; get the color back
            mov byte [es:di], al ; draw the pixel, es = memory block pos in the memory (set earlier), di = the pixel offset, al = the color
            ret