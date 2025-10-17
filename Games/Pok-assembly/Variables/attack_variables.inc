section .bss
    current_attack_damage resw 1

section .data
    struc attack
        .name: resw 1
        .type: resb 1
        .category: resb 1 ; 0 = null, 1 = normal, 2 = special
        .pp: resb 1
        .max_pp: resb 1
        .damage: resw 1
        .effect: resb 1
    endstruc

    attack_tackle_template:
        dw attackNameTackle ; name
        db 0 ; type
        db 1 ; category
        db 25 ; pp
        db 25 ; max_pp
        dw 40 ; damage
        db 0 ; effect

    attack_tailwhip_template:
        dw attackNameTailWhip ; name
        db 0 ; type
        db 0 ; category
        db 30 ; pp
        db 30 ; max_pp
        dw 0 ; damage
        db 1 ; effect

    attack_bulletseed_template:
        dw attackNameBulletseed ; name
        db 4 ; type
        db 1 ; category
        db 30 ; pp
        db 30 ; max_pp
        dw 20 ; damage
        db 0 ; effect

    attack_sludgebomb_template:
        dw attackNameSludgeBomb ; name
        db 7 ; type
        db 2 ; category
        db 10 ; pp
        db 10 ; max_pp
        dw 90 ; damage
        db 0 ; effect

    attack_sunnyday_template:
        dw attackNameSunnyDay ; name
        db 1 ; type
        db 0 ; category
        db 5 ; pp
        db 5 ; max_pp
        dw 0 ; damage
        db 2 ; effect
