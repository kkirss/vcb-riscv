set(TARGET_NAME libvdisplay_sprite)

add_library(${TARGET_NAME} INTERFACE)

target_link_libraries(${TARGET_NAME} INTERFACE
    libsprite
    libvdisplay_driver
)

target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
