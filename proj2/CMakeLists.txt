cmake_minimum_required(VERSION 3.16)

project(proj2)

include_directories(./src)
include_directories(../proj1/src)

aux_source_directory(./src SRC_MAIN)
add_executable (${PROJECT_NAME} ${SRC_MAIN})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

link_directories(${PROJECT_ROOT}/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC proj1)
