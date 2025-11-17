section .data
    struc trainer
        .name: resw 1
        .sprite: resw 1
        .current_poke: resb 1 ; index in his pokemon list
        .has_chosen: resb 1
        .action_key_pressed: resb 1 ; ascii code pressed
        .battle_tab: resb 1 ; 0 = attacks, 1 = pokemons, 2 = bag
        .pokemons: resw 6
        ; .items: resw 5
    endstruc

    first_trainerStruc:
        istruc trainer
            at trainer.name, dw 0
            at trainer.sprite, dw 0
            at trainer.current_poke, db 0
            at trainer.has_chosen, db FALSE
            at trainer.action_key_pressed, db 00h
            at trainer.battle_tab, db 0
            at trainer.pokemons, dw NULL, NULL, NULL, NULL, NULL, NULL
        iend
    second_trainerStruc:
        istruc trainer
            at trainer.name, dw 0
            at trainer.sprite, dw 0
            at trainer.current_poke, db 0
            at trainer.has_chosen, db FALSE
            at trainer.action_key_pressed, db 00h
            at trainer.battle_tab, db 1
            at trainer.pokemons, dw NULL, NULL, NULL, NULL, NULL, NULL
        iend