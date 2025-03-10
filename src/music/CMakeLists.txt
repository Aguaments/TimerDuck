project(music)

add_library(${PROJECT_NAME}
SHARED music.cpp
)

target_link_libraries(${PROJECT_NAME}
PUBLIC winmm
)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${UTILS_DIR}
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC utils
)
