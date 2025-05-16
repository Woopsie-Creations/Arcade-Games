%macro init_timer 1
    ; === Get initial tick count ===
    mov ax, 0x0040
    mov es, ax
    mov si, 0x006C
    cli
    mov ax, word [es:si]
    mov dx, word [es:si+2]
    sti

    ; Save start time
    mov [time_start], ax
    mov [time_start+2], dx

    ; Convert seconds (%1) to ticks (18 ticks/sec)
    mov bx, %1
    mov ax, 18
    mul bx                 ; DX:AX = ticks
    mov [interval_ticks], ax
    mov [interval_ticks+2], dx

    ; expected_time = start_time + interval_ticks
    mov ax, [time_start]
    add ax, [interval_ticks]
    mov [expected_time], ax

    mov dx, [time_start+2]
    adc dx, [interval_ticks+2]
    mov [expected_time+2], dx
%endmacro

section .data
    time_start dw 0
               dw 0
    interval_ticks dw 0
                   dw 0
    expected_time dw 0
                  dw 0
    current_time dw 0
                 dw 0

section .text
    initTimer:
        init_timer 2
        ret

    getCurrentTime:
        mov ax, 0x0040
        mov es, ax
        mov si, 0x006C
        cli
        mov ax, word [es:si]
        mov dx, word [es:si+2]
        sti
        ret

;    checkTimer:
;        call getCurrentTime
;
;        mov [current_time], ax
;        mov [current_time+2], dx
;
;        ; Then we compare times
;        mov ax, [current_time+2]
;        cmp ax, [expected_time+2]
;        ja moveGhostsOutOfCage
;        jb .earlyExit
;
;        mov ax, [current_time]
;        cmp ax, [expected_time]
;        jb .earlyExit
;        
;        call moveGhostsOutOfCage
;        .earlyExit:
;        ret