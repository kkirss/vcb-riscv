SRC := ./src
LOADERS := ./loaders
RUNTIMES := ./runtimes
BUILD := ./build

CPU_NAME ?= cpu-v0_1
MAIN_PROGRAM ?= fibonacci

TARGET := riscv64-unknown-elf
LOADER_SCRIPT := $(LOADERS)/$(CPU_NAME).ld
RUNTIME_ASSEMBLY := $(RUNTIMES)/$(CPU_NAME)/crtbegin.s

CFLAGS += -O1
CFLAGS += -mabi=ilp32
CFLAGS += -misa-spec=2.2
CFLAGS += -march=rv32i
CFLAGS += -mstrict-align
CFLAGS += -mbranch-cost=2
CFLAGS += -mtune=size
CFLAGS += -nostartfiles
CFLAGS += -T $(LOADER_SCRIPT)
#CFLAGS += -Wl,--verbose

ASSEMBLE_FLAGS += -D__riscv_ $(RUNTIME_ASSEMBLY)

NOSTART_FLAGS += -s
NOSTART_FLAGS += -nostartfiles

SOURCES := $(wildcard $(SRC)/*.c)
ALL_TARGETS := $(patsubst $(SRC)/%.c,$(BUILD)/%,$(SOURCES))

.PHONY: all
all: clean $(BUILD) compile assemble disassemble vcbmem cpu_main_program

$(BUILD):
	mkdir -p "$(BUILD)"

ASSEMBLY_FILES := $(patsubst %,%.s,$(ALL_TARGETS))
.PHONY: compile
compile: $(ASSEMBLY_FILES)

$(BUILD)/%.s: $(SRC)/%.c
	$(TARGET)-gcc -S -fverbose-asm $(CFLAGS) "$^" -o "$@"

ELF_FILES := $(patsubst %,%.elf,$(ALL_TARGETS))
.PHONY: assemble
assemble: $(ELF_FILES)

$(BUILD)/%.elf: $(SRC)/%.c
	$(TARGET)-gcc -v $(ASSEMBLE_FLAGS) $(CFLAGS) "$^" -o "$@"
#	$(TARGET)-readelf --all "$@"

DISASSEMBLED_ELF_FILES := $(patsubst %,%.elf.d,$(ALL_TARGETS))
.PHONY: disassemble
disassemble: $(DISASSEMBLED_ELF_FILES)

$(BUILD)/%.elf.d: $(BUILD)/%.elf
	$(TARGET)-objdump --disassemble "$^" > "$@"

VCBMEM_FILES := $(patsubst %,%.vcbmem,$(ALL_TARGETS))
.PHONY: vcbmem
vcbmem: $(VCBMEM_FILES)

$(BUILD)/%.bin: $(BUILD)/%.elf
	$(TARGET)-objcopy -O binary "$^" "$@"

# VCB loads memory in big-endian format
# So we need to swap the endianness for the .vcbmem file
$(BUILD)/%.vcbmem: $(BUILD)/%.bin
	$(TARGET)-objcopy -I binary -O binary --reverse-bytes=4 "$^" "$@"
	hexdump -C "$@"

.PHONY: cpu_main_program
cpu_main_program: $(BUILD)/$(MAIN_PROGRAM).vcbmem
	cp "$^" "$(BUILD)/$(CPU_NAME).vcbmem"
	cp "$^" "$(BUILD)/$(CPU_NAME)_openvcb.vcbmem"

$(BUILD)/$(CPU_NAME).vcbmem: $(BUILD)/$(MAIN_PROGRAM).vcbmem
	cp "$^" "$@"

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD)
