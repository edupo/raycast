cmake_minimum_required(VERSION 3.10)

project(raycaster)
add_subdirectory(ced)

file(GLOB GAME_FILES "*.c")
add_executable(game ${GAME_FILES})
target_link_libraries(game ced)

add_custom_command(TARGET game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:game>)

add_custom_command(TARGET game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/textures/ $<TARGET_FILE_DIR:game>/textures/)