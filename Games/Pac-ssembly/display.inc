%macro displayItem 4
    mov ax, [viewport_memory_block_pos]
    mov es, ax
    ; calculate the position of the item
    mov ax, %1
    mov bx, 320
    mul bx
    add ax, %2
    mov di, ax
    ; draw the item
    mov dx, %3 ;[item_height]
    %%eachItemRow:
        mov cx, %4 ;[item_width]
        %%eachItemColumn:
            xor ax, ax
            ; get the colour of the sprite at said position in the memory by the register si
            mov al, [si]
            cmp byte [is_displaying_black], TRUE
            je %%keepColor
            cmp al, 0x00
            je %%skipTransparent      ; skip the colour placement if transparent
            cmp byte [blinkColor], TRUE
            je %%keepColor
            mov byte [es:di], 0x0F
            %%keepColor:
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
        %%eachLetter:
        mov si, [%1+bx]
        push bx
        displayItem [letter_y_pos], [letter_x_pos], %5, %6
        pop bx
        add word [letter_x_pos], %6 + 1
        add bx, 2
        cmp bx, %2 * 2
        jne %%eachLetter
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

%macro printEntities 0-* pacman, blinky, pinky, inky, clyde
    %rep 5
        mov al, [%1Struc + entity.sprite_nb]
        xor ah, ah ; make sure we read only 1 byte of item

        mov bx, ENTITY_SPRITE_WIDTH * ENTITY_SPRITE_HEIGHT
        mul bx
        push ax

        %ifidni %1, pacman
        mov si, %1
        %else
        mov ax, %1
        cmp byte [%1_in_fright_mode], TRUE
        jne %%skip_%1
        mov ax, fright

        %%skip_%1:
        mov si, ax
        %endif
        
        pop ax
        add si, ax

        displayItem [%1Struc + entity.y_pos], [%1Struc + entity.x_pos], ENTITY_SPRITE_HEIGHT, ENTITY_SPRITE_WIDTH 
        %rotate 1
    %endrep
%endmacro

%macro clearItem 4
        mov ax, [viewport_memory_block_pos]
        mov es, ax
        ; calculate the position of the item
        mov ax, %1
        mov bx, 320
        mul bx
        add ax, %2
        mov di, ax
        ; draw the item
        mov dx, %3 ;[item_height]
        %%eachItemRow:
            mov cx, %4 ;[item_width]
            %%eachItemColumn:
                mov byte [es:di], 0x00  ; place the pixel on the viewport
                ; go to the next pixel
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

