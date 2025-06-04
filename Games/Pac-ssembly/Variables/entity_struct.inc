section .data
    ENTITY_SPRITE_WIDTH equ 12
    ENTITY_SPRITE_HEIGHT equ 12

    struc entity
        .initial_x_pos: resw 1
        .initial_y_pos: resw 1
        .x_pos: resw 1
        .y_pos: resw 1
        .x_speed: resw 1
        .y_speed: resw 1
        .x_speed_buffer: resw 1
        .y_speed_buffer: resw 1
        .movement_buffered: resb 1
        .animation_frame: resb 1
        .sprite_nb: resb 1
        .is_dead: resb 1
        .top_bound: resw 1
        .right_bound: resw 1
        .bottom_bound: resw 1
        .left_bound: resw 1
    endstruc

    buffered_col_test db FALSE
    col_test_nb db 1

%include "Variables/pacman_variables.inc"
%include "Variables/ghost_variables.inc"