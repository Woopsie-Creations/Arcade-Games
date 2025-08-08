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
            cmp al, 0x0F
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

%macro textDisplay 7
    mov word [letter_x_pos], %4
    mov word [letter_y_pos], %3
    mov bx, 0
        %%eachLetter:
        mov si, %1
        mov si, [si+bx]
        push bx
        displayItem [letter_y_pos], [letter_x_pos], %5, %6
        cmp byte [has_written_fancy_text], TRUE
        je %%skip
        mov al, %7
        cmp al, FALSE
        je %%skip
        call displayViewport
        mov dx, 50000
        mov ah, 0x86
        int 0x15
        %%skip:
        pop bx
        add word [letter_x_pos], %6 + 1
        add bx, 2
        cmp bx, %2 * 2
        jne %%eachLetter
    mov bx, word [letter_x_pos]
    mov al, %7
    cmp al, FALSE
    je %%end
    mov byte [has_written_fancy_text], TRUE
    %%end:
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
                mov byte [es:di], 0x0F  ; place the pixel on the viewport
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

; updateDisplayedScore number, displayedNumbers, count

%macro updateDisplayedScore 3
    xor cx, cx ; displayedNumbers' count
    %%loop:
        cmp cx, %3
        jge %%done

        mov bx, cx ; get numbers' count
        
        movzx ax, byte [%1 + bx] ; get the number
        shl ax, 1
        mov bx, ax
        mov ax, word [displayNumbersFont + bx] ; use the number as an index to get sprite

        mov bx, cx
        shl bx, 1
        mov word [%2 + bx], ax ; put the sprite

        inc cx
        jmp %%loop
    %%done:
%endmacro

%macro displayCurrentPokes 0-* first_trainerStruc, buffer1, FIRST_PLAYER_POKE_Y_POS, FIRST_PLAYER_POKE_X_POS, BACK_SPRITE_HEIGHT, BACK_SPRITE_WIDTH, BACK_SPRITE_SIZE, second_trainerStruc, buffer2, SECOND_PLAYER_POKE_Y_POS, SECOND_PLAYER_POKE_X_POS, FRONT_SPRITE_HEIGHT, FRONT_SPRITE_WIDTH, FRONT_SPRITE_SIZE
    %rep 2
        push bx
        cmp bx, 0
        je %%do_%1
        cmp bx, 1
        je %%skip_%1
        %%do_%1:
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
        %%skip_%1:
        pop bx
        dec bx
        %rotate 7
    %endrep
%endmacro

%macro displayHpBar 3
    mov si, %3
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]

    mov ax, [bx + pokemon.hp] ; containing pokemon hp
    cmp ax, 0
    je %%skipHpbar

    push bx

    ; multiply by 50 cuz the max_width of the hpbar is 50
    mov bx, 50
    mul bx

    pop bx
    push bx
    ; divide my max_hp
    mov bx, [bx + pokemon.max_hp]
    div bx
    
    ; so now we have the percentage of hp
    pop bx
    mov byte [current_hp_width], al

    cmp al, 13
    jle %%red
    cmp al, 25
    jle %%yellow
    mov al, [hp_color_table+0]
    jmp %%end
    %%red:
    mov al, [hp_color_table+2]
    jmp %%end
    %%yellow:
    mov al, [hp_color_table+1]

    %%end:
    mov byte [current_hp_color], al

    %%display:
    mov ax, [viewport_memory_block_pos]
    mov es, ax
    ; calculate the position of the item
    mov ax, %1
    mov bx, 320
    mul bx
    add ax, %2
    mov di, ax
    mov dx, 2 ; hp_bar height
    %%eachItemRow:
        xor cx, cx
        mov cl, [current_hp_width]
        %%eachItemColumn:
            xor ax, ax
            mov al, [current_hp_color]
            mov byte [es:di], al     ; place the pixel on the viewport
            inc di
            dec cl
            jnz %%eachItemColumn
        add di, SCREEN_WIDTH
        xor ax, ax
        mov al, [current_hp_width]
        sub di, ax
        dec dx
        jnz %%eachItemRow
    %%skipHpbar:
%endmacro

%macro displayPokeName 4
    textDisplay %1, %4, %2, %3, FONT_HEIGHT, FONT_WIDTH, FALSE
%endmacro

%macro displayPP 3
    ; got bx from previous operations
    push bx
    mov al, [bx + attack.%1]

    xor dx, dx
    mov bl, 10
    div bl ; AX / 10 → AL = quotient (1st digit), AH = remainder (2nd digit)
    mov byte [concatenatedNumbers], al
    mov byte [concatenatedNumbers+1], ah
    updateDisplayedScore concatenatedNumbers, displayedNumbers, 2
    textDisplay displayedNumbers, 2, %2+FONT_HEIGHT*2, %3+FONT_WIDTH/2, FONT_HEIGHT, FONT_WIDTH, FALSE
    pop bx
