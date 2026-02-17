#include <SFML/Graphics.hpp>
#include "AudioProcessor.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Music Visualizer");
    window.setFramerateLimit(60);

    //audio processor
    AudioProcessor audioProcessor;

    if (!audioProcessor.loadMusic("C:/Users/Prath/Programming/MusicVisualizer/assets/Timeless.mp3")) {
        std::cerr << "failed to load audio file" << std::endl;
        return -1;
    }

    //starts playing
    audioProcessor.play();

    while (window.isOpen()) {
        while (const auto event = window.waitEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        //get frequency data
        std::vector<float> frequencies = audioProcessor.getFrequencyData();

        if (!frequencies.empty()) {
            std::cout << "1st sample: " << frequencies[0] << std::endl;
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}