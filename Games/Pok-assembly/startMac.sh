clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="/opt/homebrew/bin/nasm"
GAME_DIR="$ROOT_DIR/Pok-assembly"
GAME_BIN="$GAME_DIR/Bin"
DOSBOX_BIN="/Users/$USER/Desktop/dosbox.app/Contents/MacOS/DOSBox"

# Assemble the .asm sprites
rm -rf "$GAME_BIN/Sprites/"*
rm -rf "$GAME_BIN/Sprites/".* 2>/dev/null

find "$GAME_DIR/Sprites" -type f -name '*.asm' | while read -r asm_file; do
    filename=$(basename "$asm_file" .asm)
    output_file="$GAME_BIN/Sprites/${filename}.bin"
    "$NASM" "$asm_file" -f bin -o "$output_file"
done

# Assemble the game
"$NASM" "$GAME_DIR/main.asm" -f bin -o "$GAME_BIN/PA.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -c "MOUNT c $GAME_BIN" -c "c:" -c "loadhigh PA.com" -c "exit"