clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Launcher"
GAME_BIN="$GAME_DIR/Bin"
DOSBOX_BIN="/Users/$USER/Desktop/dosbox.app/Contents/MacOS/DOSBox"
DOSBOX_CONF="/Users/$USER/Library/Preferences/DOSBox 0.74-3-3 Preferences"

# Assemble the game
"$NASM" "$GAME_DIR/launcher.asm" -f bin -o "$GAME_BIN/launcher.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "launcher.com" -c "exit"