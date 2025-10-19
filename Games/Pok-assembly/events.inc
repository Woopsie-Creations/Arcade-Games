%include "animations.inc"

%macro hit 1
    mov si, %1
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]
    mov ax, [bx + pokemon.hp]
    ; ax contains the enemy pokemon hp

    cmp word [current_attack_damage], ax
    jge %%setToZero

    sub word ax, [current_attack_damage]
    jmp %%progressively

    %%setToZero:
    mov word ax, 0

    %%progressively:
    ; serves as animation
    push ax
    push bx
    cmp word ax, 0
    je %%this_is_the_end
    cmp word [bx + pokemon.hp], 0
    je %%this_is_the_end
    dec word [bx + pokemon.hp]
    call displayFrame
    pop bx
    pop ax
    
    cmp word [bx + pokemon.hp], ax
    jne %%progressively
    jmp %%end

    %%this_is_the_end:
    pop bx
    pop ax
    mov word [bx + pokemon.hp], 0
    call displayFrame
    ; yes we are waiters
    wait 50000
    wait 50000
    wait 50000
    wait 50000
    wait 50000

    mov al, byte [%1 + trainer.current_poke]
    inc al ; should be capped (not restricted to index 5 max)
    ; should also check if the poke is already dead -> cannot switch to it
    changePoke %1, al
    %%end:
%endmacro

%macro changePoke 2
    mov byte [%1 + trainer.current_poke], %2
    mov byte [%1 + trainer.has_chosen], FALSE
    mov byte [%1 + trainer.action_key_pressed], 00h
    call displayFrame
%endmacro

%macro changeTab 1 
    cmp byte [%1 + trainer.battle_tab], 0
    je %%pokemon
    ; bag not implemented
    ; cmp byte [%1 + trainer.battle_tab], 1
    ; je %%bag
    mov al, 0
    jmp %%end
    %%pokemon:
    mov al, 1
    jmp %%end
    %%bag:
    mov al, 2
    %%end:
    mov byte [%1 + trainer.battle_tab], al
    call displayFrame
%endmacro

%macro switchPoke 2 
    add bl, %2
    cmp bl, 6
    jl %%changePoke
    sub bl, 6
    %%changePoke:
    changePoke %1, bl
%endmacro

%macro events 6
    mov ah, [%1 + trainer.action_key_pressed]
    cmp ah, 00h
    je %%end

    cmp ah, %2
    je %%input
    cmp ah, %3
    je %%input
    cmp ah, %4
    je %%input
    cmp ah, %5
    je %%input
    cmp ah, %6
    je %%input
    jmp %%end

    %%input:
    cmp byte [%1 + trainer.battle_tab], 0
    je %%hit
    cmp byte [%1 + trainer.battle_tab], 1
    je %%change
    ; bag not implemented
    
    %%middleBotKey:
    mov bx, 0
    jmp %%executeHit
    %%rightBotKey:
    mov bx, 1
    jmp %%executeHit
    %%middleTopKey:
    mov bx, 2
    jmp %%executeHit
    %%rightTopKey:
    mov bx, 3
    jmp %%executeHit

    %%hit:
    xor bx, bx
    cmp ah, %3
    je %%middleBotKey
    cmp ah, %5
    je %%rightBotKey
    cmp ah, %4
    je %%middleTopKey
    cmp ah, %6
    je %%rightTopKey

    %%executeHit:
    shl bx, 1
    push bx
    mov si, %1
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]
    pop si
    mov bx, [bx + pokemon.attacks + si]
    mov ax, [bx + attack.damage]
    dec byte [bx + attack.pp]
    mov word [current_attack_damage], ax

    %ifidni %1, first_trainerStruc
        jmp hit_second
    %else
        jmp hit_first
    %endif

    %%change:
    xor bx, bx
    mov bl, [%1 + trainer.current_poke]
    cmp ah, %2
    je %%fourth
    cmp ah, %3
    je %%second
    cmp ah, %4
    je %%fifth
    cmp ah, %5
    je %%third
    cmp ah, %6
    je %%sixth

    %%fourth:
    switchPoke %1, 3
    jmp %%end
    %%second:
    switchPoke %1, 1
    jmp %%end
    %%fifth:
    switchPoke %1, 4
    jmp %%end
    %%third:
    switchPoke %1, 2
    jmp %%end
    %%sixth:
    switchPoke %1, 5
    %%end:
    mov byte [%1 + trainer.has_chosen], FALSE
    mov byte [%1 + trainer.action_key_pressed], 00h
%endmacro

section .text
    changeTab_first:
        changeTab first_trainerStruc
        jmp readKeyboard.second_player
    changeTab_second:
        changeTab second_trainerStruc
        jmp gameLoop
        
    executeEvents:
        cmp byte [first_trainerStruc + trainer.has_chosen], FALSE
        je .end 
        cmp byte [second_trainerStruc + trainer.has_chosen], FALSE
        je .end
        mov byte [in_execution], TRUE
        ; should decide which one should go first
        cmp byte [second_trainerStruc + trainer.battle_tab], 1
        je .second
        .first:
        displayCurrentAction first_trainerStruc, PLAYER_ONE_HAS_CHOSEN_TEXT_Y_POS, PLAYER_ONE_HAS_CHOSEN_TEXT_X_POS
        events first_trainerStruc, I_KEY, J_KEY, K_KEY, N_KEY, M_KEY
        cmp byte [second_trainerStruc + trainer.has_chosen], FALSE
        je .end
        .second:
        displayCurrentAction second_trainerStruc, PLAYER_TWO_HAS_CHOSEN_TEXT_Y_POS, PLAYER_TWO_HAS_CHOSEN_TEXT_X_POS
        events second_trainerStruc, T_KEY, F_KEY, G_KEY, C_KEY, V_KEY
        cmp byte [first_trainerStruc + trainer.has_chosen], TRUE
        je .first

        .end:
        call displayFrame
        mov byte [in_execution], FALSE
        ret

    hit_second:
        cmp word [current_attack_damage], 0
        je .skip
        ; got index of attack previously in bx
        hitAnimation 2
        hit second_trainerStruc
        
        .skip:
        mov byte [first_trainerStruc + trainer.has_chosen], FALSE
        mov byte [first_trainerStruc + trainer.action_key_pressed], 00h
        cmp byte [second_trainerStruc + trainer.has_chosen], TRUE
        je executeEvents.second
        ret 
    hit_first:
        cmp word [current_attack_damage], 0
        je .skip
        ; got index of attack previously in bx
        hitAnimation 1
        hit first_trainerStruc

        .skip:
        mov byte [second_trainerStruc + trainer.has_chosen], FALSE
        mov byte [second_trainerStruc + trainer.action_key_pressed], 00h
        cmp byte [first_trainerStruc + trainer.has_chosen], TRUE
        je executeEvents.first
        
        call displayFrame
        mov byte [in_execution], FALSE
        ret