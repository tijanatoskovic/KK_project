#!/bin/bash

PLUGIN="DeadCodeElimination.so"
SRC="DeadCodeElimination.cpp"
TEST_DIR="tests"
OUT_DIR="tests_out"

mkdir -p "$OUT_DIR"

echo "Compiling $SRC to $PLUGIN..."
clang++ -fPIC -shared "$SRC" -o "$PLUGIN" `llvm-config --cxxflags --ldflags --system-libs --libs core passes`

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

TESTS=("test1.ll" "test2.ll" "test3.ll")

for TEST in "${TESTS[@]}"; do
    echo "Running DCE on $TEST..."
    opt -load-pass-plugin="./$PLUGIN" \
        -passes=dce-simple \
        -S "$TEST_DIR/$TEST" \
        -o "$OUT_DIR/${TEST%.ll}_out.ll"
done

echo "All DCE tests finished."
