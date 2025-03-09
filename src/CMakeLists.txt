project(Timer_main)

add_subdirectory(music)
add_subdirectory(timer)
add_subdirectory(utils)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
${TIMER_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
timer
)