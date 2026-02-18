cmake_minimum_required(VERSION 3.22)

project(MusicVisualizer)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics Audio REQUIRED)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Debug/)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Release/)

add_executable(MusicVisualizer 
    src/main.cpp 
    src/Visualizer.cpp
    src/AudioProcessor.cpp
    src/Particle.cpp
    src/UIManager.cpp)

target_link_libraries(MusicVisualizer PRIVATE SFML::Graphics SFML::Audio)

link_directories("C:/Users/Prath/SFML-3.0.2/lib")