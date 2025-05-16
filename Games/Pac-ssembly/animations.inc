%macro animationSide 8
    %2:
        cmp byte [%1Struc + entity.animation_frame], %4
        je %%Frame1
        cmp byte [%1Struc + entity.animation_frame], %5
        je %%Frame2
        cmp byte [%1Struc + entity.animation_frame], %6
        je %%Frame3
        cmp byte [%1Struc + entity.animation_frame], %7
        je %%Frame4
        jmp %%end_anim
        %%Frame1:
            mov byte [%1Struc + entity.sprite_nb], %3 + 1
            jmp %%end_anim
        %%Frame2:
            mov byte [%1Struc + entity.sprite_nb], %3
            jmp %%end_anim
        %%Frame3:
            mov byte [%1Struc + entity.sprite_nb], %8
            jmp %%end_anim
        %%Frame4:
            mov byte [%1Struc + entity.sprite_nb], %3
            mov byte [%1Struc + entity.animation_frame], 0
            jmp %%end_anim
        %%end_anim:
%endmacro

%macro pacman_animations 0-* pacman
    cmp word [%1Struc + entity.y_speed], -2
    je %1_animationUp
    cmp word [%1Struc + entity.x_speed], 2
    je %1_animationRight
    cmp word [%1Struc + entity.y_speed], 2
    je %1_animationDown
    cmp word [%1Struc + entity.x_speed], -2
    je %1_animationLeft
    jmp %%end
        animationSide %1, %1_animationUp, 1, 1, 2, 3, 4, 0
        jmp %%end
        animationSide %1, %1_animationRight, 3, 1, 2, 3, 4, 0
        jmp %%end
        animationSide %1, %1_animationDown, 5, 1, 2, 3, 4, 0
        jmp %%end
        animationSide %1, %1_animationLeft, 7, 1, 2, 3, 4, 0
    %%end:
%endmacro

%macro ghosts_animations 0-* blinky, pinky, inky, clyde
    %rep 4
        cmp word [%1Struc + entity.y_speed], -2
        je %1_animationUp
        cmp word [%1Struc + entity.x_speed], 2
        je %1_animationRight
        cmp word [%1Struc + entity.y_speed], 2
        je %1_animationDown
        cmp word [%1Struc + entity.x_speed], -2
        je %1_animationLeft
        jmp %%end_%1
            animationSide %1, %1_animationUp, 0, 1, 3, 5, 7, 0
            jmp %%end_%1
            animationSide %1, %1_animationRight, 2, 1, 3, 5, 7, 2
            jmp %%end_%1
            animationSide %1, %1_animationDown, 4, 1, 3, 5, 7, 4
            jmp %%end_%1
            animationSide %1, %1_animationLeft, 6, 1, 3, 5, 7, 6
        %%end_%1:
        %rotate 1
    %endrep
%endmacro