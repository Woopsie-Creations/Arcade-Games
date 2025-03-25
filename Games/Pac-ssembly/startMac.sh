clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Pac-ssembly"
GAME_BIN="$GAME_DIR/Bin"
DOSBOX_BIN="/Users/$USER/Documents/dosbox.app/Contents/MacOS/DOSBox"

# Assemble the game
"$NASM" "$GAME_DIR/main.asm" -f bin -o "$GAME_BIN/PS.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "PS.com" -c "exit"


