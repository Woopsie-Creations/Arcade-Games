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
        mov cx, [delay_waitloop]
        call waitLoop
        call waitLoop
        call waitLoop
        xor cx, cx
        
        ; is key pressed ?
        mov ah, 01h 
        int 16h
        jz gameLoop ; if no, skip

        ; which key is pressed
        mov ah, 00h
        int 16h
        ; first player
        cmp ah, LEFT_ARROW
        je left1
        cmp ah, RIGHT_ARROW
        je right1
        cmp ah, UP_ARROW 
        je up1
        cmp ah, DOWN_ARROW
        je down1

        ; second player
        cmp ah, A_KEY
        je left2
        cmp ah, D_KEY
        je right2
        cmp ah, W_KEY 
        je up2
        cmp ah, S_KEY
        je down2

        cmp ah, ESCAPE_KEY
        je exitProgram
        jmp gameLoop

    ; ------------------------
    up1:
        mov ax, [y_pos_1]
        add ax, SPRITE_HEIGHT
        cmp ax, WINDOW_DOWN_BORDER
        jl gameLoop ; skip if in the air
        mov byte [jumping_1], 1
        mov word [y_velocity_1], 14
        jmp gameLoop
    
    left1:
        cmp word [x_pos_1], WINDOW_LEFT_BORDER
        jle gameLoop ; skip if collision
        clearOldPosition [x_pos_1], [y_pos_1]
        sub word [x_pos_1], 10
        setPixelPosition [x_pos_1], [y_pos_1]
        jmp gameLoop
    
    right1:
        mov ax, [x_pos_1]
        add ax, SPRITE_WIDTH
        cmp ax, WINDOW_RIGHT_BORDER
        jge gameLoop ; skip if collision
        clearOldPosition [x_pos_1], [y_pos_1]
        add word [x_pos_1], 10
        setPixelPosition [x_pos_1], [y_pos_1]
        jmp gameLoop
    
    down1:
        cmp word [y_pos_1], WINDOW_DOWN_BORDER
        je gameLoop ; skip if collision
        clearOldPosition [x_pos_1], [y_pos_1]
        add word [y_pos_1], 10
        setPixelPosition [x_pos_1], [y_pos_1]
        jmp gameLoop

    up2:
        mov ax, [y_pos_2]
        add ax, SPRITE_HEIGHT
        cmp ax, WINDOW_DOWN_BORDER
        jl gameLoop ; skip if in the air
        mov byte [jumping_2], 1
        mov word [y_velocity_2], 14
        jmp gameLoop
    
    left2:
        cmp word [x_pos_2], WINDOW_LEFT_BORDER
        jle gameLoop ; skip if collision
        clearOldPosition [x_pos_2], [y_pos_2]
        sub word [x_pos_2], 10
        setPixelPosition [x_pos_2], [y_pos_2]
        jmp gameLoop
    
    right2:
        mov ax, [x_pos_2]
        add ax, SPRITE_WIDTH
        cmp ax, WINDOW_RIGHT_BORDER
        jge gameLoop ; skip if collision
        clearOldPosition [x_pos_2], [y_pos_2]
        add word [x_pos_2], 10
        setPixelPosition [x_pos_2], [y_pos_2]
        jmp gameLoop
    
    down2:
        cmp word [y_pos_2], WINDOW_DOWN_BORDER
        jge gameLoop ; skip if collision
        clearOldPosition [x_pos_2], [y_pos_2]
        add word [y_pos_2], 10
        setPixelPosition [x_pos_2], [y_pos_2]
        jmp gameLoop


    ; ------------------------