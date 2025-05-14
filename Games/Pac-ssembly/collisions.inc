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

%macro pacmanCol 0
    cmp byte [col_test_nb], 1
    jne %%secondColTest
    mov byte [col_test_nb], 2
    colVerifier secondCollisionTest
    %%secondColTest:
    mov byte [col_test_nb], 1
    colVerifier pacmanMovement.doMovement
%endmacro

%macro ghostCol 0 
    cmp byte [col_test_nb], 1
    jne %%secondColTest
    mov byte [col_test_nb], 2
    ghost_colVerifier ghostMovement
    %%secondColTest:
    mov byte [col_test_nb], 1
    ghost_colVerifier ghostMovement.doMovement
    jmp .endLoop
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
    %5
%endmacro