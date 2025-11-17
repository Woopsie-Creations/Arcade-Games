%macro checkKeys 6
    cmp ah, %2
    je %%checkTab
    ; can be an attack, so dealing with indexes
    mov si, 0
    cmp ah, %3
    je %%checkPPs
    mov si, 2
    cmp ah, %4
    je %%checkPPs
    mov si, 4
    cmp ah, %5
    je %%checkPPs
    mov si, 6
    cmp ah, %6
    je %%checkPPs
    jmp %%end
    %%checkTab:
        cmp byte [%1 + trainer.battle_tab], 0
        je %%end
        jmp %%change
    %%checkPPs:
        cmp byte [%1 + trainer.battle_tab], 0
        jne %%change
        ; get the attack's pp
        push si
        mov si, %1
        mov bl, [si + trainer.current_poke]
        xor bh, bh
        shl bx, 1
        add bx, trainer.pokemons
        mov bx, [si + bx]
        pop si
        mov bx, [bx + pokemon.attacks + si] ; and its attack
        mov bl, byte [bx + attack.pp]
        ; got the pps into bl
        cmp byte bl, 0
        je %%end
    %%change:
        mov byte [%1 + trainer.action_key_pressed], ah
        mov byte [%1 + trainer.has_chosen], TRUE
    %%end:
%endmacro

section .text
    readKeyboard:
        ; is key pressed ?
        mov ah, 01h 
        int 16h
        jz gameLoop ; if no, skip

        ; which key is pressed
        mov ah, 00h
        int 16h

        cmp ah, ESCAPE_KEY
        je exitProgram
        
        cmp ah, LEFT_ARROW
        je changeTab_first
        cmp ah, RIGHT_ARROW
        je changeTab_first
        
        checkKeys first_trainerStruc, I_KEY, J_KEY, N_KEY, K_KEY, M_KEY

        .second_player:
        cmp ah, A_KEY
        je changeTab_second
        cmp ah, D_KEY
        je changeTab_second

        checkKeys second_trainerStruc, T_KEY, F_KEY, C_KEY, G_KEY, V_KEY

        jmp gameLoop