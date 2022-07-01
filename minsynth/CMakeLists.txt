add_library(minsynth STATIC IAudioDevice.h AudioDevice.h AudioDevice.cpp)
target_include_directories(minsynth PRIVATE ${PROJECT_SOURCE_DIR}/portaudio/include)
target_link_libraries(minsynth PortAudio)

