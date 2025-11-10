DIRS=(
    "da_x"
)

CURRENT_DIR=$(pwd)
rm -rf CURRENT_DIR/payloads

for DIR in "${DIRS[@]}"; do
    echo "Building in directory: $DIR"
    (cd "$DIR" && make clean && ./build.sh)
    cd "$CURRENT_DIR"
done
