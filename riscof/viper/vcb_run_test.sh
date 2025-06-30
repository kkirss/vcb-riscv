#!/bin/bash
RISCV_PREFIX=riscv64-unknown-elf-

cwd="$(pwd)"

VCB_FILE="$1"
ELF_FILE="$2"
SIGNATURE_FILE="$3"

BIN_FILE="${ELF_FILE%.elf}.bin"
VCBMEM_ORIGINAL_FILE="${ELF_FILE%.elf}.vcbmem"
VCBMEM_RUNNING_FILE="${VCB_FILE%.vcb}.vcbmem"
VCBMEM_IMAGE_FILE="${ELF_FILE%.elf}.vcbmem_image"

echo "Running VCB test $ELF_FILE for $VCB_FILE"

# Extract signature location from ELF file
echo "Extracting signature location from ELF file"
SIGNATURE_BEGIN_LOCATION_HEX=$(${RISCV_PREFIX}objdump -t "$ELF_FILE" | awk '/rvtest_sig_begin/ {print $1}')
SIGNATURE_END_LOCATION_HEX=$(${RISCV_PREFIX}objdump -t "$ELF_FILE" | awk '/rvtest_sig_end/ {print $1}')
SIGNATURE_LENGTH_DEC=$(("0x${SIGNATURE_END_LOCATION_HEX}" - "0x${SIGNATURE_BEGIN_LOCATION_HEX}"))

# Convert the ELF file to VCB VMEM format
echo "Converting ELF executable to VCB VMEM file"
${RISCV_PREFIX}objcopy -O binary "$ELF_FILE" "$BIN_FILE"
${RISCV_PREFIX}objcopy -I binary -O binary --reverse-bytes=4 "$BIN_FILE" "$VCBMEM_ORIGINAL_FILE"

# Disassemble the ELF file
echo "Disassembling ELF executable"
${RISCV_PREFIX}objdump --disassemble --source "$ELF_FILE" > "${ELF_FILE}.d"

# Confirm if the user is ready to start the test
echo ""
echo "Press any key to prepare test. (This will overwrite the running vcbmem file.)"
read -n 1 -s

# Copy the original vcbmem file to the running vcbmem file
echo "Copying $VCBMEM_ORIGINAL_FILE to $VCBMEM_RUNNING_FILE"
cp "$VCBMEM_ORIGINAL_FILE" "$VCBMEM_RUNNING_FILE"

# Wait for the user to run the simulation
echo ""
echo "Please run the simulation in Virtual Circuit Board:"
echo "1. Start the simulation (Tab)"
echo "2. Wait for the simulation to get stuck in a loop"
echo "3. Exit the simulation (Tab), you should see a message 'Persistent memory preserved.'"
echo ""
echo "Press any key once done."
read -n 1 -s

# Generate signature file from .vcbmem file
echo "Generating signature file $SIGNATURE_FILE"
${RISCV_PREFIX}objcopy -I binary -O binary --reverse-bytes=4 "$VCBMEM_RUNNING_FILE" "$VCBMEM_IMAGE_FILE"
hexdump --skip "0x${SIGNATURE_BEGIN_LOCATION_HEX}" --length "$SIGNATURE_LENGTH_DEC" --no-squeezing --format '1/4 "%08x" "\n"' "$VCBMEM_IMAGE_FILE" > "$SIGNATURE_FILE"
