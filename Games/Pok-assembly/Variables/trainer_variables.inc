section .data
    struc trainer
        .name: resw 1
        .sprite: resw 1
        .current_poke: resb 1 ; index in his pokemon list
        .pokemons: resw 6
        ; .items: resw 5
    endstruc

    first_trainerStruc:
        istruc trainer
            at trainer.name, dw 0
            at trainer.sprite, dw 0
            at trainer.current_poke, db 0
            at trainer.pokemons, dw NULL, NULL, NULL, NULL, NULL, NULL
        iend
    second_trainerStruc:
        istruc trainer
            at trainer.name, dw 0
            at trainer.sprite, dw 0
            at trainer.current_poke, db 0
            at trainer.pokemons, dw NULL, NULL, NULL, NULL, NULL, NULL
        iend