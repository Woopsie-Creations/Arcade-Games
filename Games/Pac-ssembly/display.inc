%macro displayItem  4
    %define %%item_x_pos %2
    %define %%item_y_pos %1

    mov ax, [viewport_memory_block_pos]
    mov es, ax
    ; calculate the position of the item
    mov ax, %%item_y_pos
    mov bx, 320
    mul bx
    add ax, %%item_x_pos
    mov di, ax
    ; draw the item
    mov dx, %3 ;[item_height]
    %%eachItemRow:
        mov cx, %4 ;[item_width]
        %%eachItemColumn:
            xor ax, ax
            ; get the colour of the sprite at said position in the memory by the register si
            mov al, [si]
            cmp al, 0x00
            je %%skipTransparent      ; skip the colour placement if transparent
            mov byte [es:di], al     ; place the pixel on the viewport
            %%skipTransparent:
            ; go to the next pixel
            add si, 1
            inc di
            ; if it hasn't reached the end of the line, loop
            dec cx
            jnz %%eachItemColumn
        ; go to the next row
        add di, SCREEN_WIDTH
        sub di, %4 ;[item_width]
        ; if it hasn't reached the last row, loop
        dec dx
        jnz %%eachItemRow
%endmacro

%macro textDisplay 6
    mov word [letter_x_pos], %4
    mov word [letter_y_pos], %3
    mov bx, 0
        .eachLetter:
        mov si, [%1+bx]
        push bx
        displayItem [letter_y_pos], [letter_x_pos], %5, %6
        pop bx
        add word [letter_x_pos], %6 + 1
        add bx, 2
        cmp bx, %2 * 2
        jne .eachLetter
%endmacro

%macro placeFruitBox 3
    cmp byte [current_fruit_case_index], %1
    je %%updateFruitBox
    jmp %%skip
    %%updateFruitBox:
        push si
        mov si, selectfruitBox
        displayItem %2-2, %3-2, SELECT_FRUIT_BOX_HEIGHT, SELECT_FRUIT_BOX_WIDTH
        pop si
    %%skip:
