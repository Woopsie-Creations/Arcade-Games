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

    ; attack_tackle:
    ;     istruc attack
    ;         at attack.name, dw attackNameTackle
    ;         at attack.type, db 0
    ;         at attack.category, db 1
    ;         at attack.pp, db 25
    ;         at attack.max_pp, db 25
    ;         at attack.damage, dw 40
    ;         at attack.effect, db 0
    ;     iend

    attack_tailwhip_template:
        dw attackNameTailWhip ; name
        db 0 ; type
        db 0 ; category
        db 30 ; pp
        db 30 ; max_pp
        dw 0 ; damage
        db 1 ; effect

    ; attack_tailwhip:
    ;     istruc attack
    ;         at attack.name, dw attackNameTailWhip
    ;         at attack.type, db 0
    ;         at attack.category, db 0
    ;         at attack.pp, db 30
    ;         at attack.max_pp, db 30
    ;         at attack.damage, dw 0
    ;         at attack.effect, db 1
    ;     iend

    attack_bulletseed_template:
        dw attackNameBulletseed ; name
        db 4 ; type
        db 1 ; category
        db 15 ; pp
        db 15 ; max_pp
        dw 20 ; damage
        db 0 ; effect
    
    ; attack_bulletseed:
    ;     istruc attack
    ;         at attack.name, dw attackNameBulletseed
    ;         at attack.type, db 4
    ;         at attack.category, db 1
    ;         at attack.pp, db 15
    ;         at attack.max_pp, db 15
    ;         at attack.damage, dw 20
    ;         at attack.effect, db 0
    ;     iend