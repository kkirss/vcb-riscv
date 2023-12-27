set(TARGET_NAME libvdisplay_driver)

add_library(${TARGET_NAME} INTERFACE)

target_link_libraries(${TARGET_NAME} INTERFACE
    libsprite
)

target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
