SRC := ./src
LOADERS := ./loaders
RUNTIMES := ./runtimes
BUILD := ./build

CPU_NAME ?= cpu-v0_1
MAIN_PROGRAM ?= display_hello

TARGET := riscv64-unknown-elf
LOADER_SCRIPT := $(LOADERS)/$(CPU_NAME).ld
RUNTIME_ASSEMBLY := $(RUNTIMES)/$(CPU_NAME)/crtbegin.s

CC := $(TARGET)-g++
CFLAGS += -O1
CFLAGS += -mabi=ilp32
CFLAGS += -misa-spec=2.2
CFLAGS += -march=rv32i
CFLAGS += -mstrict-align
CFLAGS += -mbranch-cost=2
CFLAGS += -mtune=size
CFLAGS += -nostartfiles
CFLAGS += -T $(LOADER_SCRIPT)
CFLAGS += -MD -MP
# Verbose logging
#CFLAGS += --verbose
#CFLAGS += -Wl,--verbose

CXX := $(TARGET)-g++
CXXFLAGS := $(CFLAGS)

LDFLAGS += -D__riscv_ $(RUNTIME_ASSEMBLY)

.PHONY: all clean build_dirs assembly_files object_files link disassemble vcb_vmem vcb_main_program
all: clean build_dirs assembly_files object_files link disassemble vcb_vmem vcb_main_program ## Run all of the steps below

####
# Create build directories
####

SOURCE_DIRS := $(wildcard $(SRC)/**/)
BUILD_DIRS := $(patsubst $(SRC)%,$(BUILD)%,$(SOURCE_DIRS))

build_dirs: $(BUILD) $(BUILD_DIRS) ## Create build directories

$(BUILD)/%/:
	mkdir -p "$@"

$(BUILD):
	mkdir -p "$(BUILD)"

####
# Compile C object & assembly files
####

C_SOURCES := $(wildcard $(SRC)/**/*.c)
C_OBJECT_FILES := $(patsubst %.c,%.o,$(C_SOURCES))
C_ASSEMBLY_FILES := $(patsubst %.c,%.s,$(C_SOURCES))

object_files: $(C_OBJECT_FILES) ## Compile object files (.o)

# %.o:
#	(uses implicit Makefile rule)

assembly_files: $(C_ASSEMBLY_FILES) ## Compile assembly files (.s)

%.s: %.c
	$(CC) -S -fverbose-asm $(CFLAGS) "$^" -o "$@"

####
# Compile C++ object & assembly files
####

CPP_SOURCES := $(wildcard $(SRC)/**/*.cpp)
CPP_OBJECT_FILES := $(patsubst %.cpp,%.o,$(CPP_SOURCES))
CPP_ASSEMBLY_FILES := $(patsubst %.cpp,%.s,$(CPP_SOURCES))

object_files: $(CPP_OBJECT_FILES) $(CPP_ASSEMBLY_FILES)

# %.o:
#	(uses implicit Makefile rule)

assembly_files: $(CPP_ASSEMBLY_FILES)

%.s: %.cpp
	$(CC) -S -fverbose-asm $(CFLAGS) "$^" -o "$@"

####
# Link object files to executables
####

MAIN_ELF_FILES := $(patsubst %,%main.elf,$(BUILD_DIRS))

link: $(MAIN_ELF_FILES) ## Link object files to executable files (.elf)

$(BUILD)/%/main.elf: $(SRC)/%/*.o
	@echo "Linking" $^ "to" $@
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o "$@"
#	$(TARGET)-readelf --all "$@"

####
# Disassemble executables
####

MAIN_ELF_D_FILES := $(patsubst %,%main.elf.d,$(BUILD_DIRS))
disassemble: $(MAIN_ELF_D_FILES) ## Disassemble executable files (.elf.d)

%.elf.d: %.elf
	$(TARGET)-objdump --disassemble "$^" > "$@"

####
# VCB VMEM conversion
####

VCB_VMEM_FILES := $(patsubst %,%main.vcbmem,$(BUILD_DIRS))

vcb_vmem: $(VCB_VMEM_FILES) ## Convert executable files to VCB VMEM files (.vcbmem)

%.bin: %.elf
	$(TARGET)-objcopy -O binary "$^" "$@"

# VCB loads memory in big-endian format
# So we need to swap the endianness for the .vcbmem file
%.vcbmem: %.bin
	$(TARGET)-objcopy -I binary -O binary --reverse-bytes=4 "$^" "$@"
	hexdump -C "$@"

####
# Copy main program VCB VMEM file
####

vcb_main_program: $(BUILD)/$(CPU_NAME).vcbmem ## Copy VCB main program (MAIN_PROGRAM/main.vcbmem -> CPU_NAME.vcbmem)

$(BUILD)/$(CPU_NAME).vcbmem: $(BUILD)/$(MAIN_PROGRAM)/main.vcbmem
	cp "$^" "$@"

####
# Clean built files
####

clean: ## Clean up built files
	@echo "Cleaning up..."
	rm -rf $(BUILD)
	rm -rf $(SRC)/**/*.o
	rm -rf $(SRC)/**/*.d
	rm -rf $(SRC)/**/*.s

###
# Print help message
###
C_BLUE := \033[0;34m
C_STEP := $(C_BLUE)
C_END := \033[0m
LONGEST_TARGET_LEN := $(shell grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "%s\n", $$1}' | awk '!len || length($1) > len {len=length($1)} END{print len}')

.DEFAULT_GOAL := help
.PHONY: help
help: ## Print this help message
	@echo "Usage: make $(C_STEP)<target>$(C_END)"
	@echo ""
	@echo "Available targets:"
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "$(C_STEP)%-$(LONGEST_TARGET_LEN)s$(C_END) %s\n", $$1, $$2}'
