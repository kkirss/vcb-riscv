set(TARGET_NAME fibonacci)

add_executable(${TARGET_NAME}
    main.c
    fibonacci.c
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
