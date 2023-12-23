#!/bin/bash
RISCV_PREFIX="/opt/riscv"

if [ -d "$RISCV_PREFIX" ]; then
    echo "RISC-V toolchain found in $RISCV_PREFIX"
else
    echo "Creating $RISCV_PREFIX folder..."
    sudo mkdir /opt/riscv
    echo "Giving $USER ownership to the $RISCV_PREFIX folder..."
    sudo chown -R $USER:$USER $RISCV_PREFIX

    echo "Installing riscv-gnu-toolchain dependencies for Ubuntu..."
    sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

    RISCV_GNU_TOOLCHAIN_DIR="$HOME/riscv-gnu-toolchain"
    if [ -d "$RISCV_GNU_TOOLCHAIN_DIR" ]; then
        echo "riscv-gnu-toolchain folder found in $RISCV_GNU_TOOLCHAIN_DIR"
        cd "$RISCV_GNU_TOOLCHAIN_DIR" || exit 1
        echo "Updating riscv-gnu-toolchain..."
        git pull
        git submodule update --recursive --remote
        make clean
    else
        echo "Cloning riscv-gnu-toolchain into $RISCV_GNU_TOOLCHAIN_DIR..."
        echo "Note: You can delete this folder after the script is finished"
        git clone https://github.com/riscv/riscv-gnu-toolchain "$RISCV_GNU_TOOLCHAIN_DIR"
        cd "$RISCV_GNU_TOOLCHAIN_DIR" || exit 1
    fi

    echo "Compiling riscv-gnu-toolchain..."
    echo "Note: This will take ~1 hour"
    ./configure --prefix="$RISCV_PREFIX" --enable-multilib
    make
fi

echo "Checking if riscv-gnu-toolchain is installed..." # By running `riscv64-unknown-elf-gcc --version` and checking if it returns 0
$RISCV_PREFIX/bin/riscv64-unknown-elf-gcc --version
if [ $? -eq 0 ]; then
    echo "riscv-gnu-toolchain was installed correctly"

    riscv64-unknown-elf-gcc --version > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "riscv-gnu-toolchain is already in PATH"
    else
        echo "NB: Add $RISCV_PREFIX/bin to your system PATH"
    fi
else
    echo "riscv-gnu-toolchain was not installed correctly"
    echo "Exiting..."
    exit 1
fi
