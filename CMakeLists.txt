cmake_minimum_required(VERSION 3.10)

project(raycaster)

find_package(SDL2)
file(GLOB C_FILES "*.c")
add_executable(game ${C_FILES})
target_link_libraries(game -lsdl2)