%endmacro

%macro displayPokeAttack 4
    %assign %%_label_id 0
    %assign %%x_pos %4
    %assign %%y_pos %3

    mov bx, 0
    %rep 2
        %rep 2
            %%beginning%+%%_label_id:
            push bx
            mov bx, [%1 + trainer.current_poke]
            shl bx, 1
            add bx, trainer.pokemons
            mov bx, [%1 + bx] ; here we get the current poke
            pop si
            push si
            shl si, 1
            mov bx, [bx + pokemon.attacks + si] ; and its attack
            push bx

            mov ax, [bx + attack.name]
            mov word [current_attack_name], ax
            displayPokeName [current_attack_name], %%y_pos, %%x_pos, %2
            
            pop bx
            displayPP pp, %%y_pos, %%x_pos
            displayPP max_pp, %%y_pos, %%x_pos+FONT_WIDTH*4

            pop bx
            cmp bx, 3
            je %%setToZero%+%%_label_id
            inc bx
            jmp %%end%+%%_label_id
            %%setToZero%+%%_label_id:
            mov bx, 0
            %%end%+%%_label_id:
            %assign %%_label_id %%_label_id + 1
            %assign %%x_pos %%x_pos+BATTLE_LITTLE_CASE_WIDTH+2
        %endrep
        %assign %%x_pos %4
        %assign %%y_pos %%y_pos-BATTLE_LITTLE_CASE_HEIGHT-2
    %endrep
%endmacro

%macro displayTeamPokeName 4
    %assign %%_label_id 0
    %assign %%x_pos %4
    %assign %%y_pos %3

    mov bx, [%1 + trainer.current_poke]
    %rep 2
        %rep 3
            %%beginning%+%%_label_id:
            xor bh, bh
            push bx
            shl bx, 1
            add bx, trainer.pokemons
            mov bx, [%1 + bx]
            mov ax, [bx + pokemon.name]
            mov word [current_poke_name], ax
            displayPokeName [current_poke_name], %%y_pos, %%x_pos, %2
            pop bx
            
            cmp bx, 5
            je %%setToZero%+%%_label_id
            inc bx
            jmp %%end%+%%_label_id
            %%setToZero%+%%_label_id:
            mov bx, 0
            %%end%+%%_label_id:
            %assign %%_label_id %%_label_id + 1
            %assign %%x_pos %%x_pos+BATTLE_LITTLE_CASE_WIDTH+2
        %endrep
        %assign %%x_pos %4
        %assign %%y_pos %%y_pos-BATTLE_LITTLE_CASE_HEIGHT-2
    %endrep
%endmacro

%macro displayCurrentPokeName 4
    mov si, %1
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]
    
    mov ax, [bx + pokemon.name]
    mov word [current_poke_name], ax
    displayPokeName [current_poke_name], %2, %3, %4
%endmacro

%macro displayCaseBg 3
    mov si, %3
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]

    pop si
    push si
    shl si, 1
    mov bx, [bx + pokemon.attacks + si] ; and its attack
    
    mov bl, byte [bx + attack.type]
    xor bh, bh
    mov al, byte [type_color_table+bx]
    mov byte [current_case_color], al

    mov ax, [viewport_memory_block_pos]
    mov es, ax
    ; calculate the position of the item
    mov ax, %1+4
    mov bx, 320
    mul bx
    add ax, %2+3
    mov di, ax
    mov dx, BATTLE_LITTLE_CASE_HEIGHT-8 ; case height
    %%eachItemRow:
        xor cx, cx
        mov cl, BATTLE_LITTLE_CASE_WIDTH-6 ; case width
        %%eachItemColumn:
            xor ax, ax
            mov al, [current_case_color]
            mov byte [es:di], al     ; place the pixel on the viewport
            inc di
            dec cl
            jnz %%eachItemColumn
        add di, SCREEN_WIDTH
        xor ax, ax
        mov al, BATTLE_LITTLE_CASE_WIDTH-6 ; case width
        sub di, ax
        dec dx
        jnz %%eachItemRow 
%endmacro

