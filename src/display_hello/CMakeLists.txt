set(TARGET_NAME display_hello)

add_executable(${TARGET_NAME}
    ${CMAKE_SOURCE_DIR}/init_assemblies/default.s
    main.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    libsimple_font
    libsprite
    libvdisplay_driver
    libvdisplay_sprite
)

set_target_properties(${TARGET_NAME} PROPERTIES
    LINK_DEPENDS ${LINKER_SCRIPT}
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
