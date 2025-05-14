%macro ghost_colTest 6
    %6:
        mov ax, %1
        sub ax, %4
        cmp word %2, -2
        jne .testOtherSide
        add ax, 2
        jmp .endCol
        .testOtherSide:
        cmp word %2, 2
        jne .sideCol
        add ax, 9
        jmp .endCol
        .sideCol:
        cmp byte %3, 1
        je .firstSideCol
        add ax, 5
        .firstSideCol:
        add ax, 3
        .endCol:
        mov bx, %5
        xor dx, dx
        div bx
%endmacro

%macro ghost_colVerifier 1
    cmp al, 32
    je .tunnelTeleport
    cmp al, 33
    je .tunnelTeleport
    cmp al, 34
    je %1
    cmp al, 35
    je %1
    cmp al, 36
    je %1
    cmp al, 37
    je %1
    jmp .skipMovement
%endmacro

%macro ghostAnimationSide 2
    %1:
        pop bx
        cmp byte [ghost_animation_frame+bx], 1
        je .ghostFrame1
        cmp byte [ghost_animation_frame+bx], 3
        je .ghostFrame2
        cmp byte [ghost_animation_frame+bx], 5
        je .ghostFrame3
        cmp byte [ghost_animation_frame+bx], 7
        je .ghostFrame4
        dec cx
        jnz eachGhostAnimation
        ret
        .ghostFrame1:
            mov byte [item+bx+2], %2
            dec cx
            jnz eachGhostAnimation
            ret
        .ghostFrame2:
            mov byte [item+bx+2], %2
            dec cx
            jnz eachGhostAnimation
            ret
        .ghostFrame3:
            mov byte [item+bx+2], %2
            dec cx
            jnz eachGhostAnimation
            ret
        .ghostFrame4:
            mov byte [item+bx+2], %2
            jmp .endAnimation
        .endAnimation:
            mov byte [ghost_animation_frame+bx], 0
            dec cx
            jnz eachGhostAnimation
        ret
%endmacro

section .bss
    cage_amount_of_ghosts resb 1

    ghost_waiting_in_cage resb 4 ; 4 ghosts

section .text
    ghostBehavior:
        call checkTimer ; for cage behavior

        call ghostPattern
        call ghostMovement
        ret
    
    ghostMovement:
        add sp, 2
        mov cx, 4
        eachGhostMovement:
            mov bx, cx
            push cx
            dec bx ; byte index
            mov ax, bx
            push bx
            shl ax, 1 ; word index
            mov si, ax

            ghost_colTest [ghost_y_pos+si], [ghost_y_speed+si], [ghost_col_test_nb+bx], MAZE_Y_POS, WALL_HEIGHT, ghost_colY
            mov bx, COLUMN_NUMBER
            xor dx, dx
            mul bx
            pop bx ; byte index
            push ax

            ghost_colTest [ghost_x_pos+si], [ghost_x_speed+si], [ghost_col_test_nb+bx], MAZE_X_POS, WALL_WIDTH, ghost_colX
            mov bx, ax
            pop ax

            add bx, ax
            mov al, [maze+bx]

            pop bx
            mov cx, bx
            push cx
            dec bx ; byte index

            cmp byte [ghost_col_test_nb+bx], 1
            jne .secondColTest
            mov byte [ghost_col_test_nb+bx], 2
            ghost_colVerifier ghostMovement
            .secondColTest:
            mov byte [ghost_col_test_nb+bx], 1
            ghost_colVerifier .doMovement
            jmp .endLoop

            .doMovement:
                inc byte [ghost_animation_frame+bx]
                shl bx, 1
                mov ax, [ghost_x_speed+bx]
                add word [ghost_x_pos+bx], ax
                mov ax, [ghost_y_speed+bx]
                add word [ghost_y_pos+bx], ax

                jmp .endLoop

            .skipMovement:
                mov byte [ghost_col_test_nb+bx], 1
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
                jnz eachGhostMovement
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
    
    ghostAnimation:
        mov cx, 4
        eachGhostAnimation:
            mov bx, cx
            dec bx ; byte index
            mov ax, bx
            shl ax, 1 ; word index
            push bx
            mov bx, ax
            cmp word [ghost_y_speed+bx], 0
            jl ghost_animationUp
            jg ghost_animationDown
            cmp word [ghost_x_speed+bx], 0
            jg ghost_animationRight
            jl ghost_animationLeft
                ghostAnimationSide ghost_animationUp, 0
                ghostAnimationSide ghost_animationRight, 2
                ghostAnimationSide ghost_animationDown, 4
                ghostAnimationSide ghost_animationLeft, 6
            ret

%include "ghostPattern.inc"
