%macro checkKeys 6
    cmp ah, %2
    je %%check
    cmp ah, %3
    je %%change
    cmp ah, %4
    je %%change
    cmp ah, %5
    je %%change
    cmp ah, %6
    je %%change
    jmp %%end
    %%check:
        cmp byte [%1 + trainer.battle_tab], 0
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
        
        checkKeys first_trainerStruc, I_KEY, J_KEY, K_KEY, N_KEY, M_KEY

        .second_player:
        cmp ah, A_KEY
        je changeTab_second
        cmp ah, D_KEY
        je changeTab_second

        checkKeys second_trainerStruc, T_KEY, F_KEY, G_KEY, C_KEY, V_KEY

        jmp gameLoop