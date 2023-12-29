set(TARGET_NAME fibonacci)

add_executable(${TARGET_NAME}
    ${CMAKE_SOURCE_DIR}/init_assemblies/default.s
    main.c
    fibonacci.c
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
