SRC := ./src
LOADERS := ./loaders
RUNTIMES := ./runtimes
BUILD := ./build

CPU_NAME ?= cpu-v0_1
MAIN_PROGRAM ?= fibonacci

TARGET := riscv64-unknown-elf
LOADER_SCRIPT := $(LOADERS)/$(CPU_NAME).ld
RUNTIME_ASSEMBLY := $(RUNTIMES)/$(CPU_NAME)/crtbegin.s

CC := $(TARGET)-gcc
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

LDFLAGS += -D__riscv_ $(RUNTIME_ASSEMBLY)

C_SOURCES := $(wildcard $(SRC)/*.c)

.PHONY: all
all: clean $(BUILD) compile assemble disassemble vcbmem cpu_main_program

$(BUILD):
	mkdir -p "$(BUILD)"

.PHONY: compile
compile: $(patsubst $(SRC)/%.c,$(BUILD)/%.s,$(C_SOURCES))

$(BUILD)/%.s: $(SRC)/%.c
	$(CC) -S -fverbose-asm $(CFLAGS) "$^" -o "$@"

.PHONY: assemble
assemble: $(patsubst $(SRC)/%.c,$(BUILD)/%.elf,$(C_SOURCES))

$(BUILD)/%.elf: $(SRC)/%.c
	$(CC) $(LDFLAGS) $(CFLAGS) "$^" -o "$@"
#	$(TARGET)-readelf --all "$@"

.PHONY: disassemble
disassemble: $(patsubst $(SRC)/%.c,$(BUILD)/%.elf.d,$(C_SOURCES))

$(BUILD)/%.elf.d: $(BUILD)/%.elf
	$(TARGET)-objdump --disassemble "$^" > "$@"

.PHONY: vcbmem
vcbmem: $(patsubst $(SRC)/%.c,$(BUILD)/%.vcbmem,$(C_SOURCES))

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