%endmacro

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
        call spawnCurrentFruit
        call printGhosts
        call printPacman
        call printUI
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

    printPacman:
        ; choose animation frame
        mov ax, [item+0]
        mov bx, PACMAN_WIDTH * PACMAN_HEIGHT
        mul bx
        mov si, pacman
        add si, ax
    
        displayItem [pacman_y_pos], [pacman_x_pos], PACMAN_HEIGHT, PACMAN_WIDTH
        ret

    printGhosts:
        mov cx, 4 ; 4 ghosts
        .eachGhost:
            ; choose animation frame
            mov bx, cx ; get byte index
            inc bx
            mov al, [item+bx]
            xor ah, ah ; make sure we read only 1 byte of item

            mov bx, GHOST_WIDTH * GHOST_HEIGHT
            mul bx
            
            mov bx, cx
            dec bx
            shl bx, 1

            mov si, [ghost_sprite+bx]
            add si, ax

            mov di, bx
            push cx
            displayItem [ghost_y_pos+di], [ghost_x_pos+di], GHOST_HEIGHT, GHOST_WIDTH
            pop cx
            loop .eachGhost
        ret

    printMaze:
        ; init coordinates
        mov word [wall_x_pos], MAZE_X_POS
        mov word [wall_y_pos], MAZE_Y_POS
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
                displayItem [wall_y_pos], [wall_x_pos], WALL_HEIGHT, WALL_WIDTH
                add word [wall_x_pos], WALL_WIDTH
                pop bx
                pop dx
                inc bx
                inc dx
                cmp dx, COLUMN_NUMBER
                jne .eachMazeColumn
            add word [wall_y_pos], WALL_HEIGHT
            mov word [wall_x_pos], MAZE_X_POS
            pop dx
            inc dx
            cmp dx, ROW_NUMBER
            jne .eachMazeRow
        ret

    spawnCurrentFruit:
        cmp byte [fruit_should_be_displayed], 1
        je .spawn
        ret
        .spawn:
            mov ax, 99
            mov bx, [current_fruit_case_index]
            mul bx
            mov si, fruits
            add si, ax
            displayItem FRUIT_SPAWN_Y_POS, FRUIT_SPAWN_X_POS, FRUIT_HEIGHT, FRUIT_WIDTH
        ret

    printUI:
        gameTitle:
            mov si, topleft
            displayItem TITLE_Y_POS, TITLE_X_POS, TITLE_HEIGHT, TITLE_WIDTH
        team:
            mov si, topright
            displayItem TEAM_Y_POS, TEAM_X_POS, TEAM_HEIGHT, TEAM_WIDTH
        printScoreText:
            mov si, scoreTitle
            displayItem SCORE_TEXT_Y_POS, SCORE_TEXT_X_POS, SCORE_TEXT_TITLE_HEIGHT, SCORE_TEXT_TITLE_WIDTH
        printScoreBox:
            mov si, scoreNumberBox
            displayItem SCORE_BOX_Y_POS, SCORE_BOX_X_POS, SCORE_TEXT_TITLE_HEIGHT, SCORE_BOX_WIDTH
        printScore:
            call updateDisplayedScore
            textDisplay displayedNumbers, 9, SCORE_BOX_Y_POS+2, SCORE_BOX_X_POS+2, FONT_HEIGHT, FONT_WIDTH
        printFruitTitle:
            mov si, fruitTitle
            displayItem FRUIT_TITLE_Y_POS, FRUIT_TITLE_X_POS, FRUIT_TITLE_HEIGHT, FRUIT_TITLE_WIDTH
        printFruits:
            %assign current_fruit_y_pos FRUIT_BANK_Y_POS
            %assign current_fruit_x_pos FRUIT_BANK_X_POS
            mov si, fruits
            %assign current_fruit_index 0
            %rep 8
                placeFruitBox current_fruit_index, current_fruit_y_pos, current_fruit_x_pos
                displayItem current_fruit_y_pos, current_fruit_x_pos, FRUIT_HEIGHT, FRUIT_WIDTH
                %assign current_fruit_x_pos current_fruit_x_pos+FRUIT_WIDTH+6
                %if current_fruit_x_pos = FRUIT_BANK_X_POS+(4*(FRUIT_WIDTH+6))
                    %assign current_fruit_x_pos FRUIT_BANK_X_POS
                    %assign current_fruit_y_pos current_fruit_y_pos+FRUIT_HEIGHT+5
                %endif
                %assign current_fruit_index current_fruit_index+1
            %endrep
        printLevel:
            mov si, levelTitle
            displayItem LEVEL_Y_POS, LEVEL_X_POS, LEVEL_TITLE_HEIGHT, LEVEL_TITLE_WIDTH
        printLevelNbBox:
            mov si, levelNbBox
            displayItem LEVEL_BOX_Y_POS, LEVEL_X_POS, LEVEL_NUMBER_HEIGHT, LEVEL_NUMBER_WIDTH
        printLevelNb:
            call updateDisplayedLevel
            textDisplay displayedLevel, 3, LEVEL_BOX_Y_POS+3, LEVEL_X_POS+3, FONT_HEIGHT, FONT_WIDTH
        pressArrows:
            textDisplay pressText, 5, PRESS_ARROWS_Y_POS, PRESS_ARROWS_X_POS, FONT_HEIGHT, FONT_WIDTH
            arrows:
                mov si, bottomleft
                displayItem PRESS_ARROWS_Y_POS + FONT_HEIGHT + 4, PRESS_ARROWS_X_POS + 1, PRESS_ARROWS_HEIGHT, PRESS_ARROWS_WIDTH
        pressEnter:
            textDisplay pressText, 5, PRESS_ENTER_Y_POS, PRESS_ENTER_X_POS, FONT_HEIGHT, FONT_WIDTH
            cmp byte [isPause], 1
            je displayEnterText
            displayEscText:
                textDisplay escText, 6, PRESS_ENTER_Y_POS + FONT_HEIGHT + 4, PRESS_ENTER_X_POS, FONT_HEIGHT, FONT_WIDTH
            ret
            displayEnterText:
                textDisplay enterText, 5, PRESS_ENTER_Y_POS + FONT_HEIGHT + 4, PRESS_ENTER_X_POS, FONT_HEIGHT, FONT_WIDTH
        ret

        ; ; testing purpose
        ; drawPixel:
        ;     mov word [item_width], 1
        ;     mov word [item_height], 1
        ;     mov ax, 2
        ;     mov word [item_x_pos], ax
        ;     mov ax, 2
        ;     ret
