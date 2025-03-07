cmake_minimum_required(VERSION 3.28)
project(Timer)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${PROJECT_SOURCE_DIR}/src/utils/)
include_directories(${PROJECT_SOURCE_DIR}/src/timer)
include_directories(${PROJECT_SOURCE_DIR}/src/bgm)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/timer SRC_TIMER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/utils SRC_UTILS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/bgm SRC_BGM)

add_executable(Timer
        main.cpp
        ${SRC_TIMER}
        ${SRC_UTILS}
        ${SRC_BGM}
)
