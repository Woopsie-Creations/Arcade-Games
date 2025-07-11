section .data
FONT_WIDTH equ 5
FONT_HEIGHT equ 5
; Font letter A
A           db 0x00,0x0F,0x0F,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter B
B           db 0x0F,0x0F,0x0F,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x00

; Font letter C
C           db 0x00,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x00,0x0F,0x0F,0x0F,0x0F

; Font letter D
D           db 0x0F,0x0F,0x0F,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x00

; Font letter E
E           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter F
F           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00

; Font letter G
G           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter H
H           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter I
I           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter J
J           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x0F,0x00,0x0F,0x00,0x00
            db 0x0F,0x0F,0x0F,0x00,0x00

; Font letter K
K           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x0F,0x00
            db 0x0F,0x0F,0x0F,0x00,0x00
            db 0x0F,0x00,0x00,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter L
L           db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter M
M           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x00,0x0F,0x0F
            db 0x0F,0x00,0x0F,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter N
N           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x00,0x00,0x0F
            db 0x0F,0x00,0x0F,0x00,0x0F
            db 0x0F,0x00,0x00,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter O
O           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter P
P           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x00,0x00,0x00,0x00

; Font letter Q
Q           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x0F,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter R
R           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter S
S           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x00,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter T
T           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00

; Font letter U
U           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font letter V
V           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x00,0x0F,0x00,0x0F,0x00
            db 0x00,0x0F,0x00,0x0F,0x00
            db 0x00,0x00,0x0F,0x00,0x00

; Font letter W
W           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F
            db 0x0F,0x00,0x0F,0x00,0x0F
            db 0x0F,0x0F,0x00,0x0F,0x0F
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter X
X           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x00,0x0F,0x00,0x0F,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x0F,0x00,0x0F,0x00
            db 0x0F,0x00,0x00,0x00,0x0F

; Font letter Y
Y           db 0x0F,0x00,0x00,0x00,0x0F
            db 0x00,0x0F,0x00,0x0F,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x00,0x0F,0x00,0x00

; Font letter Z
Z           db 0x0F,0x0F,0x0F,0x0F,0x0F
            db 0x00,0x00,0x00,0x0F,0x00
            db 0x00,0x00,0x0F,0x00,0x00
            db 0x00,0x0F,0x00,0x00,0x00
            db 0x0F,0x0F,0x0F,0x0F,0x0F

space       db 0x00,0x00,0x00,0x00,0x00
            db 0x00,0x00,0x00,0x00,0x00
            db 0x00,0x00,0x00,0x00,0x00
            db 0x00,0x00,0x00,0x00,0x00
            db 0x00,0x00,0x00,0x00,0x00

; Font number 0
font0           db 0x00,0x0F,0x0F,0x0F,0x00
                db 0x0F,0x00,0x00,0x0F,0x0F
                db 0x0F,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x00,0x00,0x0F
                db 0x00,0x0F,0x0F,0x0F,0x00

; Font number 1
font1           db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x0F,0x0F,0x00,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font number 2
font2           db 0x00,0x0F,0x0F,0x00,0x00
                db 0x0F,0x00,0x00,0x0F,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x0F,0x00,0x00,0x00
                db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font number 3
font3           db 0x0F,0x0F,0x0F,0x0F,0x00
                db 0x00,0x00,0x00,0x00,0x0F
                db 0x00,0x0F,0x0F,0x0F,0x0F
                db 0x00,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x0F,0x0F,0x00

; Font number 4
font4           db 0x0F,0x00,0x00,0x00,0x0F
                db 0x0F,0x00,0x00,0x00,0x0F
                db 0x00,0x0F,0x0F,0x0F,0x0F
                db 0x00,0x00,0x00,0x00,0x0F
                db 0x00,0x00,0x00,0x00,0x0F

; Font number 5
font5           db 0x00,0x0F,0x0F,0x0F,0x0F
                db 0x0F,0x00,0x00,0x00,0x00
                db 0x0F,0x0F,0x0F,0x0F,0x0F
                db 0x00,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font number 6
font6           db 0x00,0x0F,0x0F,0x0F,0x0F
                db 0x0F,0x00,0x00,0x00,0x00
                db 0x0F,0x0F,0x0F,0x0F,0x0F
                db 0x0F,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x0F,0x0F,0x00

; Font number 7
font7           db 0x0F,0x0F,0x0F,0x0F,0x0F
                db 0x00,0x00,0x00,0x00,0x0F
                db 0x00,0x00,0x00,0x0F,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x0F,0x00,0x00,0x00

; Font number 8
font8           db 0x0F,0x0F,0x0F,0x0F,0x0F
                db 0x0F,0x00,0x00,0x00,0x0F
                db 0x00,0x0F,0x0F,0x0F,0x00
                db 0x0F,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font number 9
font9           db 0x00,0x0F,0x0F,0x0F,0x0F
                db 0x0F,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x0F,0x0F,0x0F
                db 0x00,0x00,0x00,0x00,0x0F
                db 0x0F,0x0F,0x0F,0x0F,0x00

; Font symbol dash (-)
fontDash        db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x0F,0x0F,0x0F,0x0F,0x0F
                db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00

; Font symbol underscore (_)
fontUnderS      db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x0F,0x0F,0x0F,0x0F,0x0F

; Font symbol slash (/)
fontSlash       db 0x00,0x00,0x00,0x00,0x0F
                db 0x00,0x00,0x00,0x0F,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x0F,0x00,0x00,0x00
                db 0x0F,0x00,0x00,0x00,0x00

; Font symbol double dot (:)
fontDblDot      db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00

; Font symbol dot (.)
fontDot         db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00
                db 0x00,0x00,0x0F,0x00,0x00
                db 0x00,0x00,0x00,0x00,0x00