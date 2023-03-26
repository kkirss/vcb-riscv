#!/bin/bash
echo "Creating /opt/riscv folder..."
sudo mkdir /opt/riscv
echo "Giving $USER ownership to the /opt/riscv folder..."
sudo chown -R $USER:$USER /opt/riscv

echo "Installing riscv-gnu-toolchain dependencies for Ubuntu..."
sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

cd ~
echo "Cloning riscv-gnu-toolchain into ~/riscv-gnu-toolchain..."
echo "Note: You can delete this folder after the script is finished"
git clone https://github.com/riscv/riscv-gnu-toolchain
echo "Compiling riscv-gnu-toolchain..."
echo "Note: This will take ~1 hour"
cd riscv-gnu-toolchain
./configure --prefix=/opt/riscv --enable-multilib
make
echo "NB: Add /opt/riscv to your system PATH"
