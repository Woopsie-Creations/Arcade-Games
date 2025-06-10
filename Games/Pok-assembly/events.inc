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

%macro changePoke 1
    cmp byte [%1 + trainer.current_poke], 1
    je %%isOne
    mov byte [%1 + trainer.current_poke], 1
    jmp %%end
    %%isOne:
    mov byte [%1 + trainer.current_poke], 0
    %%end:
    call displayFrame
%endmacro

section .text
    changePoke_first:
        changePoke first_trainerStruc
        jmp gameLoop
    changePoke_second:
        changePoke second_trainerStruc
        jmp gameLoop
    hit_first:
        hit first_trainerStruc, 2
        jmp gameLoop
    hit_second:
        hit second_trainerStruc, 2
        jmp gameLoop