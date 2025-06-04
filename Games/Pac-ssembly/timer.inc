%macro init_timer 5
    ; === Get initial tick count ===
    mov ax, 0x0040
    mov es, ax
    mov si, 0x006C
    cli
    mov ax, word [es:si]
    mov dx, word [es:si+2]
    sti

    ; Save start time
    mov [%2], ax
    mov [%2+2], dx

    ; Convert seconds (%1) to ticks (18 ticks/sec)
    mov bx, %1
    mov ax, 18
    mul bx                 ; DX:AX = ticks
    mov [%3], ax
    mov [%3+2], dx

    ; expected_time = start_time + interval_ticks
    mov ax, [%2]
    add ax, [%3]
    mov [%4], ax

    mov dx, [%2+2]
    adc dx, [%3+2]
    mov [%4+2], dx

    mov byte %5, TRUE
%endmacro

%macro getCurrentTime 0
    mov ax, 0x0040
    mov es, ax
    mov si, 0x006C
    cli
    mov ax, word [es:si]
    mov dx, word [es:si+2]
    sti
%endmacro

%macro checkTimer 4
    getCurrentTime
    mov [%1], ax ; current_time
    mov [%1+2], dx

    ; Then we compare times
    mov ax, [%1+2]
    cmp ax, [%2+2] ; expected_time
    ja %3
    jb %%earlyExit

    mov ax, [%1]
    cmp ax, [%2]
    jb %%earlyExit
    
    ; it's time to...
    call %3
    mov byte %4, FALSE
    %%earlyExit:
%endmacro

%macro checkGhostTimers 0-* blinky, pinky, inky, clyde
    %rep %0
        checkTimer current_time_%1, expected_time_%1, moveGhostsOutOfCage, [has_init_timer_%1]
        %rotate 1
    %endrep
%endmacro

%macro initGhostTimers 0-* blinky, pinky, inky, clyde
    mov bx, 0
    %rep 4
        push bx
        init_timer bx, time_start_%1, interval_ticks_%1, expected_time_%1, [has_init_timer_%1]
        pop bx
        add bx, 2
        %rotate 1
    %endrep
%endmacro

%macro createGhostsTimers 0-* blinky, pinky, inky, clyde
    [section .bss]
    %rep %0
        has_init_timer_%1 resb 1
        time_start_%1 resw 2
        interval_ticks_%1 resw 2
        expected_time_%1 resw 2
        current_time_%1 resw 2
        %rotate 1
    %endrep
    [section .text]
%endmacro

section .bss
    has_init_timer_fruit resb 1
    time_start_fruit resw 2
    interval_ticks_fruit resw 2
    expected_time_fruit resw 2
    current_time_fruit resw 2

    has_init_timer_fright resb 1
    time_start_fright resw 2
    interval_ticks_fright resw 2
    expected_time_fright resw 2
    current_time_fright resw 2

    has_init_timer_score resb 1
    time_start_score resw 2
    interval_ticks_score resw 2
    expected_time_score resw 2
    current_time_score resw 2
