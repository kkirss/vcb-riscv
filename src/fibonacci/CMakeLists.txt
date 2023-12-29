set(TARGET_NAME fibonacci)

add_executable(${TARGET_NAME}
    ${CMAKE_SOURCE_DIR}/init_assemblies/default.s
    main.c
    fibonacci.c
)

set_target_properties(${TARGET_NAME} PROPERTIES
    SUFFIX ".elf"
    LINK_DEPENDS ${LINKER_SCRIPT}
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
