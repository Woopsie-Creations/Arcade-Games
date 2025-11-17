%macro wait 1
    mov dx, %1
    mov ah, 0x86
    int 0x15
%endmacro

%macro hitAnimation 1-*
    %rep 3
        call clearViewport
        mov bx, %1
        displayCurrentPokes
        call displayUI
        call displayViewport
        wait 50000
        wait 25000 ; yes we wait even more, why not?

        ; re-display normally
        call displayFrame
        wait 50000
    %endrep
%endmacro