#!/bin/bash

if which riscof > /dev/null 2>&1; then
    echo "riscof is already installed"
else
    echo "Installing riscof..."
    # TODO: Docs say Python 3.6 is required but using default Python instead
    pip3 install git+https://github.com/riscv/riscof.git
fi

if which riscv32-unknown-elf-gcc > /dev/null 2>&1; then
    echo "riscv32-unknown-elf-gcc is already installed/linked"
else
    echo "Creating link to riscv32-unknown-elf-gcc..."
    echo "(The 64-bit compiler supports 32-bit compilation. But riscof doesn't know that.)"
    ln -s /opt/riscv/bin/riscv64-unknown-elf-gcc /opt/riscv/bin/riscv32-unknown-elf-gcc
fi