%macro clearEntities 0-* pacman, blinky, pinky, inky, clyde
    %rep %0
        clearItem [%1Struc + entity.y_pos], [%1Struc + entity.x_pos], ENTITY_SPRITE_HEIGHT, ENTITY_SPRITE_WIDTH
        %rotate 1
    %endrep
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
        ; call clearViewport
        call printMaze
        call spawnCurrentFruit
        printEntities
        call printUI
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
        ; clearEntities
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

    printMaze:
        ; init coordinates
        mov byte [is_displaying_black], TRUE
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
            mov byte [is_displaying_black], FALSE
        ret

    spawnCurrentFruit:
        cmp byte [fruit_should_be_displayed], TRUE
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
        mov byte [is_displaying_black], TRUE
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
            updateDisplayedScore current_score, displayedNumbers, 9, FALSE
            textDisplay displayedNumbers, 9, SCORE_BOX_Y_POS+2, SCORE_BOX_X_POS+2, FONT_HEIGHT, FONT_WIDTH
        printDynamicScore:
            cmp byte [dynamic_score], FALSE
            je skipPrintDynamicScore

            cmp word [expected_time_score], -1
            je .initScore

            checkTimer current_time_score, expected_time_score, skipPrintDynamicScore, [has_init_timer_score]
            jmp .display

            .initScore:
            updateDisplayedScore dynamic_score_amount, displayedDynamicNumbers, 4, TRUE
            mov ax, [pacmanStruc + entity.y_pos]
            sub ax, 5
            mov word [DYNAMIC_SCORE_Y_POS], ax
            mov ax, [pacmanStruc + entity.x_pos]
            sub ax, 6
            mov word [DYNAMIC_SCORE_X_POS], ax
            init_timer 1, time_start_score, interval_ticks_score, expected_time_score, [has_init_timer_score]

            .display:
                mov ax, [DYNAMIC_SCORE_Y_POS]
                mov bx, [DYNAMIC_SCORE_X_POS]
                textDisplay displayedDynamicNumbers, 4, ax, bx, FONT_HEIGHT, FONT_WIDTH
                jmp printHScoreBox
                
        skipPrintDynamicScore:
            mov byte [dynamic_score], FALSE
            call resetDynamicScore

        printHScoreBox:
            mov si, scoreNumberBox
            displayItem SCORE_BOX_Y_POS+SCORE_TEXT_TITLE_HEIGHT+2, SCORE_BOX_X_POS, SCORE_TEXT_TITLE_HEIGHT, SCORE_BOX_WIDTH
        printHScore:
            updateDisplayedScore high_score, displayedHighscoreNumbers, 9, FALSE
            textDisplay displayedHighscoreNumbers, 9, SCORE_BOX_Y_POS+SCORE_TEXT_TITLE_HEIGHT+4, SCORE_BOX_X_POS+2, FONT_HEIGHT, FONT_WIDTH
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
        printLives:
            mov bx, [pacman_lives]
            xor bh, bh
            mov cx, 4
            mov dx, LIVES_Y_POS
            .everyLives:
                mov si, pacman
                add si, 3 * (ENTITY_SPRITE_HEIGHT * ENTITY_SPRITE_WIDTH)
                push cx
                push bx
                push dx
                cmp bx, 0
                jle .clearLives
                displayItem dx, LIVES_X_POS, ENTITY_SPRITE_HEIGHT, ENTITY_SPRITE_WIDTH
                jmp .skipClearLives
                .clearLives:
                clearItem dx, LIVES_X_POS, ENTITY_SPRITE_HEIGHT, ENTITY_SPRITE_WIDTH
                .skipClearLives:
                pop dx
                add dx, ENTITY_SPRITE_HEIGHT
                pop bx
                dec bx
                pop cx
                dec cx
                jnz .everyLives
        printLevel:
            mov si, levelTitle
            displayItem LEVEL_Y_POS, LEVEL_X_POS, LEVEL_TITLE_HEIGHT, LEVEL_TITLE_WIDTH
        printLevelNbBox:
            mov si, levelNbBox
            displayItem LEVEL_BOX_Y_POS, LEVEL_X_POS, LEVEL_NUMBER_HEIGHT, LEVEL_NUMBER_WIDTH
        printLevelNb:
            call updateDisplayedLevel
            textDisplay displayedLevel, 3, LEVEL_BOX_Y_POS+3, LEVEL_X_POS+3, FONT_HEIGHT, FONT_WIDTH
        printSmalWoopsie:
            mov si, smalWoopsie
            displayItem SMAL_WOOPSIE_Y_POS, SMAL_WOOPSIE_X_POS, SMAL_WOOPSIE_HEIGHT, SMAL_WOOPSIE_WIDTH
        pressArrows:
            textDisplay pressText, 5, PRESS_ARROWS_Y_POS, PRESS_ARROWS_X_POS, FONT_HEIGHT, FONT_WIDTH
            arrows:
                mov si, bottomleft
                displayItem PRESS_ARROWS_Y_POS + FONT_HEIGHT + 4, PRESS_ARROWS_X_POS + 1, PRESS_ARROWS_HEIGHT, PRESS_ARROWS_WIDTH
        pressEnter:
            textDisplay pressText, 5, PRESS_ENTER_Y_POS, PRESS_ENTER_X_POS, FONT_HEIGHT, FONT_WIDTH
            cmp byte [isPause], TRUE
            je .displayEnterText
            .displayEscText:
                textDisplay escText, 3, PRESS_ENTER_Y_POS + FONT_HEIGHT + 4, PRESS_ENTER_X_POS, FONT_HEIGHT, FONT_WIDTH
            jmp .end
            .displayEnterText:
                textDisplay enterText, 3, PRESS_ENTER_Y_POS + FONT_HEIGHT + 4, PRESS_ENTER_X_POS, FONT_HEIGHT, FONT_WIDTH
            .end:
        ReadyPause:
            displayStateText:
                cmp byte [isPause], FALSE
                je .end
                textDisplay current_state_text, 5, STATE_TEXT_Y_POS, STATE_TEXT_X_POS, FONT_HEIGHT, FONT_WIDTH
                .end:
        mov byte [is_displaying_black], FALSE
        ret