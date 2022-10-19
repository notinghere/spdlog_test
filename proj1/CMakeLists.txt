cmake_minimum_required(VERSION 3.16)

project(proj1)

include_directories(./src)

aux_source_directory(./src SRC_MAIN)
#add_executable (${PROJECT_NAME} ${SRC_MAIN})
add_library(${PROJECT_NAME} SHARED ${SRC_MAIN})

#find_package(Threads REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

