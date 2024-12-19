ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"

NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Street-Fighssembly"
GAME_BIN="$GAME_DIR/bin"
DOSBOX_BIN="/Users/$USER/Desktop/dosbox.app/Contents/MacOS/DOSBox"

"$NASM" "$GAME_DIR/main.asm" -f bin -o "$GAME_BIN/SF.com"

"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "SF.com"