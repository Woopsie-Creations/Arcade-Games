%macro behaviorTestCol 1
    push bx
    colTest [bx + entity.y_pos], [bx + entity.y_speed_buffer], MAZE_Y_POS, WALL_HEIGHT
    mov bx, COLUMN_NUMBER
    xor dx, dx
    mul bx
    pop bx
    push bx
    push ax

    colTest [bx + entity.x_pos], [bx + entity.x_speed_buffer], MAZE_X_POS, WALL_WIDTH
    mov bx, ax
    pop ax
    add bx, ax
    mov al, [maze+bx]
    pop bx

    cmp al, 35
    jge .continueDirection
    
    cmp word [bx + entity.x_speed_buffer], 0
    je %1.xCoordTest
    cmp word [bx + entity.y_speed_buffer], 0
    je %1.yCoordTest

    .continueDirection:
%endmacro

section .text
    goUp:
        cmp word [bx + entity.y_speed_buffer], 2
        je .skip
        cmp word [bx + entity.y_speed], 2
        je .skip
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], 0
        mov word [bx + entity.y_speed_buffer], -2
        .skip:
        ret

    goRight:
        cmp word [bx + entity.x_speed_buffer], -2
        je .skip
        cmp word [bx + entity.x_speed], -2
        je .skip
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], 2
        mov word [bx + entity.y_speed_buffer], 0
        .skip:
        ret

    goDown:
        cmp word [bx + entity.y_speed_buffer], -2
        je .skip
        cmp word [bx + entity.y_speed], -2
        je .skip
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], 0
        mov word [bx + entity.y_speed_buffer], 2
        .skip:
        ret

    goLeft:
        cmp word [bx + entity.x_speed_buffer], 2
        je .skip
        cmp word [bx + entity.x_speed], 2
        je .skip
        mov byte [bx + entity.movement_buffered], TRUE
        mov word [bx + entity.x_speed_buffer], -2
        mov word [bx + entity.y_speed_buffer], 0
        .skip:
        ret 

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
        behaviorTestCol blinkyPattern
        
        .xCoordTest:
        mov word ax, [blinkyStruc + entity.x_pos]
        mov word dx, [pacmanStruc + entity.x_pos]
        cmp dx, ax
        jl goLeft
        jg goRight
        je .yCoordTest
        
        .yCoordTest:
        mov word ax, [blinkyStruc + entity.y_pos]
        mov word dx, [pacmanStruc + entity.y_pos]
        cmp dx, ax
        jl goUp
        jg goDown
        je .xCoordTest

        .skipGhost:
        ret

    pinkyPattern:
        cmp byte [ghost_waiting_in_cage+1], TRUE
        je .skipGhost

        mov bx, pinkyStruc
        
        jmp goRight
        .skipGhost:
        ret

    inkyPattern:
        cmp byte [ghost_waiting_in_cage+2], TRUE
        je .skipGhost

        mov bx, inkyStruc
        
        jmp goLeft
        .skipGhost:
        ret

    clydePattern:
        cmp byte [ghost_waiting_in_cage+3], TRUE
        je .skipGhost

        mov bx, clydeStruc
        
        jmp goRight
        .skipGhost:
        ret
