# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Launcher"
GAME_BIN="$GAME_DIR/Bin"
DOSBOX_BIN="/Users/$USER/Desktop/dosbox.app/Contents/MacOS/DOSBox"
FILE_PATH="$GAME_BIN/file.txt"

clear 

# Assemble the game
"$NASM" "$GAME_DIR/launcher.asm" -f bin -o "$GAME_BIN/launcher.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "launcher.com" -c "exit"

# Read the file
if [ -f "$FILE_PATH" ]; then
    GAME_PATH=$(head -n 1 "$FILE_PATH" | sed 's/[[:space:]]*$//')
else
    echo "Error: File not found: $FILE_PATH"
    exit 1
fi

# Extract game directory and filename correctly
GAME_DIR=$(dirname "$GAME_PATH")
GAME_FILE=$(basename "$GAME_PATH")

clear

# Execute in DOSBox
"$DOSBOX_BIN" -c "MOUNT c $ROOT_DIR/$GAME_DIR" -c "c:" -c "loadhigh $GAME_FILE" -c "exit"

./startMac.sh