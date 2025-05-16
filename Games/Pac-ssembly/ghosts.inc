%macro ghostsOutOfCage 0-* blinky, pinky, inky, clyde
    mov bx, 0
    %rep 4
        push bx
        cmp byte [ghost_waiting_in_cage+bx], FALSE
        je %%continueLoop_%1

        mov word [%1Struc + entity.x_speed], 0
        mov word [%1Struc + entity.y_speed], 0
        ; move
        cmp word [%1Struc + entity.x_pos], MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - WALL_WIDTH
        je %%checkY_%1
        jl %%moveXRight_%1
        jg %%moveXLeft_%1

        %%moveXRight_%1:
            inc word [%1Struc + entity.x_pos]
            mov byte [%1Struc + entity.sprite_nb], 2
            jmp %%continueLoop_%1
            
        %%moveXLeft_%1:
            dec word [%1Struc + entity.x_pos]
            mov byte [%1Struc + entity.sprite_nb], 6
            jmp %%continueLoop_%1
            
        %%checkY_%1:
            mov ax, MAZE_Y_POS + WALL_HEIGHT * 11 - 3
            cmp word [%1Struc + entity.y_pos], ax
            je %%outOfCage_%1

            dec word [%1Struc + entity.y_pos]
            ; mov byte [%1Struc + entity.sprite_nb], 0
            jmp %%continueLoop_%1

        %%outOfCage_%1:
            ; here is the next pattern (for now placeholder: going to the right)
            mov word [%1Struc + entity.y_speed], 0
            mov word [%1Struc + entity.x_speed], 2
            ; move ghosts because of an offset from cage
            dec word [%1 + entity.x_pos]

            pop bx
            mov byte [ghost_waiting_in_cage+bx], FALSE
            push bx
            dec byte [cage_amount_of_ghosts]

            cmp byte [cage_amount_of_ghosts], 0
            je %%continueLoop_%1 ; no need to redo a timer if there's no more ghost

            ; Schedule next run
            ; Times specific to ghosts
            ; mov ax, [expected_time]
            ; add ax, [interval_ticks]
            ; mov [expected_time], ax

            ; mov dx, [expected_time+2]
            ; adc dx, [interval_ticks+2]
            ; mov [expected_time+2], dx
    
        %%continueLoop_%1:
            pop bx
            inc bx
            %rotate 1
    %endrep
%endmacro

section .bss
    cage_amount_of_ghosts resb 1

    ghost_waiting_in_cage resb 4 ; 4 ghosts

section .text
    ghostBehavior:
        ; checkTimer current_time, expected_time, moveGhostsOutOfCage ; for cage behavior
        call moveGhostsOutOfCage
        call ghostPattern
        ret

    moveGhostsOutOfCage:
        cmp byte [cage_amount_of_ghosts], 0
        je .earlyExit

        ghostsOutOfCage

        .earlyExit:
            ret

%include "ghostPattern.inc"
