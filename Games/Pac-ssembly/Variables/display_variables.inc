section .bss
    viewport_memory_block_pos resw 1
    save_color resb 1

section .data
    SCREEN_WIDTH equ 320
    SCREEN_HEIGHT equ 200

    is_displaying_black db FALSE