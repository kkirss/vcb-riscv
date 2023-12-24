add_executable(display_hello
    main.cpp
    simple_font.cpp
    vdisplay_driver.cpp
)

target_include_directories(display_hello PRIVATE ${CMAKE_SOURCE_DIR}/src/display_hello)

add_disassembly(display_hello)
add_vcbmem(display_hello)
