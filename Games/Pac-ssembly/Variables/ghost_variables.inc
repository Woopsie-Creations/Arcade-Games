section .data
    ghost_sprite dw blinky
                 dw pinky
                 dw inky
                 dw clyde

    blinky_in_fright_mode db FALSE
    pinky_in_fright_mode db FALSE
    inky_in_fright_mode db FALSE
    clyde_in_fright_mode db FALSE

    blinky_stuck db FALSE
    pinky_stuck db FALSE
    inky_stuck db FALSE
    clyde_stuck db FALSE

    blinkyStruc:
        istruc entity
            at entity.initial_x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - WALL_WIDTH - 1
            at entity.initial_y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 11 - 3
            at entity.x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 7
            at entity.y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 11 - 3
            at entity.x_speed, dw 0
            at entity.y_speed, dw 0
            at entity.x_speed_buffer, dw 0
            at entity.y_speed_buffer, dw 0
            at entity.movement_buffered, db FALSE
            at entity.animation_frame, db 1
            at entity.sprite_nb, db 7
            at entity.is_dead, db FALSE
        iend
    pinkyStruc:
        istruc entity
            at entity.initial_x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - WALL_WIDTH
            at entity.initial_y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 14 - 3
            at entity.x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - WALL_WIDTH
            at entity.y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 14 - 3
            at entity.x_speed, dw 0
            at entity.y_speed, dw 0
            at entity.x_speed_buffer, dw 0
            at entity.y_speed_buffer, dw 0
            at entity.movement_buffered, db FALSE
            at entity.animation_frame, db 1
            at entity.sprite_nb, db 5
            at entity.is_dead, db FALSE
        iend
    inkyStruc:
        istruc entity
            at entity.initial_x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - (ENTITY_SPRITE_WIDTH + WALL_WIDTH)
            at entity.initial_y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 14 - 3
            at entity.x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - (ENTITY_SPRITE_WIDTH + WALL_WIDTH)
            at entity.y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 14 - 3
            at entity.x_speed, dw 0
            at entity.y_speed, dw 0
            at entity.x_speed_buffer, dw 0
            at entity.y_speed_buffer, dw 0
            at entity.movement_buffered, db FALSE
            at entity.animation_frame, db 1
            at entity.sprite_nb, db 0
            at entity.is_dead, db FALSE
        iend
    clydeStruc:
        istruc entity
            at entity.initial_x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) + WALL_WIDTH
            at entity.initial_y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 14 - 3
            at entity.x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) + WALL_WIDTH
            at entity.y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 14 - 3
            at entity.x_speed, dw 0
            at entity.y_speed, dw 0
            at entity.x_speed_buffer, dw 0
            at entity.y_speed_buffer, dw 0
            at entity.movement_buffered, db FALSE
            at entity.animation_frame, db 1
            at entity.sprite_nb, db 0
            at entity.is_dead, db FALSE
        iend
