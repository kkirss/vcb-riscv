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
#CFLAGS += -Wl,--verbose

CXX := $(TARGET)-g++
CXXFLAGS := $(CFLAGS)

LDFLAGS += -D__riscv_ $(RUNTIME_ASSEMBLY)

.PHONY: all
all: clean build_dirs assembly_files object_files link vcb_vmem vcb_main_program

####
# Create build directories
####

SOURCE_DIRS := $(wildcard $(SRC)/**/)
BUILD_DIRS := $(patsubst $(SRC)%,$(BUILD)%,$(SOURCE_DIRS))

.PHONY: build_dirs
build_dirs: $(BUILD) $(BUILD_DIRS)

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

.PHONY: object_files
object_files: $(C_OBJECT_FILES)

# %.o:
#	(uses implicit Makefile rule)

.PHONY: assembly_files
assembly_files: $(C_ASSEMBLY_FILES)

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
MAIN_ELF_D_FILES := $(patsubst %,%main.elf.d,$(BUILD_DIRS))

.PHONY: link
link: $(MAIN_ELF_FILES) $(MAIN_ELF_D_FILES)

$(BUILD)/%/main.elf: $(SRC)/%/*.o
	@echo "Linking" $^ "to" $@
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o "$@"
#	$(TARGET)-readelf --all "$@"

%.elf.d: %.elf
	$(TARGET)-objdump --disassemble "$^" > "$@"

####
# VCB VMEM conversion
####

VCB_VMEM_FILES := $(patsubst %,%main.vcbmem,$(BUILD_DIRS))

.PHONY: vcb_vmem
vcb_vmem: $(VCB_VMEM_FILES)

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

.PHONY: vcb_main_program
vcb_main_program: $(BUILD)/$(CPU_NAME).vcbmem

$(BUILD)/$(CPU_NAME).vcbmem: $(BUILD)/$(MAIN_PROGRAM)/main.vcbmem
	cp "$^" "$@"

####
# Clean built files
####

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD)
	rm -rf $(SRC)/**/*.o
	rm -rf $(SRC)/**/*.d
	rm -rf $(SRC)/**/*.s
