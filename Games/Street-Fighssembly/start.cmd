@echo off
setlocal

for /f "delims=" %%i in ("%~dp0.") do set ROOT_DIR=%%~fi
for /f "delims=" %%i in ("%ROOT_DIR%") do set ROOT_DIR=%%~dpi

set NASM=C:\Users\Enzo\AppData\Local\bin\NASM\nasm.exe
set GAME_DIR=%ROOT_DIR%Street-Fighssembly
set GAME_BIN=%GAME_DIR%\bin
set DOSBOX_BIN=C:\Program Files (x86)\DOSBox-0.74-3\DOSBox.exe
set DOSBOX_CONF=C:\Users\%USERNAME%\AppData\Local\DOSBox\dosbox-0.74-3.conf
set CONF=%ROOT_DIR%DOSBox-Conf

"%NASM%" "%GAME_DIR%\Main.asm" -f bin -o "%GAME_BIN%\SF.com"

"%DOSBOX_BIN%" -c "config -set sdl fullscreen=true" -c "config -set sdl fullresolution=desktop" -c "config -writeconf %CONF%\DOSBox" -c "exit"

copy "%CONF%\DOSBox" "%DOSBOX_CONF%" /Y

"%DOSBOX_BIN%" -c "MOUNT c %GAME_BIN%" -c "c:" -c "SF.com" -c "config -set sdl fullscreen=false" -c "config -set sdl fullresolution=original" -c "config -writeconf %CONF%\DOSBox" -c "exit"

copy "%CONF%\DOSBox" "%DOSBOX_CONF%" /Y

endlocal
