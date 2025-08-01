section .bss
    current_attack_damage resw 1

section .data
    struc attack
        .name: resw 1
        .type: resb 1
        .category: resb 1 ; 0 = null, 1 = normal, 2 = special
        .damage: resw 1
        .effect: resb 1
    endstruc

    attack_tackle:
        istruc attack
            at attack.name, dw attackNameTackle
            at attack.type, db 0
            at attack.category, db 1
            at attack.damage, dw 40
            at attack.effect, db 0
        iend

    attack_tailwhip:
        istruc attack
            at attack.name, dw attackNameTailWhip
            at attack.type, db 0
            at attack.category, db 0
            at attack.damage, dw 0
            at attack.effect, db 1
        iend
    
    attack_bulletseed:
        istruc attack
            at attack.name, dw attackNameBulletseed
            at attack.type, db 4
            at attack.category, db 1
            at attack.damage, dw 20
            at attack.effect, db 0
        iend