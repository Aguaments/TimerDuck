project(timer)

add_library(${PROJECT_NAME}
SHARED
timer.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${MUSIC_DIR}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${UTILS_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
music
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
utils
)