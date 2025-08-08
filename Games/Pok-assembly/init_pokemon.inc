%macro assignAttack 4
    lea si, %2
    lea di, [%3] ; destination buffer
    mov cx, ATTACK_SIZE
    %%copy_loop:
        lodsb
        stosb
        loop %%copy_loop
    mov word [%1 + pokemon.attacks + %4], di
%endmacro

%macro initPokeAttacks 9
    assignAttack %1, %2, %6, 0
    assignAttack %1, %3, %7, 2
    assignAttack %1, %4, %8, 4
    assignAttack %1, %5, %9, 6
%endmacro

%macro assignPoke 3
    mov ax, %2
    mov word [%1 + trainer.pokemons + %3], ax
%endmacro

%macro initPokes 7
    assignPoke %1, %2, 0
    assignPoke %1, %3, 2
    assignPoke %1, %4, 4
    assignPoke %1, %5, 6
    assignPoke %1, %6, 8
    assignPoke %1, %7, 10
%endmacro