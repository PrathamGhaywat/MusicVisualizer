cmake_minimum_required(VERSION 3.22)

project(MusicVisualizer)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/Prath/SFML-3.0.2/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Audio REQUIRED)

add_executable(MusicVisualizer 
    src/main.cpp 
    src/Visualizer.cpp
    src/AudioProcessor.cpp
    src/Particle.cpp)

target_link_libraries(MusicVisualizer PRIVATE SFML::Graphics SFML::Audio)

link_directories("C:/Users/Prath/SFML-3.0.2/lib")