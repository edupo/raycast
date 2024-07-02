cmake_minimum_required(VERSION 3.10)
project(ced)

find_package(SDL2)
file(GLOB CED_SOURCE_FILES "*.c")
file(GLOB CED_INCLUDE_FILES "*.h")

add_library(
    ced OBJECT 
    ${CED_SOURCE_FILES}
    ${CED_INCLUDE_FILES}
    )
target_include_directories(
    ced
    PUBLIC 
    ${PROJECT_SOURCE_DIR})

target_link_libraries(ced PUBLIC -lsdl2 -lsdl2_image)
