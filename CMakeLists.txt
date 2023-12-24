cmake_minimum_required(VERSION 3.13)
project(vcb-riscv VERSION 1.0)

set(CPU_NAME "cpu-v0_1")

set(RAM_SIZE "4096K") # 4096K bytes is max size of VMEM (20 bit address of 32-bit word -> 2^20 * (32/8) = 4096K)
set(DISPLAY_POINTER_ADDRESS "0x3FFFF4")
set(DISPLAY_BUFFERS_START "0x300000")
set(DISPLAY_BUFFERS_SIZE "900K")
set(STACK_SIZE "4K")
set(STACK_TOP "0x2FFFFC")

set(LINKER_SCRIPTS "${CMAKE_SOURCE_DIR}/linker_scripts")
set(INIT_ASSEMBLIES "${CMAKE_SOURCE_DIR}/init_assemblies")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(LINKER_SCRIPT "${LINKER_SCRIPTS}/default.ld")
set(INIT_ASSEMBLY "${INIT_ASSEMBLIES}/default.s")

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "riscv")
set(CMAKE_CROSSCOMPILING 1)

set(TOOLCHAIN_PREFIX "riscv64-unknown-elf")
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PREFIX}-objcopy")
set(CMAKE_OBJDUMP "${TOOLCHAIN_PREFIX}-objdump")

set(COMMON_OPTIONS
    -O4
    -mabi=ilp32
    -march=rv32i
    -mstrict-align
    -mbranch-cost=2
    -mtune=size
    # Verbose logging
#    --verbose
#    -Wl,--verbose
#    -Wl,--print-gc-sections
)

add_compile_options(
    ${COMMON_OPTIONS}
    # Include debug symbols (can be used to add source code annotation to disassembly)
    -g
    # Used to generate dependency files (.d)
    -MD -MP
)

add_link_options(
    ${COMMON_OPTIONS}
    -nostartfiles
    -static
    -T ${LINKER_SCRIPT}
    -D__riscv_ ${INIT_ASSEMBLY}
    -Wl,--defsym=__RAM_SIZE__=${RAM_SIZE}
    -Wl,--defsym=__DISPLAY_POINTER_ADDRESS__=${DISPLAY_POINTER_ADDRESS}
    -Wl,--defsym=__DISPLAY_BUFFERS_START__=${DISPLAY_BUFFERS_START}
    -Wl,--defsym=__DISPLAY_BUFFERS_SIZE__=${DISPLAY_BUFFERS_SIZE}
    -Wl,--defsym=__STACK_SIZE__=${STACK_SIZE}
    -Wl,--defsym=__STACK_TOP__=${STACK_TOP}
    -Wl,--gc-sections
    -Wl,--no-warn-rwx-segment
)

# Function to add a disassembly step to a target
function(add_disassembly target)
    set(disassembly_output_path "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.elf.d")

    add_custom_command(
        COMMENT "Disassembling ${target}"
        DEPENDS ${target}
        OUTPUT ${disassembly_output_path}
        COMMAND ${CMAKE_OBJDUMP} --disassemble --source $<TARGET_FILE:${target}> > ${disassembly_output_path}
    )
    add_custom_target("disassemble_${target}" ALL
        DEPENDS ${disassembly_output_path}
    )
endfunction()

# Function to add a vcbmem generating step to a target
function(add_vcbmem target)
    set(disassembly_output_path "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.elf.d")
    set(elf_binary_path "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.bin")
    set(vcbmem_output_path "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.vcbmem")

    add_custom_command(
        COMMENT "Generating vcbmem for ${target}"
        DEPENDS ${target}
        OUTPUT ${vcbmem_output_path}
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${target}> ${elf_binary_path}
        COMMAND ${CMAKE_OBJCOPY} -I binary -O binary --reverse-bytes=4 ${elf_binary_path} ${vcbmem_output_path}
        COMMAND rm ${elf_binary_path}
    )
    add_custom_target("vcbmem_${target}" ALL
        DEPENDS ${vcbmem_output_path}
    )

    add_custom_target("cpu_${target}"
        COMMENT "Using ${target} program for CPU ${CPU_NAME} vcbmem"
        DEPENDS ${vcbmem_output_path} ${disassembly_output_path}
        COMMAND cp ${vcbmem_output_path} ${CMAKE_SOURCE_DIR}/${CPU_NAME}.vcbmem
    )
endfunction()

include_directories(src)

add_subdirectory(src/display_hello)
add_subdirectory(src/fibonacci)

add_subdirectory(riscof)
