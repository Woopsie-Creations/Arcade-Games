clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="nasm"  # Assumes NASM is installed globally
GAME_DIR="$ROOT_DIR/Pac-ssembly"
GAME_BIN="$GAME_DIR/Bin"
DOSBOX_BIN="/usr/bin/dosbox"
DOSBOX_CONF="$HOME/.dosbox/dosbox-0.74.conf"
CONF="$ROOT_DIR/DOSBox-Conf"

# Ensure DOSBox-Conf directory exists
mkdir -p "$CONF"

# Assemble the game
"$NASM" "$GAME_DIR/main.asm" -f bin -o "$GAME_BIN/PS.com"

# Run the game with the explicit config
"$DOSBOX_BIN" -conf "$CONF/DOSBox.conf" -c "MOUNT c $GAME_BIN" -c "c:" -c "PS.com" -c "exit"