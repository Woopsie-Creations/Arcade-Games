%macro hitAnimation 1-*
    %rep 3
        call clearViewport
        mov bx, %1
        displayCurrentPokes
        call displayUI
        call displayViewport
        mov dx, 50000
        mov ah, 0x86
        int 0x15
        mov dx, 25000
        mov ah, 0x86
        int 0x15

        ; re-display normally
        call displayFrame
        mov dx, 50000
        mov ah, 0x86
        int 0x15
    %endrep
%endmacro