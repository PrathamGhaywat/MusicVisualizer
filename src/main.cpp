#include <SFML/Graphics.hpp>
#include "AudioProcessor.h"
#include "Visualizer.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Music Visualizer");
    window.setFramerateLimit(60);

    AudioProcessor audioProcessor;
    Visualizer visualizer(64, 1200, 800);

    std::cout << "Visualizer created with 64 bars\n";
    
    std::string filepath;
    std::cout << "Enter audio file path: ";
    std::getline(std::cin, filepath);
    
    if (!audioProcessor.loadMusic(filepath)) {
        std::cerr << "Failed to load audio file!" << std::endl;
        return -1;
    }
    
    std::cout << "Audio loaded successfully!\n";
    audioProcessor.play();

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        std::vector<float> frequencies = audioProcessor.getFrequencyData();
        visualizer.update(frequencies, deltaTime);

        window.clear(sf::Color::Black);
        visualizer.draw(window);
        window.display();
    }

    return 0;
}