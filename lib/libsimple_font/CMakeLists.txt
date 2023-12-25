set(TARGET_NAME libsimple_font)

add_library(${TARGET_NAME} OBJECT
    simple_font.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    libsprite
)

target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
