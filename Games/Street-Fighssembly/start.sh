ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"

NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Street-Fighssembly"
GAME_BIN="$GAME_DIR/bin"
DOSBOX_BIN="/Users/$USER/Desktop/dosbox.app/Contents/MacOS/DOSBox"
DOSBOX_CONF="/Users/$USER/Library/Preferences/DOSBox 0.74-3-3 Preferences"
CONF="$ROOT_DIR/DOSBox-Conf"

"$NASM" "$GAME_DIR/Main.asm" -f bin -o "$GAME_BIN/SF.com"

"$DOSBOX_BIN" -c "config -set sdl fullscreen=true" -c "config -set sdl fullresolution=desktop" -c "config -writeconf $CONF/DOSBox" -c "exit"

cp "$CONF/DOSBox" "$DOSBOX_CONF"

"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "SF.com" -c "config -set sdl fullscreen=false" -c "config -set sdl fullresolution=original" -c "config -writeconf $CONF/DOSBox" -c exit

cp "$CONF/DOSBox" "$DOSBOX_CONF"