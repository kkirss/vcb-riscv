add_executable(fibonacci
    main.c
    fibonacci.c
)

target_include_directories(fibonacci PRIVATE ${CMAKE_SOURCE_DIR}/src/fibonacci)

add_disassembly(fibonacci)
add_vcbmem(fibonacci)
