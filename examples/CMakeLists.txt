add_executable(playSine playSine.cpp)
target_include_directories(playSine PRIVATE ${PROJECT_SOURCE_DIR}/minsynth)
target_link_libraries(playSine minsynth)

add_executable(windowedExample WIN32 windowedExample.cpp)
target_link_libraries(windowedExample minsynth)
target_include_directories(windowedExample PRIVATE ${PROJECT_SOURCE_DIR}/minsynth)

set(KINECT_PATH "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409")
add_executable(theremin WIN32 theremin.cpp BodyApp.cpp BodyApp.h)
target_link_libraries(theremin minsynth d2d1.lib ${KINECT_PATH}/Lib/x64/Kinect20.lib)
target_include_directories(theremin PRIVATE ${KINECT_PATH}/inc/ ${PROJECT_SOURCE_DIR}/minsynth)
