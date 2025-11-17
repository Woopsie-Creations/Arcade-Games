%macro assignAttack 3
section .data
attack_%1_%3:
    istruc attack
        at attack.name,      dw 0
        at attack.type,      db 0
        at attack.category,  db 0
        at attack.pp,        db 0
        at attack.max_pp,    db 0
        at attack.damage,    dw 0
        at attack.effect,    db 0
    iend

section .text
    lea si, [%2]
    lea di, [attack_%1_%3]
    mov cx, attack_size
    push di
    rep movsb
    pop di

    mov ax, di
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