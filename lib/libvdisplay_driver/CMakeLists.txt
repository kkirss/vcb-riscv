set(TARGET_NAME libvdisplay_driver)

add_library(${TARGET_NAME} OBJECT
    vdisplay_driver.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    libsprite
)

target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
