%macro pacmanAnimationSide 2
    %1:
        cmp byte [pacmanStruc + entity.animation_frame], 1
        je %%pacmanFrame1
        cmp byte [pacmanStruc + entity.animation_frame], 2
        je %%pacmanFrame2
        cmp byte [pacmanStruc + entity.animation_frame], 3
        je %%pacmanFrame3
        cmp byte [pacmanStruc + entity.animation_frame], 4
        je %%pacmanFrame4
        ret
        %%pacmanFrame1:
            mov byte [pacmanStruc + entity.sprite_nb], %2 + 1
            ret
        %%pacmanFrame2:
            mov byte [pacmanStruc + entity.sprite_nb], %2
            ret
        %%pacmanFrame3:
            mov byte [pacmanStruc + entity.sprite_nb], 0
            ret
        %%pacmanFrame4:
            mov byte [pacmanStruc + entity.sprite_nb], %2
            mov byte [pacmanStruc + entity.animation_frame], 0
            ret
%endmacro

section .text
    pacmanAnimation:
        cmp word [pacmanStruc + entity.y_speed], -2
        je animationUp
        cmp word [pacmanStruc + entity.x_speed], 2
        je animationRight
        cmp word [pacmanStruc + entity.y_speed], 2
        je animationDown
        cmp word [pacmanStruc + entity.x_speed], -2
        je animationLeft
            pacmanAnimationSide animationUp, 1
            pacmanAnimationSide animationRight, 3
            pacmanAnimationSide animationDown, 5
            pacmanAnimationSide animationLeft, 7
    
    pacmanEating:
        cmp al, 38 ; fruit
        je .eraseFruit
        cmp al, 35 ; super gum
        je .eraseSuperGum
        cmp al, 36 ; gum
        je .eraseGum
        jmp .exit
        .eraseFruit:
            cmp byte [fruit_should_be_displayed], FALSE
            je .exit
            call eraseFruit
            ; -- WHICH FRUIT --
            mov bx, [current_fruit_case_index]
            shl bx, 1
            addToScore [fruit_score_table+bx]
            jmp .exit
        .eraseSuperGum:
            dec byte [maze_remaining_gums]
            mov byte [maze+bx], 37
            addToScore 50
            jmp .exit
        .eraseGum:
            dec byte [maze_remaining_gums]
            mov byte [maze+bx], 37
            addToScore 10
        .exit:
            ret
