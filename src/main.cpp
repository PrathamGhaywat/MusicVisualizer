#include <SFML/Graphics.hpp>
#include "AudioProcessor.h"
#include "Visualizer.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Music Visualizer");
    window.setFramerateLimit(60);

    //audio processor
    AudioProcessor audioProcessor;

    //create visualizer with 64 bars
    Visualizer visualizer(64, 1200, 800);

    std::cout << "Visualizer created with 64 bars\n";

    if (!audioProcessor.loadMusic("C:/Users/Prath/Programming/MusicVisualizer/assets/Timeless.mp3")) {
        std::cerr << "failed to load audio file" << std::endl;
        return -1;
    } else {
        std::cout << "Audio loaded successfully!\n";
    }

    //starts playing
    audioProcessor.play();

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        //get frequency data
        std::vector<float> frequencies = audioProcessor.getFrequencyData();

        //update visualizer with frequnecy data
        visualizer.update(frequencies, deltaTime);

        std::cout << "Frequencies size: " << frequencies.size();
        if (!frequencies.empty()) {
            std::cout << " | First freq: " << frequencies[0] << std::endl;
        } else {
            std::cout << " | EMPTY!\n";
        }

        window.clear(sf::Color::Black);
        visualizer.draw(window);
        window.display();
    }

    return 0;
}