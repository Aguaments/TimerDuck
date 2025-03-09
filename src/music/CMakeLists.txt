project(music)

add_library(${PROJECT_NAME}
SHARED
music.cpp
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
winmm
)