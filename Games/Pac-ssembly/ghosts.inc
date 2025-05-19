%macro ghostsOutOfCage 0-* blinky, pinky, inky, clyde
    mov bx, 0
    %rep %0
        cmp byte [ghost_waiting_in_cage+bx], FALSE
        je %%continueLoop_%1
        cmp byte [has_init_timer_%1], TRUE
        je %%continueLoop_%1
        cmp word [expected_time_%1], -1
        je %%continueLoop_%1

        mov word [%1Struc + entity.y_speed], 0
        mov word [%1Struc + entity.x_speed], 0

        ; move
        cmp word [%1Struc + entity.x_pos], MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - WALL_WIDTH
        je %%checkY_%1
        jl %%moveXRight_%1
        jg %%moveXLeft_%1

        %%moveXRight_%1:
            mov word [%1Struc + entity.y_speed], 0
            mov word [%1Struc + entity.x_speed], 1
            jmp %%continueLoop_%1
            
        %%moveXLeft_%1:
            mov word [%1Struc + entity.y_speed], 0
            mov word [%1Struc + entity.x_speed], -1
            jmp %%continueLoop_%1
            
        %%checkY_%1:
            cmp word [%1Struc + entity.y_pos], MAZE_Y_POS + WALL_HEIGHT * 11 - 3
            je %%outOfCage_%1

            dec word [%1Struc + entity.y_pos]
            mov byte [%1Struc + entity.sprite_nb], 0
            jmp %%continueLoop_%1

        %%outOfCage_%1:
            ; here is the next pattern (for now placeholder: going to the right)
            mov word [%1Struc + entity.y_speed], 0
            mov word [%1Struc + entity.x_speed], 2
            ; move ghosts because of an offset from cage
            mov word ax, [blinkyStruc + entity.initial_x_pos]
            mov word [%1Struc + entity.x_pos], ax

            mov byte [ghost_waiting_in_cage+bx], FALSE
            mov byte [has_init_timer_%1], FALSE
            dec byte [cage_amount_of_ghosts]

            mov word [expected_time_%1], -1
    
        %%continueLoop_%1:
            inc bx
            %rotate 1
    %endrep
%endmacro

%macro ghostsInCage 0-* blinky, pinky, inky, clyde
    mov bx, 0
    %rep %0
        cmp byte [ghost_waiting_in_cage+bx], FALSE
        je %%continueLoop_%1

        mov word ax, [clydeStruc + entity.initial_x_pos]
        cmp word [%1Struc + entity.x_pos], ax
        jge %%goLeft_%1

        mov word ax, [inkyStruc + entity.initial_x_pos]
        cmp word [%1Struc + entity.x_pos], ax
        jle %%goRight_%1
        jmp %%continueLoop_%1

        %%goRight_%1:
            mov word [%1Struc + entity.x_speed], 1
            mov byte [%1Struc + entity.sprite_nb], 2
            jmp %%continueLoop_%1
        
        %%goLeft_%1:
            mov word [%1Struc + entity.x_speed], -1
            mov byte [%1Struc + entity.sprite_nb], 6

        %%continueLoop_%1:
            inc bx
            %rotate 1
    %endrep
%endmacro

section .bss
    cage_amount_of_ghosts resb 1

    ghost_waiting_in_cage resb 4 ; 4 ghosts
    ghost_needs_to_leave resb 4 ; 4 ghosts

section .text
    ghostBehavior:
        checkGhostTimers
        call ghostPattern
        ret

    moveGhostsOutOfCage:
        cmp byte [cage_amount_of_ghosts], 0
        je .earlyExit

        ghostsInCage
        ghostsOutOfCage

        .earlyExit:
            ret

%include "ghostPattern.inc"
