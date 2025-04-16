section .data
    VIEWPORT_WIDTH equ 300
    VIEWPORT_HEIGHT equ 180

    VIEWPORT_X_OFFSET equ 10
    VIEWPORT_Y_OFFSET equ 10

section .bss 
    viewport: resb VIEWPORT_WIDTH * VIEWPORT_HEIGHT

section .text
    setViewport:
        mov bx, VIEWPORT_WIDTH * VIEWPORT_HEIGHT
        mov cx, bx
        clearViewport:
            mov byte [viewport+bx], 0x00
            dec bx
            loop clearViewport

        ; place second player
        ; -------------------
        ; find the player position from the screen position to the viewport position
        mov ax, [y_pos_2]
        sub ax, 10
        mov bx, 300
        mul bx
        add ax, [x_pos_2] 
        sub ax, 10
        mov bx, ax ; bx is used later to position the correct pixel in its right location
        mov dx, 0
        .eachSpriteRow:
            mov cx, 0
            .eachSpriteLine:
                push bx  ; save viewport position of the player into the stack for later
                mov bx, 0
                add bx, dx
                mov al, [buffer1+bx]
                pop bx  ; retrieve the viewport position of the player to place the correct color in its correct location
                cmp al, 0x00
                je .skipPlaceColor
                mov byte [viewport+bx], al
                .skipPlaceColor:
                inc bx  ; increment to the next pixel of the viewport
                inc dx  ; increment the number of pixel of the sprite to choose the correct color from the sprite
                inc cx  ; increment the width position
                cmp cx, SPRITE_WIDTH
                jne .eachSpriteLine ; if it gets to the end of the line, go to the next line
            add bx, 300 - SPRITE_WIDTH 
            cmp dx, SPRITE_SIZE
            jne .eachSpriteRow ; continue until we have done each pixels

        ; place first player, it is placed after to make put it in front of the second player
        ; -------------------
        ; find the player position from the screen position to the viewport position
        mov ax, [y_pos_1]
        sub ax, 10
        mov bx, 300
        mul bx
        add ax, [x_pos_1] 
        sub ax, 10
        mov bx, ax ; bx is used later to position the correct pixel in its right location
        mov dx, 0
        .eachSpriteRow1:
            mov cx, 0
            .eachSpriteLine1:
                push bx  ; save viewport position of the player into the stack for later
                mov bx, 0
                add bx, dx
                mov al, [buffer1+bx]
                pop bx  ; retrieve the viewport position of the player to place the correct color in its correct location
                cmp al, 0x00
                je .skipPlaceColor1
                mov byte [viewport+bx], al
                .skipPlaceColor1:
                inc bx  ; increment to the next pixel of the viewport
                inc dx  ; increment the number of pixel of the sprite to choose the correct color from the sprite
                inc cx  ; increment the width position
                cmp cx, SPRITE_WIDTH
                jne .eachSpriteLine1 ; if it gets to the end of the line, go to the next line
            add bx, 300 - SPRITE_WIDTH 
            cmp dx, SPRITE_SIZE
            jne .eachSpriteRow1 ; continue until we have done each pixels
        ret


    displayViewport:
        ; first set the viewport position in the screen
        mov ax, VIEWPORT_Y_OFFSET
        mov bx, 320
        mul bx
        add ax, VIEWPORT_X_OFFSET
        mov di, ax
        ; then display the viewport
        mov si, viewport
        mov dx, VIEWPORT_HEIGHT
        .eachRow:
            mov cx, VIEWPORT_WIDTH
            .eachLine:
                rep movsb
            add di, 320 - VIEWPORT_WIDTH 
            dec dx
            jnz .eachRow
        ret