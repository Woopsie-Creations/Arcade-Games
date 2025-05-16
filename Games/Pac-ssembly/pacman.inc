section .text    
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
