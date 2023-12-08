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

See [Tests](#tests) for details on running tests.

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

## Tests

Tests can be run semi-automatically for the CPU using [RISCOF - The RISC-V Compatibility Framework](https://riscof.readthedocs.io/en/stable/intro.html).

Each test is run on a reference CPU (Spike) and the VCB CPU (i.e. DUT - Device Under Test).
The tests write to a specific memory area, resulting in a 'signature'.
The signatures are compared to determine if the test passed or failed.

### Dependencies

You need to have the following installed:
* Python 3 & pip (already installed on most systems)
* gcc (riscv64-unknown-elf-gcc)
  * Run `programs/setup/ubuntu-riscv-gnu-toolchain.sh` for easy setup on Ubuntu.
* [RISCOF](https://riscof.readthedocs.io/en/stable/installation.html#install-riscof)
  * Run `programs/setup/ubuntu-riscof.sh` for easy setup on Ubuntu.
* [Spike](https://github.com/riscv-software-src/riscv-isa-sim#build-steps)
  * Run `programs/setup/ubuntu-spike.sh` for easy setup on Ubuntu.

#### Testing in VCB

**NB:** You need to enable persistent VMEM in VCB.
You can do this by setting VMEM Settings -> Persistent Memory to be `0x0` to `0xfffff` 

During a test run, the script will handle all the compilation and .vcbmem file management.

Running the test in VCB has to be done manually.
During a test run, GNOME Terminal windows are opened with instructions.

### Running all tests

To run all tests:
```
cd ./programs
make riscof_run
```

Note: There are a lot of tests.
As each of them requires a manual step, it might be better to run them individually.

### Running a specific test

To run a specific test, first generate separate test files:
```
make riscof_separate_tests
```

Then run the test:
```
make riscof_run_<test>
```

### Test results

After running a test, an HTML report is generated in `programs/riscof/riscof_work/report.html`.

The signatures files are stored in `programs/riscof/riscof_work/rv32i_m/I/src/*/dut|ref/*.signature`.

### Debugging

#### Disassembly

To get a better idea of what the test are doing, you can disassemble the test ELF files:
```
make riscof_disassemble
```
You can then view the assembly files in `programs/riscof/riscof_work/rv32i_m/I/src/*/dut/my.elf.d`.
(This is the exact assembly used for the `.vcbmem`.)

#### Source code

You can find the source code for each test in `programs/riscof/riscv-arch-test/riscv-test-suite/rv32i_m/I/src`.

Note that these use macros, which can obfuscate things a bit.
You can find the macros in `programs/riscof/riscv-arch-test/riscv-test-suite/env`

#### Debugging in VCB

You can debug the test in VCB by letting the test copy the `.vcbmem` file and stopping it.

Note: I'm not sure if the tests are idempotent, so you might want to disable VMEM persistence while doing this.

## Contributing

Feel free to open issues and pull requests for improvements :)

## Library

There used to be a VCB circuit library in this repository.
I have put this piece on hold for now.

### Blueprint images

The `vcb_riscv` Python module is for generating images of blueprints.
This uses the [vcbb](https://github.com/chrjen/vcbb) project internally.

(Though the repository makes no use of this for now.)
