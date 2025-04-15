clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="nasm"
GAME_DIR="$ROOT_DIR/Street-Fighssembly"
GAME_BIN="$GAME_DIR/bin"
DOSBOX_BIN="/usr/bin/dosbox"
DOSBOX_CONF="$HOME/.dosbox/dosbox-0.74.conf"

# Assemble the sprites
"$NASM" "$GAME_DIR/sprite.asm" -f bin -o "$GAME_BIN/sprite.bin"

# Assemble the game
"$NASM" "$GAME_DIR/main.asm" -f bin -o "$GAME_BIN/SF.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "SF.com" -c "exit"