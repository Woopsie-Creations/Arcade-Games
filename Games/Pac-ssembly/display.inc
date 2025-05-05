section .text
    initViewport:
        mov bx, 4000        ; nb of 16bytes sections we want to allocate
        ; interrupt
        mov ah, 48h
        int 21h
        ; if failed to allocate, exit
        jc exitProgram
        ; save the pos of the block allocated
        mov word [viewport_memory_block_pos], ax
        ret

    displayFrame:
        call clearViewport
        call printMaze
        call printGhosts
        call printPacman
        ; call drawPixel
        call displayViewport
        ret

    clearViewport:
        ; "select" the memory block allocated for the viewport
        mov ax, [viewport_memory_block_pos]
        mov es, ax
        ; set the position to the first pixel
        mov di, 0
        .clearEachPixels:
            ; set the pixel selected to black
            mov byte [es:di], 0x00
            ; loop until it has done every pixels
            inc di
            cmp di, SCREEN_HEIGHT * SCREEN_WIDTH
            jne .clearEachPixels
        ret

    displayViewport:
        ; set the position to the first pixel
        mov di, 0
        .eachPixel:
            ; go to the memory block for the viewport to then take the colour of the selected pixel of the viewport
            mov ax, [viewport_memory_block_pos]
            mov es, ax
            xor ax, ax  ; clear the register ax because we will only use the lower part (al) for the colour
            mov al, [es:di]
            push ax     ; then save the colour
            ; then go the memory block for the screen, retrieve the colour and place it (same pixel position as the viewport because they have the same size)
            mov ax, 0xA000
            mov es, ax
            pop ax
            mov byte [es:di], al
            ; loop until it has done every pixels
            inc di
            cmp di, SCREEN_HEIGHT * SCREEN_WIDTH
            jne .eachPixel
        ret

    displayItem:
        ; "select" the memory block allocated for the viewport
        mov ax, [viewport_memory_block_pos]
        mov es, ax
        ; calculate the position of the item
        mov ax, [item_y_pos]
        mov bx, 320
        mul bx
        add ax, [item_x_pos]
        mov di, ax
        ; draw the item
        mov dx, [item_height]
        .eachItemRow:
            mov cx, [item_width]
            .eachItemColumn:
                xor ax, ax
                ; get the colour of the sprite at said position in the memory by the register si
                mov al, [si]
                cmp al, 0x00
                je .skipTransparent      ; skip the colour placement if transparent
                mov byte [es:di], al     ; place the pixel on the viewport
                .skipTransparent:
                ; go to the next pixel
                add si, 1
                inc di
                ; if it hasn't reached the end of the line, loop
                dec cx
                jnz .eachItemColumn
            ; go to the next row
            add di, SCREEN_WIDTH
            sub di, [item_width]
            ; if it hasn't reached the last row, loop
            dec dx
            jnz .eachItemRow
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

    printGhosts:
        mov cx, 4 ; 4 ghosts
        .eachGhost:
            ; manipulate cx (-1 and *2) to have a word index
            mov bx, cx
            dec bx
            shl bx, 1

            ; set size and coordinates
            mov word [item_width], GHOST_WIDTH
            mov word [item_height], GHOST_HEIGHT
            mov ax, [ghost_x_pos+bx]
            mov word [item_x_pos], ax
            mov ax, [ghost_y_pos+bx]
            mov word [item_y_pos], ax
            ; choose animation frame
            push bx ; save word index
            mov bx, cx ; get byte index
            inc bx
            mov al, [item+bx]
            xor ah, ah ; make sure we read only 1 byte of item

            mov bx, GHOST_WIDTH * GHOST_HEIGHT
            mul bx
            pop bx ; get back word index

            mov si, [ghost_sprite+bx]
            add si, ax

            push cx
            call displayItem
            pop cx
            loop .eachGhost
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
                xor ax, ax
                mov al, [bx]
                push bx
                mov bx, WALL_WIDTH * WALL_HEIGHT
                mul bx
                mov si, walls
                add si, ax
                call displayItem
                add word [item_x_pos], WALL_WIDTH
                pop bx
                pop dx
                inc bx
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

        ; testing purpose
        drawPixel:
            mov word [item_width], 1
            mov word [item_height], 1
            mov ax, 2
            mov word [item_x_pos], ax
            mov ax, 2
            ret