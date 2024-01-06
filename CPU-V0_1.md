# 32-bit Pipelined RISC-V CPU

This document describes the v0.1 CPU project - `cpu-v0_1.vcb`.

## Specs

* RISC-V 32-bit integer ISA (RV32I)
* 5 stage pipeline with forwarding
* 11-tick clock
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

* Memory only works for word-aligned access.
    * gcc compiler flag `-mstrict-align` enforces this.
* `ecall` doesn't do anything
* `ebreak` doesn't do anything
* Exceptions/traps aren't raised

## Planned improvements

* [x] Use faster adder for ALU
* [x] Add Virtual Display
* [ ] Write display driver for Virtual Display
* [x] Add data forwarding to avoid RAW hazard halts
* [ ] Speed up clock (in ticks)
* [ ] Use a more compact PC incrementor
* [x] Add support for byte & half-word loads

(Leaving out multiplication, division & floating point math for now. Perhaps something for the next version.)

## Credits

Credits to VCB Discord community members:

* @Erikbot's decoder & VMEM controller
* @Jerry's register file cell
* @nikamir's VICP inspired the chip-based design
* @liq3's adder & async memory controller concept
* @rty's adder
* @Cake_Eater's signed decimal display

Huge thanks to you 🙂

## Community

There's [a thread about this project in the VCB Discord community](https://discord.com/channels/937059867615694889/1087508766020349992/1087508766020349992)

## Technical Details

### Multiplexers

All multiplexers required:

* PC-SRC
    * 1: alu-out / j-target
    * 0: PC+4
* ALU-I2-SRC
    * 11: EX-OUT-DATA
    * 10: WRITE-DATA
    * 01: imm
    * 00: r2
* ALU-I1-SRC
    * 11: EX-OUT-DATA
    * 10: WRITE-DATA
    * 01: PC
    * 00: r1
* R2-SRC
    * 11: EX-OUT-DATA
    * 10: WRITE-DATA
    * 00: r2
* R1-SRC
    * 11: EX-OUT-DATA
    * 10: WRITE-DATA
    * 00: r1
* EX-OUT-SRC:
    * 10: PC+4
    * 01: imm
    * 00: alu-out
* MEM-OUT-SRC
    * 1: load-data
    * 0: ex-out-data

### Pipeline

The CPU pipeline consists of 5 stages:

* IF: Instruction Fetch
* ID: Instruction Decode
* EX: Execute
* MEM: Memory
* WB: Write Back

#### RAW Hazard Controller

Note: Outdated

##### Inputs

Input signals:

* R1
    * RS1==PC-1-RD -> Previous instruction 'may write to RS1'
    * PC-2-WRITE-RS-1 = (RS1==PC-2-RD && PC-2-REG-WRITE) -> Second before instruction 'writes to RS1'
* R2
    * RS2==PC-1-RD -> Previous instruction 'may write to RS2'
    * PC-2-WRITE-RS-2 = (RS2==PC-2-RD && PC-2-REG-WRITE) -> Second before instruction 'writes to RS2'
* Both
    * PC-1-REG-WRITE -> Previous instruction 'writes to register file'
    * PC-1-MEM-LOAD -> Previous instruction 'loads from memory'
* *PC-2-MEM-LOAD is irrelevant -> the value is already in the MEM pipeline register*

Assumptions for inputs:

```
if (PC-1-MEM-LOAD) {
  assert (PC-1-REG-WRITE);
}
```

##### Outputs

Hazard control signals:

* R1, one of:
    * R1-EX-STALL
    * R1-SRC-PC-1
    * R1-SRC-PC-2
    * R2-SRC-REG
* R2, one of:
    * R2-EX-STALL
    * R2-SRC-PC-1
    * R2-SRC-PC-2
    * R2-SRC-imm
    * R2-SRC-REG
* EX-STALL = (R1-EX-STALL || R2-EX-STALL), sets all of:
    * IF-STALL
    * ID-STALL
    * EX-STALL
    * MEM-FLUSH

##### Logic

R1 logic:

```
if (RS1==PC-1-RD) { // Previous instruction 'may write to RS1'
  if (PC-1-REG-WRITE) { // Previous instruction 'writes to RS1'
    if (PC-1-MEM-LOAD) { // Previous instruction 'loads from memory' -> stall, not available yet
      set UNTIL-EX-STALL;
    } else { // Previous instruction 'calculates in EX stage' -> get R1 from MEM pipeline register
      set R1-SRC-PC-1;
    }
  }
  if (RS1==PC-2-RD && PC-2-REG-WRITE) { // Second before instruction 'writes to RS1' -> get R1 from MEM pipeline register
    set R1-SRC-PC-2;
  } else { // Second before instruction 'doesn't write to RS1' -> get R1 from register file
    set R2-SRC-REG;
  }
} else { // Previous instruction 'doesn't write to RS1''
  if (RS1==PC-2-RD && PC-2-REG-WRITE) { // Second before instruction 'writes to RS1' -> get R1 from MEM pipeline register
    set R1-SRC-PC-2;
  } else { // Second before instruction 'doesn't write to RS1' -> get R1 from register file
    set R2-SRC-REG;
  }
}
```

R1 truth table:
| RS1==PC-1-RD | PC-1-REG-WRITE | PC-1-MEM-LOAD | PC-2-WRITE-RS-1 | OUT |
|--------------|----------------|---------------|-----------------|--------------|
| 0 | 0 | 0 | 0 | R2-SRC-REG |
| 0 | 0 | 0 | 1 | R1-SRC-PC-2 |
| 0 | 0 | 1 | 0 | x |
| 0 | 0 | 1 | 1 | x |
| 0 | 1 | 0 | 0 | R2-SRC-REG |
| 0 | 1 | 0 | 1 | R1-SRC-PC-2 |
| 0 | 1 | 1 | 0 | R2-SRC-REG |
| 0 | 1 | 1 | 1 | R1-SRC-PC-2 |
| 1 | 0 | 0 | 0 | R2-SRC-REG |
| 1 | 0 | 0 | 1 | R1-SRC-PC-2 |
| 1 | 0 | 1 | 0 | x |
| 1 | 0 | 1 | 1 | x |
| 1 | 1 | 0 | 0 | R1-SRC-PC-1 |
| 1 | 1 | 0 | 1 | R1-SRC-PC-1 |
| 1 | 1 | 1 | 0 | R1-EX-STALL |
| 1 | 1 | 1 | 1 | R1-EX-STALL |

R2 logic is the same as R1.

### Critical Path

The critical path is BRANCH instruction in the EX stage:

1. 1 tick to read register file
2. 1 tick for ALU input multiplexers
3. 3 ticks for comparator
4. 1 tick for comparison multiplexer
5. 1 tick for checking whether EX stage should be flushed and splitting writes to pipeline stage control lines.
6. 2 ticks for PC-SRC multiplexer
    * 1 tick concurrently for pipeline stage clock controller
7. 1 tick for pipeline stage store

Total: ~~10 ticks~~ 11 ticks (temporarily due to bottleneck in PC adders but will use ALU to avoid it)
