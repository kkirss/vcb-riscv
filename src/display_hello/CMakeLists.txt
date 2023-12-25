set(TARGET_NAME display_hello)

add_executable(${TARGET_NAME}
    main.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    libsimple_font
    libsprite
    libvdisplay_driver
    libvdisplay_sprite
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
