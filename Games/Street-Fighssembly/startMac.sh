clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Street-Fighssembly"
GAME_BIN="$GAME_DIR/bin"
DOSBOX_BIN="/Users/$USER/Desktop/dosbox.app/Contents/MacOS/DOSBox"
DOSBOX_CONF="/Users/$USER/Library/Preferences/DOSBox 0.74-3-3 Preferences"

# Assemble the .asm sprites
find "$GAME_DIR/Sprites" -type f -name '*.asm' | while read -r asm_file; do
    filename=$(basename "$asm_file" .asm)
    output_file="$GAME_BIN/${filename}.bin"
    "$NASM" "$asm_file" -f bin -o "$output_file"
done

# Assemble the game
"$NASM" "$GAME_DIR/main.asm" -f bin -o "$GAME_BIN/SF.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "loadhigh SF.com" -c "exit"