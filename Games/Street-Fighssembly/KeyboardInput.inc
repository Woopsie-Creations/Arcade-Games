; --------------------------------------------------
; Keyboard input handling. 
; Each key used are listed in section .data.
; --------------------------------------------------

section .data
    %define LEFT_ARROW 4Bh
    %define RIGHT_ARROW 4Dh
    %define UP_ARROW 48h
    %define DOWN_ARROW 50h

    %define W_KEY 11h
    %define A_KEY 1Eh
    %define S_KEY 1Fh
    %define D_KEY 20h

    %define ESCAPE_KEY 01h

section .text
    readKeyboard:
        xor cx, cx
        
        ; is key pressed ?
        mov ah, 01h 
        int 16h
        jz animatePlayers ; if no, skip

        ; which key is pressed
        mov ah, 00h
        int 16h

        cmp ah, ESCAPE_KEY
        je exitProgram

        ; first player
        cmp ah, A_KEY
        je left1
        cmp ah, D_KEY
        je right1
        cmp ah, W_KEY 
        je up1
        cmp ah, S_KEY
        je down1

        ; second player
        cmp ah, LEFT_ARROW
        je left2
        cmp ah, RIGHT_ARROW
        je right2
        cmp ah, UP_ARROW 
        je up2
        cmp ah, DOWN_ARROW
        je down2

        jmp animatePlayers

    ; ------------------------
    up1:
        mov ax, [y_pos_1]
        add ax, SPRITE_HEIGHT
        cmp ax, WINDOW_DOWN_BORDER
        jl animatePlayers ; skip if in the air
        mov byte [jumping_1], 1
        mov word [y_velocity_1], 14
        call animatePlayer1
        jmp gameLoop
    
    left1:
        cmp word [x_pos_1], WINDOW_LEFT_BORDER
        jle animatePlayers ; skip if collision
        sub word [x_pos_1], 10
        call animatePlayer1
        jmp gameLoop
    
    right1:
        mov ax, [x_pos_1]
        add ax, SPRITE_WIDTH
        cmp ax, WINDOW_RIGHT_BORDER
        jge animatePlayers ; skip if collision
        add word [x_pos_1], 10
        call animatePlayer1
        jmp gameLoop
    
    down1:
        cmp word [y_pos_1], WINDOW_DOWN_BORDER
        je animatePlayers ; skip if collision
        add word [y_pos_1], 10
        call animatePlayer1
        jmp gameLoop

    up2:
        mov ax, [y_pos_2]
        add ax, SPRITE_HEIGHT
        cmp ax, WINDOW_DOWN_BORDER
        jl animatePlayers ; skip if in the air
        mov byte [jumping_2], 1
        mov word [y_velocity_2], 14
        call animatePlayer2
        jmp gameLoop
    
    left2:
        cmp word [x_pos_2], WINDOW_LEFT_BORDER
        jle animatePlayers ; skip if collision
        sub word [x_pos_2], 10
        call animatePlayer2
        jmp gameLoop
    
    right2:
        mov ax, [x_pos_2]
        add ax, SPRITE_WIDTH
        cmp ax, WINDOW_RIGHT_BORDER
        jge animatePlayers ; skip if collision
        add word [x_pos_2], 10
        call animatePlayer2
        jmp gameLoop
    
    down2:
        cmp word [y_pos_2], WINDOW_DOWN_BORDER
        jge animatePlayers ; skip if collision
        add word [y_pos_2], 10
        call animatePlayer2
        jmp gameLoop


    ; ------------------------