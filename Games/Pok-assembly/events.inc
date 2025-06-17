%macro hit 2
    mov si, %1
    mov bl, [si + trainer.current_poke]
    xor bh, bh
    shl bx, 1
    add bx, trainer.pokemons
    mov bx, [si + bx]
    
    mov ax, [bx + pokemon.hp]
    cmp ax, %2
    jle %%setToZero
    sub word [bx + pokemon.hp], %2
    jmp %%end

    %%setToZero:
    mov word [bx + pokemon.hp], 0

    %%end:
    call displayFrame
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

    %%hit:
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
        ; should decide which one should go first, but default P1
        events first_trainerStruc, I_KEY, J_KEY, K_KEY, N_KEY, M_KEY
        .second:
        events second_trainerStruc, T_KEY, F_KEY, G_KEY, C_KEY, V_KEY
        .end:
        ret

    hit_second:
        hit second_trainerStruc, 100
        mov byte [first_trainerStruc + trainer.has_chosen], FALSE
        mov byte [first_trainerStruc + trainer.action_key_pressed], 00h
        jmp executeEvents.second
    hit_first:
        hit first_trainerStruc, 8
        mov byte [second_trainerStruc + trainer.has_chosen], FALSE
        mov byte [second_trainerStruc + trainer.action_key_pressed], 00h
        ret