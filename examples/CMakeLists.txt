add_executable(playSine playSine.cpp)
target_include_directories(playSine PRIVATE ${PROJECT_SOURCE_DIR}/minsynth)
target_link_libraries(playSine minsynth)