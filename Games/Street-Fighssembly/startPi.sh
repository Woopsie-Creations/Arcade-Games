clear

# Set up paths
ROOT_DIR="$(dirname "$(realpath "$0")")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
NASM="nasm"  # Assumes NASM is installed globally
GAME_DIR="$ROOT_DIR/Street-Fighssembly"
GAME_BIN="$GAME_DIR/bin"
DOSBOX_BIN="/usr/bin/dosbox"
DOSBOX_CONF="$HOME/.dosbox/dosbox-0.74.conf"
CONF="$ROOT_DIR/DOSBox-Conf"

# Ensure DOSBox-Conf directory exists
mkdir -p "$CONF"

# Assemble the game
"$NASM" "$GAME_DIR/Main.asm" -f bin -o "$GAME_BIN/SF.com"

# Generate a new DOSBox config with required settings
"$DOSBOX_BIN" -c "config -writeconf $CONF/DOSBox.conf" -c "exit"

# Verify if the config file was actually created
if [ ! -f "$CONF/DOSBox.conf" ]; then
    echo "Error: DOSBox config file was not created."
    exit 1
fi

# Ensure the correct config file is being used
rm -f "$DOSBOX_CONF"
cp "$CONF/DOSBox.conf" "$DOSBOX_CONF"

# Run the game with the explicit config
"$DOSBOX_BIN" -conf "$CONF/DOSBox.conf" -c "MOUNT c $GAME_BIN" -c "c:" -c "SF.com" -c "exit"