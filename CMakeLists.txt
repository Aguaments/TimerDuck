cmake_minimum_required(VERSION 4.0)
project(Timer
    VERSION 1.0.0
    DESCRIPTION "A timer"
    HOMEPAGE_URL "https://github.com/Aguaments/TimerDuck"
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(MUSIC_DIR ${PROJECT_SOURCE_DIR}/src/music)
set(TIMER_DIR ${PROJECT_SOURCE_DIR}/src/timer)
set(UTILS_DIR ${PROJECT_SOURCE_DIR}/src/utils)


add_subdirectory(${PROJECT_SOURCE_DIR}/src)