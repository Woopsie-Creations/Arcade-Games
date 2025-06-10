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

%macro displayPixelBlock 0-* eax
    ; go to the memory block for the viewport to then take the colour of the selected pixel of the viewport
    mov ax, [viewport_memory_block_pos]
    mov es, ax
    %rep 4 ; you're probably wondering how i ended up in this situation
        xor eax, eax  ; clear the register ax because we will only use the lower part (al) for the colour
        mov eax, dword [es:di]
        push eax
        add di, 4
    %endrep
    mov ax, 0xA000
    mov es, ax
    %rep 4 ; you're probably wondering how i ended up in this situation
        pop eax
        mov dword [es:di-4], eax
        sub di, 4
    %endrep
%endmacro

%macro displayCurrentPokes 0-* first_trainerStruc, buffer1, FIRST_PLAYER_POKE_Y_POS, FIRST_PLAYER_POKE_X_POS, BACK_SPRITE_HEIGHT, BACK_SPRITE_WIDTH, BACK_SPRITE_SIZE, second_trainerStruc, buffer2, SECOND_PLAYER_POKE_Y_POS, SECOND_PLAYER_POKE_X_POS, FRONT_SPRITE_HEIGHT, FRONT_SPRITE_WIDTH, FRONT_SPRITE_SIZE
    %rep 2
        mov si, %1
        mov bl, [si + trainer.current_poke]
        xor bh, bh
        shl bx, 1
        add bx, trainer.pokemons
        mov bx, [si + bx]

        mov dx, [bx + pokemon.sprite]
        loadBuffer %2, %7
        mov si, %2
        displayItem %3, %4, %5, %6
        %rotate 7
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
        ; place everything and then display
        call clearViewport
        displayCurrentPokes
        call displayViewport
        ret

    clearViewport:
        ; "select" the memory block allocated for the viewport
        mov ax, [viewport_memory_block_pos]
        mov es, ax
        ; set the position to the first pixel
        mov di, 0
        .clearEachPixels:
            ; set the pixel selected to white
            mov byte [es:di], 0x0F
            ; loop until it has done every pixels
            inc di
            cmp di, SCREEN_HEIGHT * SCREEN_WIDTH
            jne .clearEachPixels
        ret

    displayViewport:
        ; set the position to the first pixel
        mov di, 0
        .eachPixel:
            displayPixelBlock
            add di, 16 ; you're probably wondering how i ended up in this situation
            cmp di, SCREEN_HEIGHT * SCREEN_WIDTH
            jne .eachPixel
        ret
    
    ; deallocate the memory used for the viewport (so it's more clean)
    deallocationViewport:
        mov ax, [viewport_memory_block_pos]
        mov es, ax
        xor ax, ax
        mov ah, 49h
        int 21h
        jc gameLoop ; return to the gameloop in case of failure (just to verify for now, will probably change)
        ret