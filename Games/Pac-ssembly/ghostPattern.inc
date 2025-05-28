%macro behaviorTestCol 2
    push bx
    colTest [bx + entity.y_pos], [bx + entity.%1], MAZE_Y_POS, WALL_HEIGHT
    mov bx, COLUMN_NUMBER
    xor dx, dx
    mul bx
    pop bx
    push bx
    push ax

    colTest [bx + entity.x_pos], [bx + entity.%2], MAZE_X_POS, WALL_WIDTH
    mov bx, ax
    pop ax
    add bx, ax
    mov al, [maze+bx]
    pop bx
%endmacro

section .text
    goUp:
        cmp word [bx + entity.y_speed], 0
        jne blinkyPattern.skipGhost
        cmp word [bx + entity.x_speed], 0
        je .testCol
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], 0
        mov word [bx + entity.y_speed_buffer], -2
        cmp byte [blinky_stuck], TRUE
        je .testCol
        jmp blinkyPattern.skipGhost
        .testCol:
        behaviorTestCol y_speed_buffer, x_speed_buffer
        cmp al, 35
        jl goDown
        mov word [bx + entity.x_speed], 0
        mov word [bx + entity.y_speed], -2
        mov byte [blinky_stuck], FALSE
        jmp blinkyPattern.skipGhost

    goRight:
        cmp word [bx + entity.x_speed], 0
        jne blinkyPattern.yCoordTest
        cmp word [bx + entity.y_speed], 0
        je .testCol
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], 2
        mov word [bx + entity.y_speed_buffer], 0
        cmp byte [blinky_stuck], TRUE
        je .testCol
        jmp blinkyPattern.yCoordTest
        .testCol:
        behaviorTestCol y_speed_buffer, x_speed_buffer
        cmp al, 35
        jl goLeft
        mov word [bx + entity.x_speed], 2
        mov word [bx + entity.y_speed], 0
        mov byte [blinky_stuck], FALSE
        jmp blinkyPattern.yCoordTest

    goDown:
        cmp word [bx + entity.y_speed], 0
        jne blinkyPattern.skipGhost
        cmp word [bx + entity.x_speed], 0
        je .testCol
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], 0
        mov word [bx + entity.y_speed_buffer], 2
        cmp byte [blinky_stuck], TRUE
        je .testCol
        jmp blinkyPattern.skipGhost
        .testCol:
        behaviorTestCol y_speed_buffer, x_speed_buffer
        cmp al, 35
        jl goUp
        mov word [bx + entity.x_speed], 0
        mov word [bx + entity.y_speed], 2
        mov byte [blinky_stuck], FALSE
        jmp blinkyPattern.skipGhost

    goLeft:
        cmp word [bx + entity.x_speed], 0
        jne blinkyPattern.yCoordTest
        cmp word [bx + entity.y_speed], 0
        je .testCol
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], -2
        mov word [bx + entity.y_speed_buffer], 0
        cmp byte [blinky_stuck], TRUE
        je .testCol
        jmp blinkyPattern.yCoordTest
        .testCol:
        behaviorTestCol y_speed_buffer, x_speed_buffer
        cmp al, 35
        jl goRight
        mov word [bx + entity.x_speed], -2
        mov word [bx + entity.y_speed], 0
        mov byte [blinky_stuck], FALSE
        jmp blinkyPattern.yCoordTest

    ghostPattern:
        call blinkyPattern
        call pinkyPattern
        call inkyPattern
        call clydePattern
        ret

    blinkyPattern:
        cmp byte [ghost_waiting_in_cage+0], TRUE
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
        
        .xCoordTest:
        cmp byte [blinky_stuck], TRUE
        je goLeft
        mov word ax, [blinkyStruc + entity.x_pos]
        mov word dx, [pacmanStruc + entity.x_pos]
        cmp dx, ax
        jl goLeft
        jg goRight
        
        .yCoordTest:
        cmp byte [blinky_stuck], TRUE
        je goUp
        mov word ax, [blinkyStruc + entity.y_pos]
        mov word dx, [pacmanStruc + entity.y_pos]
        cmp dx, ax
        jl goUp
        jg goDown

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
