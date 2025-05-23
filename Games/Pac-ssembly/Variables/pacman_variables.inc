section .data
    pacmanStruc:
        istruc entity
            at entity.initial_x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 5
            at entity.initial_y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 23 - 3
            at entity.x_pos, dw MAZE_X_POS + WALL_WIDTH * (COLUMN_NUMBER / 2) - 5
            at entity.y_pos, dw MAZE_Y_POS + WALL_HEIGHT * 23 - 3
            at entity.x_speed, dw 2
            at entity.y_speed, dw 0
            at entity.x_speed_buffer, dw 0
            at entity.y_speed_buffer, dw 0
            at entity.movement_buffered, db FALSE
            at entity.animation_frame, db 1
            at entity.sprite_nb, db 3
            at entity.is_dead, db FALSE
            at entity.top_bound, dw 0
            at entity.right_bound, dw 0
            at entity.bottom_bound, dw 0
            at entity.left_bound, dw 0
        iend

    pacman_lives db 3
    ghosts_eaten_in_a_row db 0
    got_a_bonus_life db 0