%macro displayLittleCases 5
    %assign %%_label_id 0
    %assign %2 %4+10
    %assign %1 %3+15+BATTLE_LITTLE_CASE_HEIGHT+2

    mov bx, 0
    push bx
    %rep 2
        %rep 3
            %if %%_label_id = 0
            jmp %%skipCaseBg%+%%_label_id
            %elif %%_label_id = 3
            jmp %%skipCaseBg%+%%_label_id
            %endif
            cmp byte [%5 + trainer.battle_tab], 0
            jne %%skipCaseBg%+%%_label_id
            pop bx
            push bx
            displayCaseBg %1, %2, %5
            pop bx
            inc bx
            push bx
            mov si, fontSlash
            displayItem %1+FONT_HEIGHT*3, %2+BATTLE_LITTLE_CASE_WIDTH/2-FONT_WIDTH+2, FONT_HEIGHT, FONT_WIDTH
            %%skipCaseBg%+%%_label_id:
            mov si, little_case
            displayItem %1, %2, BATTLE_LITTLE_CASE_HEIGHT, BATTLE_LITTLE_CASE_WIDTH
            %assign %%_label_id %%_label_id + 1
            %assign %2 %2+BATTLE_LITTLE_CASE_WIDTH+2
        %endrep
        %assign %2 %4+10
        %assign %1 %1-BATTLE_LITTLE_CASE_HEIGHT-2
    %endrep
    pop bx

    %assign %2 %4
    %assign %1 %3
%endmacro

