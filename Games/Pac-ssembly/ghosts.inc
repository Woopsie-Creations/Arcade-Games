section .bss
    cage_amount_of_ghosts resb 1

    ghost_waiting_in_cage resb 4 ; 4 ghosts

section .text
    ghostBehavior:
        ; checkTimer current_time, expected_time, moveGhostsOutOfCage ; for cage behavior

        call ghostPattern
        call ghostMovement
        ret
    
    ghostMovement:
        add sp, 2
        mov cx, 4
        .eachGhostMovement:
            mov bx, cx
            push cx
            dec bx ; byte index
            mov ax, bx
            push bx
            shl ax, 1 ; word index
            mov di, ax

            colCalculations [ghost_y_pos+di], [ghost_y_speed+di], [ghost_x_pos+di], [ghost_x_speed+di], ghostCol

            pop bx
            mov cx, bx
            push cx
            dec bx ; byte index

            .doMovement:
                inc byte [ghost_animation_frame+bx]
                shl bx, 1
                mov ax, [ghost_x_speed+di]
                add word [ghost_x_pos+di], ax
                mov ax, [ghost_y_speed+di]
                add word [ghost_y_pos+di], ax

                jmp .endLoop

            .skipMovement:
                mov byte [col_test_nb], 1
                mov byte [ghost_animation_frame+bx], 8
                jmp .endLoop
            .tunnelTeleport:
                shl bx, 1

                cmp word [ghost_x_speed+bx], -1
                je .tpToRight
                sub word [ghost_x_pos+bx], WALL_WIDTH * 25
                jmp .endLoop
                .tpToRight:
                add word [ghost_x_pos+bx], WALL_WIDTH * 25
            .endLoop:
                pop cx
                dec cx
                jnz .eachGhostMovement
                xor si, si
                ret

    moveGhostsOutOfCage:
        cmp byte [cage_amount_of_ghosts], 0
        je .earlyExit

        mov cx, 4 ; 4 ghosts
        .eachGhost:
            mov bx, cx
            push cx
            dec bx ; byte index
            cmp byte [ghost_waiting_in_cage+bx], 0
            je .skipGhost
            
            push bx
            shl bx, 1

            ; move
            cmp word [ghost_x_pos+bx], MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 6
            je .checkY
            jl .moveXRight
            jg .moveXLeft

            .moveXRight:
                add word [ghost_x_pos+bx], 1

                pop bx
                add bx, 2 ; get accurate item index
                mov byte [item+bx], 2
                
                pop cx
                mov cx, 1
                jmp .continueLoop
                
            .moveXLeft:
                add word [ghost_x_pos+bx], -1

                pop bx
                add bx, 2 ; get accurate item index
                mov byte [item+bx], 6
                
                pop cx
                mov cx, 1
                jmp .continueLoop
                
            .checkY:
                ; mov ax, MAZE_Y_POS + WALL_HEIGHT * 11 - 3
                ; cmp word [ghost_y_pos+bx], ax
                ; je .outOfCage

                ; sub word [ghost_y_pos+bx], 1

                ; pop bx
                ; add bx, 2 ; get accurate item index
                ; mov byte [item+bx], 0
                
                ; pop cx
                ; mov cx, 1
                ; jmp .continueLoop

                mov word [ghost_y_speed+bx], -2

            .outOfCage:
                ; here is the next pattern (for now placeholder: going to the right)
                ; mov word [ghost_y_speed+bx], 0
                ; mov word [ghost_x_speed+bx], 2

                pop bx
                add bx, 2 ; get accurate item index
                mov byte [item+bx], 0
                sub bx, 2 ; re-get normal index

                mov byte [ghost_waiting_in_cage+bx], 0
                dec byte [cage_amount_of_ghosts]

                cmp byte [cage_amount_of_ghosts], 0
                je .skipGhost ; no need to redo a timer if there's no more ghost

                ; Schedule next run
                mov ax, [expected_time]
                add ax, [interval_ticks]
                mov [expected_time], ax

                mov dx, [expected_time+2]
                adc dx, [interval_ticks+2]
                mov [expected_time+2], dx

                pop cx
                mov cx, 1
                jmp .continueLoop
            
            .skipGhost:
                pop cx
            .continueLoop:
                dec cx
                jnz .eachGhost
            .earlyExit:
            ret

%include "ghostPattern.inc"
