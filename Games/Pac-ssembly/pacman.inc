%macro colTest 6
    %6:
        mov ax, %1
        sub ax, %4
        cmp %2, -2
        jne .testOtherSide
        add ax, 2
        jmp .endCol
        .testOtherSide:
        cmp %2, 2
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

%macro colVerifier 1
    cmp al, 32
    je .tunnelTeleport
    cmp al, 33
    je .tunnelTeleport
    cmp al, 35 ; super gum
    je %1
    cmp al, 36 ; gum
    je %1
    cmp al, 37
    je %1
    jmp .skipMovement
%endmacro

%macro pacmanAnimationSide 2
    %1:
        cmp byte [pacman_animation_frame], 2
        je .pacmanFrame1
        cmp byte [pacman_animation_frame], 4
        je .pacmanFrame2
        cmp byte [pacman_animation_frame], 6
        je .pacmanFrame3
        cmp byte [pacman_animation_frame], 8
        je .pacmanFrame4
        ret
        .pacmanFrame1:
            mov byte [item+0], %2 + 1
            ret
        .pacmanFrame2:
            mov byte [item+0], %2
            ret
        .pacmanFrame3:
            mov byte [item+0], 0
            ret
        .pacmanFrame4:
            mov byte [item+0], %2
            jmp .endAnimation
        .endAnimation:
        mov byte [pacman_animation_frame], 0
        ret
%endmacro

section .text
    secondCollisionTest:
        cmp byte [buffered_col_test], 0
        je continueDirection
    pacmanMovement:
        cmp byte [movement_buffered], 0
        je continueDirection
        mov byte [buffered_col_test], 1
        mov dx, [pacman_x_speed_buffer]
        push dx
        mov dx, [pacman_y_speed_buffer]
        jmp collisionCalculations

        continueDirection:
        mov byte [buffered_col_test], 0
        mov dx, [pacman_x_speed]
        push dx
        mov dx, [pacman_y_speed]

        collisionCalculations:
        colTest [pacman_y_pos], dx, [col_test_nb], MAZE_Y_POS, WALL_HEIGHT, colY
        mov bx, COLUMN_NUMBER
        xor dx, dx
        mul bx
        pop dx

        push ax
        colTest [pacman_x_pos], dx, [col_test_nb], MAZE_X_POS, WALL_WIDTH, colX
        mov bx, ax
        pop ax

        add bx, ax
        mov al, [maze+bx]
        cmp byte [col_test_nb], 1
        jne .secondColTest
        mov byte [col_test_nb], 2
        colVerifier secondCollisionTest
        .secondColTest:
        mov byte [col_test_nb], 1
        colVerifier .doMovement

        .doMovement:
            call pacmanEatingGum
            inc byte [pacman_animation_frame]
            cmp byte [buffered_col_test], 0
            je .normalMovement
            mov byte [movement_buffered], 0
            mov ax, [pacman_x_speed_buffer]
            mov word [pacman_x_speed], ax
            mov ax, [pacman_y_speed_buffer]
            mov word [pacman_y_speed], ax
            .normalMovement:
            mov ax, [pacman_x_speed]
            add word [pacman_x_pos], ax
            mov ax, [pacman_y_speed]
            add word [pacman_y_pos], ax
            ret
        .skipMovement:
            mov byte [col_test_nb], 1
            cmp byte [buffered_col_test], 1
            je continueDirection
            mov byte [pacman_animation_frame], 8
            ret
        .tunnelTeleport:
            inc byte [pacman_animation_frame]
            cmp word [pacman_x_speed], -2
            je .tpToRight
            sub word [pacman_x_pos], WALL_WIDTH * 25
            ret
            .tpToRight:
            add word [pacman_x_pos], WALL_WIDTH * 25
            ret

    pacmanAnimation:
        cmp word [pacman_y_speed], -2
        je animationUp
        cmp word [pacman_x_speed], 2
        je animationRight
        cmp word [pacman_y_speed], 2
        je animationDown
        cmp word [pacman_x_speed], -2
        je animationLeft
            pacmanAnimationSide animationUp, 1
            pacmanAnimationSide animationRight, 3
            pacmanAnimationSide animationDown, 5
            pacmanAnimationSide animationLeft, 7
        
    pacmanEatingGum:
        xor dx, dx
        cmp al, 35 ; super gum
        je .eraseSuperGum
        cmp al, 36 ; gum
        je .eraseGum
        ret
        .eraseSuperGum:
        dec byte [MAZE_AMOUNT_OF_GUMS]
        mov byte [maze+bx], 37
        addToScore 50
        ret
        .eraseGum:
        dec byte [MAZE_AMOUNT_OF_GUMS]
        mov byte [maze+bx], 37
        addToScore 10
        ret
