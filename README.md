# vcb-riscv

Virtual Circuit Board / RISC-V circuit library

## Virtual Circuit Board

This project is for use with Virtual Circuit Board (vcb).

Buy it on Steam: https://store.steampowered.com/app/1885690/Virtual_Circuit_Board/

All credits goes to Virtual Circuit Board developer:
Reverie Foundry (studio run by a solo indie developer)


## Library

### Quickstart

See [QUICKSTART](library/1_QUICKSTART.md).

Sample:

<img alt="text_mono_4x5" src="./library/vcb_blueprints/images/text_4x.png" />

## Programs

There is a basic setup to compile C code into relatively compact binaries.
It's compiled into basic RV32I with 4-byte aligned memory access (`-mstrict-align`).

### Compilation

Run `./programs/compile.sh` to compile the C code.
The compiled output will be in the `projects/build` folder, in the `*.bin` file.

### Assembly

Run `./programms/assembly.sh` to generate assembly from the C code.
The compiled output will be in the `projects/build` folder, in the `*.s` file.

### Cleanup

Run `./programs/clean.sh` to clean all binary files.


## Contributing

Feel free to open issues and pull requests for improvements :)
