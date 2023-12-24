set(TARGET_NAME display_hello)

add_executable(${TARGET_NAME}
    main.cpp
    simple_font.cpp
    vdisplay_driver.cpp
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
