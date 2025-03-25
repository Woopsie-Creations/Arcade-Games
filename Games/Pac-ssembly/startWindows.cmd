@echo off
set "ROOT_DIR=%~dp0"
set "NASM=%ROOT_DIR%\Nasm\nasm"
set "BIN_DIR=%ROOT_DIR%\Bin"
set "DOSBOX_BIN=%ProgramFiles(x86)%\DOSBox-0.74-3\DOSBox.exe"

"%NASM%" "%ROOT_DIR%\main.asm" -f bin -o "%BIN_DIR%\PS.com"

"%DOSBOX_BIN%" -c keyb fr189 , -c "MOUNT c %BIN_DIR%" , -c c: , -c PS.com

exit