%macro displayCurrentAction 3
    mov byte [has_written_fancy_text], FALSE
    call displayFrame

    mov si, %1
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]
    
    mov ax, word [bx + pokemon.name]
    mov word [current_action_pokemon_name_text], ax

    textDisplay [current_action_pokemon_name_text], 10, %2, %3, FONT_HEIGHT, FONT_WIDTH, TRUE
    mov ax, %2
    mov byte [has_written_fancy_text], FALSE
    cmp byte [%1 + trainer.battle_tab], 1
    je %%pokemon_tab
    textDisplay ACTION_TEXT, ACTION_TEXT_WIDTH, ax, bx, FONT_HEIGHT, FONT_WIDTH, TRUE
    je %%end
    %%pokemon_tab:
    textDisplay SWITCH_TEXT, SWITCH_TEXT_WIDTH, ax, bx, FONT_HEIGHT, FONT_WIDTH, TRUE
    %%end:
    %rep 15
        mov dx, 50000
        mov ah, 0x86
        int 0x15
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
        mov bx, 0
        displayCurrentPokes
        call displayUI
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

    displayUI:
        displaySecond:
            displayCurrentPokeName second_trainerStruc, SECOND_POKE_NAME_Y_POS, SECOND_POKE_NAME_X_POS, 10
            mov si, hp_arrow_front
            displayItem SECOND_PLAYER_HP_ARROW_Y_POS, SECOND_PLAYER_HP_ARROW_X_POS, HP_ARROW_HEIGHT, HP_ARROW_WIDTH
            mov si, hp_bar
            displayItem SECOND_PLAYER_HP_BAR_Y_POS, SECOND_PLAYER_HP_BAR_X_POS, HP_BAR_HEIGHT, HP_BAR_WIDTH
            displayHpBar SECOND_PLAYER_HP_BAR_Y_POS + 2, SECOND_PLAYER_HP_BAR_X_POS + 16, second_trainerStruc

        displayFirst:
            displayCurrentPokeName first_trainerStruc, FIRST_POKE_NAME_Y_POS, FIRST_POKE_NAME_X_POS, 10
            mov si, hp_arrow_back
            displayItem FIRST_PLAYER_HP_ARROW_Y_POS, FIRST_PLAYER_HP_ARROW_X_POS, HP_ARROW_HEIGHT, HP_ARROW_WIDTH
            mov si, hp_bar
            displayItem FIRST_PLAYER_HP_BAR_Y_POS, FIRST_PLAYER_HP_BAR_X_POS, HP_BAR_HEIGHT, HP_BAR_WIDTH
            displayHpBar FIRST_PLAYER_HP_BAR_Y_POS + 2, FIRST_PLAYER_HP_BAR_X_POS + 16, first_trainerStruc

        mov si, battle_case
        displayItem FIRST_BATTLE_CASE_Y_POS, FIRST_BATTLE_CASE_X_POS, BATTLE_CASE_HEIGHT, BATTLE_CASE_WIDTH
        mov si, battle_case
        displayItem SECOND_BATTLE_CASE_Y_POS, SECOND_BATTLE_CASE_X_POS, BATTLE_CASE_HEIGHT, BATTLE_CASE_WIDTH

        displayUICaseFirst:
            cmp byte [in_execution], TRUE
            je .next
            cmp byte [first_trainerStruc + trainer.has_chosen], FALSE
            je .content
            cmp byte [second_trainerStruc + trainer.has_chosen], TRUE
            je .next
            textDisplay PLAYER_ONE_HAS_CHOSEN_TEXT, PLAYER_HAS_CHOSEN_TEXT_WIDTH, PLAYER_ONE_HAS_CHOSEN_TEXT_Y_POS, PLAYER_ONE_HAS_CHOSEN_TEXT_X_POS, FONT_WIDTH, FONT_HEIGHT, FALSE
            jmp displayUICaseSecond

            .content:
            mov si, battle_case_arrows
            displayItem BATTLE_CASE_ARROW_Y_POS, FIRST_BATTLE_CASE_ARROW_LEFT_X_POS, BATTLE_CASE_ARROW_HEIGHT, BATTLE_CASE_ARROW_WIDTH
            displayItem BATTLE_CASE_ARROW_Y_POS, FIRST_BATTLE_CASE_ARROW_RIGHT_X_POS, BATTLE_CASE_ARROW_HEIGHT, BATTLE_CASE_ARROW_WIDTH
            displayLittleCases FIRST_BATTLE_CASE_Y_POS, FIRST_BATTLE_CASE_X_POS, FIRST_PLAYER_POKE_Y_POS + BACK_SPRITE_HEIGHT + 3, 2, first_trainerStruc
            cmp byte [first_trainerStruc + trainer.battle_tab], 1
            je .pokemonTab
            jg .bagTab
            .attacksTab:
                displayPokeAttack first_trainerStruc, 6, FIRST_BATTLE_CASE_Y_POS+BATTLE_LITTLE_CASE_HEIGHT+2+20, FIRST_BATTLE_CASE_X_POS+BATTLE_LITTLE_CASE_WIDTH+14+2
                textDisplay ATTACKS_TEXT, ATTACKS_TEXT_WIDTH, FIRST_BATTLE_CASE_TEXT_Y_POS, FIRST_BATTLE_CASE_TEXT_X_POS, FONT_WIDTH, FONT_HEIGHT, FALSE
                jmp .next
            .pokemonTab:
                displayTeamPokeName first_trainerStruc, 6, FIRST_BATTLE_CASE_Y_POS+BATTLE_LITTLE_CASE_HEIGHT+2+20, FIRST_BATTLE_CASE_X_POS+14
                textDisplay POKEMON_TEXT, POKEMON_TEXT_WIDTH, FIRST_BATTLE_CASE_TEXT_Y_POS, FIRST_BATTLE_CASE_TEXT_X_POS, FONT_WIDTH, FONT_HEIGHT, FALSE
                jmp .next
            .bagTab: ; not implemented yet
            .next:

        displayUICaseSecond:
            cmp byte [in_execution], TRUE
            je .next
            cmp byte [second_trainerStruc + trainer.has_chosen], FALSE
            je .content
            cmp byte [first_trainerStruc + trainer.has_chosen], TRUE
            je .next
            textDisplay PLAYER_TWO_HAS_CHOSEN_TEXT, PLAYER_HAS_CHOSEN_TEXT_WIDTH, PLAYER_TWO_HAS_CHOSEN_TEXT_Y_POS, PLAYER_TWO_HAS_CHOSEN_TEXT_X_POS, FONT_WIDTH, FONT_HEIGHT, FALSE
            jmp .next

            .content:
            mov si, battle_case_arrows
            displayItem BATTLE_CASE_ARROW_Y_POS, SECOND_BATTLE_CASE_ARROW_LEFT_X_POS, BATTLE_CASE_ARROW_HEIGHT, BATTLE_CASE_ARROW_WIDTH
            displayItem BATTLE_CASE_ARROW_Y_POS, SECOND_BATTLE_CASE_ARROW_RIGHT_X_POS, BATTLE_CASE_ARROW_HEIGHT, BATTLE_CASE_ARROW_WIDTH
            displayLittleCases SECOND_BATTLE_CASE_Y_POS, SECOND_BATTLE_CASE_X_POS, FIRST_BATTLE_CASE_Y_POS, FIRST_BATTLE_CASE_X_POS + BATTLE_CASE_WIDTH + 2, second_trainerStruc
            cmp byte [second_trainerStruc + trainer.battle_tab], 1
            je .pokemonTab
            jg .bagTab
            .attacksTab:
                displayPokeAttack second_trainerStruc, 6, SECOND_BATTLE_CASE_Y_POS+BATTLE_LITTLE_CASE_HEIGHT+2+20, SECOND_BATTLE_CASE_X_POS+BATTLE_LITTLE_CASE_WIDTH+14+2
                textDisplay ATTACKS_TEXT, ATTACKS_TEXT_WIDTH, SECOND_BATTLE_CASE_TEXT_Y_POS, SECOND_BATTLE_CASE_TEXT_X_POS, FONT_WIDTH, FONT_HEIGHT, FALSE
                jmp .next
            .pokemonTab:
                displayTeamPokeName second_trainerStruc, 6, SECOND_BATTLE_CASE_Y_POS+BATTLE_LITTLE_CASE_HEIGHT+2+20, SECOND_BATTLE_CASE_X_POS+14
                textDisplay POKEMON_TEXT, POKEMON_TEXT_WIDTH, SECOND_BATTLE_CASE_TEXT_Y_POS, SECOND_BATTLE_CASE_TEXT_X_POS, FONT_WIDTH, FONT_HEIGHT, FALSE
                jmp .next
            .bagTab: ; not implemented yet
            .next:
        ret