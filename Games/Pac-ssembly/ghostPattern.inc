section .text
    ghostPattern:
        mov word [blinkyStruc + entity.x_speed], -2
        ret