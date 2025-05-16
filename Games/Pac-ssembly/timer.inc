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
    mov byte %4, FALSE
    call %3
    %%earlyExit:
%endmacro

%macro initGhostTimers 0
    mov bx, 0
    %rep 4
        init_timer 5, time_start_ghost, interval_ticks_ghost, expected_time_ghost, [has_init_timer_ghost+bx]
        inc bx
    %endrep
%endmacro

section .data
    has_init_timer_fruit db FALSE
    time_start_fruit dw 0
                     dw 0
    interval_ticks_fruit dw 0
                         dw 0
    expected_time_fruit dw 0
                        dw 0
    current_time_fruit dw 0
                       dw 0

    has_init_timer_ghost db FALSE
                         db FALSE
                         db FALSE
                         db FALSE
    time_start_ghost dw 0
                     dw 0
    interval_ticks_ghost dw 0
                         dw 0
    expected_time_ghost dw 0
                        dw 0
    current_time_ghost dw 0
                       dw 0
