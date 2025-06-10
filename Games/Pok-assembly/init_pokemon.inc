%macro initPokes 3
    mov ax, %2
    mov word [%1 + trainer.pokemons], ax
    mov ax, %3
    mov word [%1 + trainer.pokemons + 2], ax
%endmacro