%macro colTest 4
        mov ax, %1
        sub ax, %3
        cmp word %2, -2
        jne %%testOtherSide
        add ax, 2
        jmp %%endCol
        %%testOtherSide:
        cmp word %2, 2
        jne %%sideCol
        add ax, 9
        jmp %%endCol
        %%sideCol:
        cmp byte [col_test_nb], 1
        je %%firstSideCol
        add ax, 5
        %%firstSideCol:
        add ax, 3
        %%endCol:
        mov bx, %4
        xor dx, dx
        div bx
%endmacro

%macro colCalculations 5
    colTest %1, %2, MAZE_Y_POS, WALL_HEIGHT
    mov bx, COLUMN_NUMBER
    xor dx, dx
    mul bx
    push ax

    colTest %3, %4, MAZE_X_POS, WALL_WIDTH
    mov bx, ax
    pop ax
    add bx, ax
    mov al, [maze+bx]

    cmp byte [col_test_nb], 1
    jne %%secondColTest
    mov byte [col_test_nb], 2
    colVerifier secondCollisionTest_%5, %5
    %%secondColTest:
    mov byte [col_test_nb], 1
    colVerifier doMovement_%5, %5
%endmacro

%macro colVerifier 2
    cmp al, 32
    je tunnelTeleport_%2
    cmp al, 33
    je tunnelTeleport_%2
    cmp al, 35 ; super gum
    je %1
    cmp al, 36 ; gum
    je %1
    cmp al, 37
    je %1
    cmp al, 38
    je %1
    jmp skipMovement_%2
%endmacro

%macro movements 0-* pacman, blinky, pinky, inky, clyde
    %rep 5
        jmp movement_%1
        secondCollisionTest_%1:
            cmp byte [buffered_col_test], FALSE
            je continueDirection_%1
        movement_%1:
            ; cmp %1, pacman
            ; jne skipOutOfBounds_%1
            cmp word [%1Struc + entity.x_pos], MAZE_X_POS
            jbe doMovement_%1
            cmp word [%1Struc + entity.x_pos], MAZE_X_POS+COLUMN_NUMBER*WALL_WIDTH-ENTITY_SPRITE_WIDTH
            jae doMovement_%1
            skipOutOfBounds_%1:
            cmp byte [%1Struc + entity.movement_buffered], FALSE
            je continueDirection_%1
            mov byte [buffered_col_test], TRUE
            colCalculations [%1Struc + entity.y_pos], [%1Struc + entity.y_speed_buffer], [%1Struc + entity.x_pos], [%1Struc + entity.x_speed_buffer], %1

            continueDirection_%1:
            mov byte [buffered_col_test], FALSE
            colCalculations [%1Struc + entity.y_pos], [%1Struc + entity.y_speed], [%1Struc + entity.x_pos], [%1Struc + entity.x_speed], %1

            doMovement_%1:
                ; cmp %1, pacman
                ; jne skipGums_%1
                call pacmanEating
                skipGums_%1:
                inc byte [%1Struc + entity.animation_frame]
                cmp byte [buffered_col_test], FALSE
                je normalMovement_%1
                mov byte [%1Struc + entity.movement_buffered], FALSE
                mov ax, [%1Struc + entity.x_speed_buffer]
                mov word [%1Struc + entity.x_speed], ax
                mov ax, [%1Struc + entity.y_speed_buffer]
                mov word [%1Struc + entity.y_speed], ax
                normalMovement_%1:
                mov ax, [%1Struc + entity.x_speed]
                add word [%1Struc + entity.x_pos], ax
                mov ax, [%1Struc + entity.y_speed]
                add word [%1Struc + entity.y_pos], ax
                jmp endMovement_%1
            skipMovement_%1:
                mov byte [col_test_nb], 1
                cmp byte [buffered_col_test], TRUE
                je continueDirection_%1
                mov byte [%1Struc + entity.animation_frame], 4
                jmp endMovement_%1
            tunnelTeleport_%1:
                inc byte [%1Struc + entity.animation_frame]
                cmp word [%1Struc + entity.x_speed], -2
                je tpToRight_%1
                sub word [%1Struc + entity.x_pos], WALL_WIDTH * 25
                ; cmp %1, pacman
                ; jne skipFixTp_%1
                cmp word [%1Struc + entity.x_pos], 0
                jg skipFixTp_%1
                add word [%1Struc + entity.x_pos], 320
                jmp endMovement_%1
                tpToRight_%1:
                add word [%1Struc + entity.x_pos], WALL_WIDTH * 25
                mov ax, %1
                cmp ax, pacman
                jne skipFixTp_%1
                cmp word [%1Struc + entity.x_pos], 320
                jl skipFixTp_%1
                sub word [%1Struc + entity.x_pos], 320
                jmp endMovement_%1
                skipFixTp_%1:
        endMovement_%1:
        %rotate 1
    %endrep
%endmacro