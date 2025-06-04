section .text
    ghostPattern:
        call blinkyPattern
        call pinkyPattern
        call inkyPattern
        call clydePattern
        ret

    blinkyPattern:
        cmp byte [ghost_waiting_in_cage+0], TRUE
        je .skipGhost
        cmp byte [current_mode], 1
        je .skipGhost

        mov bx, blinkyStruc

        call rng
        
        cmp dl, 0
        je .goUp
        cmp dl, 1
        je .goRight
        cmp dl, 2
        je .goDown
        cmp dl, 3
        je .goLeft
        jmp blinkyPattern

        .goUp:
            cmp word [bx + entity.y_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], -2
            jmp .skipGhost

        .goRight:
            cmp word [bx + entity.x_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 2
            mov word [bx + entity.y_speed_buffer], 0
            jmp .skipGhost

        .goDown:
            cmp word [bx + entity.y_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], 2
            jmp .skipGhost

        .goLeft:
            cmp word [bx + entity.x_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], -2
            mov word [bx + entity.y_speed_buffer], 0
            jmp .skipGhost

        .skipGhost:
        ret

    pinkyPattern:
        cmp byte [ghost_waiting_in_cage+1], TRUE
        je .skipGhost

        mov bx, pinkyStruc
        
        call rng
        
        cmp dl, 0
        je .goUp
        cmp dl, 1
        je .goRight
        cmp dl, 2
        je .goDown
        cmp dl, 3
        je .goLeft
        jmp pinkyPattern

        .goUp:
            cmp word [bx + entity.y_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], -2
            jmp .skipGhost

        .goRight:
            cmp word [bx + entity.x_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 2
            mov word [bx + entity.y_speed_buffer], 0
            jmp .skipGhost

        .goDown:
            cmp word [bx + entity.y_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], 2
            jmp .skipGhost

        .goLeft:
            cmp word [bx + entity.x_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], -2
            mov word [bx + entity.y_speed_buffer], 0

        .skipGhost:
        ret

    inkyPattern:
        cmp byte [ghost_waiting_in_cage+2], TRUE
        je .skipGhost

        mov bx, inkyStruc
        
        call rng
        
        cmp dl, 0
        je .goUp
        cmp dl, 1
        je .goRight
        cmp dl, 2
        je .goDown
        cmp dl, 3
        je .goLeft
        jmp inkyPattern

        .goUp:
            cmp word [bx + entity.y_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], -2
            jmp .skipGhost

        .goRight:
            cmp word [bx + entity.x_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 2
            mov word [bx + entity.y_speed_buffer], 0
            jmp .skipGhost

        .goDown:
            cmp word [bx + entity.y_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], 2
            jmp .skipGhost

        .goLeft:
            cmp word [bx + entity.x_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], -2
            mov word [bx + entity.y_speed_buffer], 0
        
        .skipGhost:
        ret

    clydePattern:
        cmp byte [ghost_waiting_in_cage+3], TRUE
        je .skipGhost

        mov bx, clydeStruc

        call rng
        
        cmp dl, 0
        je .goUp
        cmp dl, 1
        je .goRight
        cmp dl, 2
        je .goDown
        cmp dl, 3
        je .goLeft
        jmp clydePattern

        .goUp:
            cmp word [bx + entity.y_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], -2
            jmp .skipGhost

        .goRight:
            cmp word [bx + entity.x_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 2
            mov word [bx + entity.y_speed_buffer], 0
            jmp .skipGhost

        .goDown:
            cmp word [bx + entity.y_speed], -2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], 0
            mov word [bx + entity.y_speed_buffer], 2
            jmp .skipGhost

        .goLeft:
            cmp word [bx + entity.x_speed], 2
            je .skipGhost
            mov byte [bx + entity.movement_buffered], TRUE
            mov word [bx + entity.x_speed_buffer], -2
            mov word [bx + entity.y_speed_buffer], 0
            
        .skipGhost:
        ret
    
    rng:
        mov ah, 0
        int 1Ah
        add dl, cl
        and dl, 3 ; from 0 to 3 -> 4 diff num
        ret
