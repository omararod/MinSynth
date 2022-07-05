add_executable(playSine playSine.cpp)
target_include_directories(playSine PRIVATE ${PROJECT_SOURCE_DIR}/minsynth)
target_link_libraries(playSine minsynth)

add_executable(windowedExample WIN32 windowedExample.cpp)
target_link_libraries(windowedExample minsynth)
target_include_directories(windowedExample PRIVATE ${PROJECT_SOURCE_DIR}/minsynth)
