#!/bin/bash

if which riscof > /dev/null 2>&1; then
    echo "riscof is already installed"
else
    echo "Installing riscof..."
    # TODO: Docs say Python 3.6 is required but using default Python instead
    pip3 install git+https://github.com/riscv/riscof.git
fi
