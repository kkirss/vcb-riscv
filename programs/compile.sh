SOURCE="${BASH_SOURCE[0]}"
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
SRC_DIR="$DIR/src"
BUILD_DIR="$DIR/build"

mkdir "$BUILD_DIR"

riscv64-unknown-elf-gcc -mabi=ilp32 -misa-spec=2.2 -march=rv32i -mstrict-align -mbranch-cost=2 -s -nostartfiles "$SRC_DIR/fibonacci.c" -o "$BUILD_DIR/fibonacci.elf"
riscv64-unknown-elf-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag -R .note -R .comment -R .eh_frame -R .eh_frame_hdr "$BUILD_DIR/fibonacci.elf"
riscv64-unknown-elf-objcopy -O binary "$BUILD_DIR/fibonacci.elf" "$BUILD_DIR/fibonacci.bin"
