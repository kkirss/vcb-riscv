#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
SRC_DIR="$DIR/src"
BUILD_DIR="$DIR/build"

mkdir -p "$BUILD_DIR"

riscv64-unknown-elf-gcc -S -mbranch-cost=2 -mabi=ilp32 -misa-spec=2.2 -march=rv32i -mstrict-align -o "$BUILD_DIR/fibonacci.s" "$SRC_DIR/fibonacci.c"
