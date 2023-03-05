# CPU Notes

Misc notes on CPU design.

## Preface

Where instructions are listed, they may not be exhaustive.
Only significantly different instructions are listed.

## Dataflow

### Jump targets

All jump targets:
* PC+imm (JAL, BRANCH)
* rs1+imm (JALR)

### Register write sources

All register write sources:
* rs1#r2 (OP)
* rs1#imm (OP-IMM)
* load-data (STORE)
* PC+4 (JAL, JALR)
* imm (LUI)
* PC+imm (AUIPC)

## ALU Usage

Some instructions need to do multiple operations, which an ALU could do.
Thus, there's a need to choose which operation the ALU is used for.

### Multiple operation instructions

TODO: Needs finalizing

Instructions that require multiple operations:
* JAL: PC+imm & PC+4
* JALR: r1+imm & PC+4
* BRANCH: r1?r2 & PC+imm

### ALU Usage Choice

Choice primarily depends on the BRANCH instruction.
Either r1?r2 or PC+imm needs a separate component.

Separate r1?r2 advantages:
1. TODO Are there any?

Separate PC+imm advantages:
1. Could potentially be calculated in the ID stage already.
   * This could allow JAL to jump faster, reducing pipeline bubbles.
2. Doesn't require a subtractor.

## Multiplexers

TODO: Needs finalizing

All multiplexers required:
* PC-SRC
  * 1: jump-target
  * 0: PC+4
* ALU-INP2
  * 1: r2
  * 0: imm
* JUMP-TARGET:
  * 1: PC+imm
  * 2: alu-out
* EX-OUT-DATA:
  * 11: PC+imm
  * 10: PC+4
  * 01: imm
  * 00: alu-out
* MEM-OUT-DATA
  * 1: mem-read-data
  * 0: ex-out-data