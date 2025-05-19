section .text
    ghostPattern:
        mov bx, 0
        call blinkyPattern
        inc bx
        call pinkyPattern
        inc bx
        call inkyPattern
        inc bx
        call clydePattern
        ret

    blinkyPattern:
        cmp byte [ghost_waiting_in_cage+bx], TRUE
        je .skipGhost

        mov word [blinkyStruc + entity.x_speed], -2
        mov word [blinkyStruc + entity.y_speed], 0
        .skipGhost:
        ret

    pinkyPattern:
        cmp byte [ghost_waiting_in_cage+bx], TRUE
        je .skipGhost
        
        mov word [pinkyStruc + entity.x_speed], 2
        mov word [pinkyStruc + entity.y_speed], 0
        .skipGhost:
        ret

    inkyPattern:
        cmp byte [ghost_waiting_in_cage+bx], TRUE
        je .skipGhost
        
        mov word [inkyStruc + entity.x_speed], -2
        mov word [inkyStruc + entity.y_speed], 0
        .skipGhost:
        ret

    clydePattern:
        cmp byte [ghost_waiting_in_cage+bx], TRUE
        je .skipGhost
        
        mov word [clydeStruc + entity.x_speed], 2
        mov word [clydeStruc + entity.y_speed], 0
        .skipGhost:
        ret
