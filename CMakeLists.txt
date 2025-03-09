cmake_minimum_required(VERSION 3.28)
project(Timer)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${PROJECT_SOURCE_DIR}/include/utils)
include_directories(${PROJECT_SOURCE_DIR}/include/timer)
include_directories(${PROJECT_SOURCE_DIR}/include/music)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/timer SRC_TIMER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/utils SRC_UTILS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/music SRC_MUSIC)

add_executable(Timer
        main.cpp
        ${SRC_TIMER}
        ${SRC_UTILS}
        ${SRC_MUSIC}
)
