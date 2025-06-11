%macro initPokes 7
    mov ax, %2
    mov word [%1 + trainer.pokemons], ax
    mov ax, %3
    mov word [%1 + trainer.pokemons + 2], ax
    mov ax, %4
    mov word [%1 + trainer.pokemons + 4], ax
    mov ax, %5
    mov word [%1 + trainer.pokemons + 6], ax
    mov ax, %6
    mov word [%1 + trainer.pokemons + 8], ax
    mov ax, %7
    mov word [%1 + trainer.pokemons + 10], ax
%endmacro