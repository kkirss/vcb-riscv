# vcb-riscv

Virtual Circuit Board (VCB) RISC-V CPU.

## Virtual Circuit Board

This project is for use with Virtual Circuit Board (vcb).

Buy it on Steam: https://store.steampowered.com/app/1885690/Virtual_Circuit_Board/

## Components

There is a VCB file for various common components - `components.vcb`.

It includes labels for everything and should be relatively straight-forward to understand.

## CPU

There is a VCB file for a RISC-V CPU - `cpu-v0_1.vcb`.

See [CPU-V0_1.md](CPU-V0_1.md) for more details. 

## Programs

The `programs` folder contains C/C++ programs and a `Makefile` to compile these.

### Dependencies

You need to have the following installed:
* make
* gcc (riscv64-unknown-elf-gcc)
  * Run `programs/setup/ubuntu-riscv-gnu-toolchain.sh` for easy setup on Ubuntu.

Note: The `Makefile` is tested on Ubuntu (WSL). But it should work on most Linux distros and possibly on Mac.

### Usage

To compile everything:
```
cd ./programs
make all
```

For more details on usage, run `make help`.

#### Source Code

The `src` folder contains C/C++ source code.
Each program is in its own folder.

Each program must have a `main.c`/`main.cpp` file, with a `main()` function.
This is the entry point for the program.

Each program can include other source and header files.

NB: The `Makefile` assumes the C/C++ standard library is not used.
Contributions to add support for this are especially welcome.

#### Compilation

Running `make all` will compile all programs in the `src` folder to:
* `build/<program>/main.vcbmem` - VCB VMEM file
  * VCB 'VMEM Editor' tab has an 'Edit VMEM externally' button (bottom left) to load this into VMEM.
* `build/<program>/main.elf` - Main ELF executable
* `build/<program>/main.elf.d` - RISC-V assembly
  * Disassembled from the main ELF executable.
  * Effectively, the exact assembly used for the `.vcbmem`.
* `src/<program>/<file>.s` - RISC-V assembly
  * Assembly of each source file, including comments with original source code.
  * This is not the exact assembly used for the `.vcbmem`. See `.elf.d` for that.
* `src/<program>/<file>.o` - Object file
* `src/<program>/<file>.d` - Dependency file

See the `Makefile` for more details.

## Contributing

Feel free to open issues and pull requests for improvements :)

## Library

There used to be a VCB circuit library in this repository.
I have put this piece on hold for now.

### Blueprint images

The `vcb_riscv` Python module is for generating images of blueprints.
This uses the [vcbb](https://github.com/chrjen/vcbb) project internally.

(Though the repository makes no use of this for now.)
