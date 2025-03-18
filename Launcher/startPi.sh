clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="nasm"  # Assumes NASM is installed globally
GAME_DIR="$ROOT_DIR/Launcher"
GAME_BIN="$GAME_DIR/Bin"
DOSBOX_BIN="/usr/bin/dosbox"
DOSBOX_CONF="$HOME/.dosbox/dosbox-0.74.conf"

# Assemble the game
"$NASM" "$GAME_DIR/launcher.asm" -f bin -o "$GAME_BIN/launcher.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "SF.com" -c "exit"