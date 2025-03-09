cmake_minimum_required(VERSION 4.0)
project(Timer)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_EXE_LINKER_FLAGS "-static")

aux_source_directory(${CMAKE_SOURCE_DIR}/src/music SRC_MUSIC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/timer SRC_TIMER)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/utils SRC_UTILS)

add_library(common
SHARED
${SRC_MUSIC}
${SRC_TIMER}
${SRC_UTILS}
)

target_include_directories(common
PUBLIC
${CMAKE_SOURCE_DIR}/include/music
${CMAKE_SOURCE_DIR}/include/timer
${CMAKE_SOURCE_DIR}/include/utils
)


add_executable(Timer
        main.cpp
)

target_link_libraries(Timer
PUBLIC
common
)
