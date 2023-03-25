# 32-bit Pipelined RISC-V CPU

This document describes the v0.1 CPU project - `cpu-v0_1.vcb`.

## Specs

* RISC-V 32-bit integer ISA (RV32I)
* 5 stage pipeline (with register RAW- & control hazard halts)
* 15-tick clock
* 32 registers
* VMEM for instruction & data memory

## Goals

* Compile C code to .vcbmem (for ease of programming)
* Use pipelining (to learn more about it)
* Clarity/documentation in the VCB project
* Avoid using tunnels, meshes & wireless inks
* Low clock period in ticks
* Use chip-based design with decoration layer (like VICP)
* Compact design

## Limitations

* The CPU hasn't been extensively tested.
  So there could be un-discovered bugs. 
* Memory only works for word-aligned access.
  * gcc compiler flag `-mstrict-align` enforces this.
* `lb`/`lbu` (load byte) doesn't work
* `lh`/`lhu` (load half-word) doesn't work
* `ecall` doesn't do anything
* `ebreak` doesn't do anything
* Exceptions/traps aren't raised
* Instruction fetches don't halt for stores in the pipeline.
  * If you modify programs 2 instructions from PC, the CPU will execute the old instruction. (Very unlikely to happen in practice.)

## Planned improvements

* [x] Use faster adder for ALU
* [ ] Add Virtual Display
* [ ] Write display driver for Virtual Display
* [ ] Add data forwarding to avoid RAW hazard halts
* [ ] Speed up clock (in ticks)
* [ ] Use a more compact PC incrementor
* [ ] Add support for byte & half-word loads
* [ ] Handle VMEM RAW hazards for instruction fetches

(Leaving out multiplication, division & floating point math for now. Perhaps something for the next version.)

## Credits

Credits to VCB Discord community members:
* @Erikbot's decoder & VMEM controller
* @Jerry's register file cell
* @nikamir's VICP inspired the chip-based design
* @liq3's adder & async memory controller concept
* @Cake_Eater's signed decimal display
Huge thanks to you 🙂

## Community

There's [a thread about this project in the VCB Discord community](https://discord.com/channels/937059867615694889/1087508766020349992/1087508766020349992)
