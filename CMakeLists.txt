cmake_minimum_required(VERSION 3.10)

project(raycaster)

find_package(SDL2)
file(GLOB C_FILES "*.c")
add_executable(game ${C_FILES})
target_link_libraries(game -lsdl2 -lsdl2_image)

add_custom_command(TARGET game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:game>)