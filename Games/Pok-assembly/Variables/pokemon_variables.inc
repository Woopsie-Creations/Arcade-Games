section .data
    struc pokemon
        .name: resw 1
        .type: resb 2 ; 2 types
        .sprite: resw 1
        .level: resb 3
        .genre: resb 1
        .hp: resw 1
        .max_hp: resw 1
        .attack_stat: resw 1
        .def_stat: resw 1
        .speattack_stat: resw 1
        .spedef_stat: resw 1
        .speed_stat: resw 1
        .attacks: resw 4
    endstruc

    first_onepokemonStruc:
        istruc pokemon
            at pokemon.name, dw bulbasaurName
            at pokemon.type, db 2, 7 
            at pokemon.sprite, dw BULBASAURB
            at pokemon.level, db 0,2,5
            at pokemon.genre, db 1
            at pokemon.hp, dw 45
            at pokemon.max_hp, dw 45
            at pokemon.attack_stat, dw 49
            at pokemon.def_stat, dw 49
            at pokemon.speattack_stat, dw 65
            at pokemon.spedef_stat, dw 65
            at pokemon.speed_stat, dw 45
            at pokemon.attacks, dw NULL, NULL, NULL, NULL
        iend
    first_twopokemonStruc:
        istruc pokemon
            at pokemon.name, dw ivysaurName
            at pokemon.type, db 2, 7 
            at pokemon.sprite, dw IVYSAURB
            at pokemon.level, db 0,5,0
            at pokemon.genre, db 1
            at pokemon.hp, dw 60
            at pokemon.max_hp, dw 60
            at pokemon.attack_stat, dw 62
            at pokemon.def_stat, dw 63
            at pokemon.speattack_stat, dw 80
            at pokemon.spedef_stat, dw 80
            at pokemon.speed_stat, dw 60
            at pokemon.attacks, dw NULL, NULL, NULL, NULL
        iend

    second_onepokemonStruc:
        istruc pokemon
            at pokemon.name, dw bulbasaurName
            at pokemon.type, db 2, 7 
            at pokemon.sprite, dw BULBASAURF
            at pokemon.level, db 0,2,5
            at pokemon.genre, db 1
            at pokemon.hp, dw 45
            at pokemon.max_hp, dw 45
            at pokemon.attack_stat, dw 49
            at pokemon.def_stat, dw 49
            at pokemon.speattack_stat, dw 65
            at pokemon.spedef_stat, dw 65
            at pokemon.speed_stat, dw 45
            at pokemon.attacks, dw NULL, NULL, NULL, NULL
        iend
    second_twopokemonStruc:
        istruc pokemon
            at pokemon.name, dw ivysaurName
            at pokemon.type, db 2, 7 
            at pokemon.sprite, dw IVYSAURF
            at pokemon.level, db 0,5,0
            at pokemon.genre, db 1
            at pokemon.hp, dw 60
            at pokemon.max_hp, dw 60
            at pokemon.attack_stat, dw 62
            at pokemon.def_stat, dw 63
            at pokemon.speattack_stat, dw 80
            at pokemon.spedef_stat, dw 80
            at pokemon.speed_stat, dw 60
            at pokemon.attacks, dw NULL, NULL, NULL, NULL
        iend