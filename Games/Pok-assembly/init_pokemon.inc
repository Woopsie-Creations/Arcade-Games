%macro assignAttack 3
    mov ax, %2
    mov word [%1 + pokemon.attacks + %3], ax
%endmacro

%macro initPokeAttacks 5
    assignAttack %1, %2, 0
    assignAttack %1, %3, 2
    assignAttack %1, %4, 4
    assignAttack %1, %5, 6
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