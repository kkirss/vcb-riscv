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
    libvinput
)

set_target_properties(${TARGET_NAME} PROPERTIES
    SUFFIX ".elf"
    LINK_DEPENDS ${LINKER_SCRIPT}
)

add_disassembly(${TARGET_NAME})
add_vcbmem(${TARGET_NAME})
add_cpu_config(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/vcb_config.json)
