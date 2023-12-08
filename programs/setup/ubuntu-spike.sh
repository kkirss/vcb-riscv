#!/bin/bash

SPIKE_PATH="/opt/riscv/riscv64-unknown-elf/bin/spike"
if [ -f "$SPIKE_PATH" ]; then
    echo "Spike RISC-V simulator is already installed"
else
    echo "Installing Spike RISC-V simulator..."

    if ! which dtc > /dev/null 2>&1; then
        echo "Installing device-tree-compiler..."
        sudo apt-get install device-tree-compiler
    fi

    RISCV_ISA_SIM_REPO_DIR="$HOME/riscv-isa-sim"
    if [ -d "$RISCV_ISA_SIM_REPO_DIR" ]; then
        echo "riscv-isa-sim already cloned"
    else
        echo "Cloning riscv-isa-sim into home directory, you can delete this later"
        git clone https://github.com/riscv-software-src/riscv-isa-sim.git "$RISCV_ISA_SIM_REPO_DIR"
    fi

    PREV_DIR=$(pwd)
    cd "$RISCV_ISA_SIM_REPO_DIR"

    mkdir build
    cd build
    ../configure --prefix=/opt/riscv/riscv64-unknown-elf
    make
    make install

    cd "$PREV_DIR"
fi
