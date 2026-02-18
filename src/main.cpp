#include <SFML/Graphics.hpp>
#include "AudioProcessor.h"
#include "Visualizer.h"
#include "UIManager.h"
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Music Visualizer");
    window.setFramerateLimit(60);

    AudioProcessor audioProcessor;
    Visualizer visualizer(64, 1200, 800);
    UIManager uiManager;

    std::vector<std::string> fontPaths = {
        "assets/Roboto-Regular.ttf",
        "../assets/Roboto-Regular.ttf",
        "../../assets/Roboto-Regular.ttf"
    };

    bool fontLoaded = false;
    for (const auto& path : fontPaths) {
        if (uiManager.loadFont(path)) {
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    if (!uiManager.loadFont("assets/Roboto-Regular.ttf")) {
        return -1;
    }

    std::cout << "Visualizer created with 64 bars\n";

    // Wait for user to enter file path via UI
    bool fileLoaded = false;
    while (window.isOpen() && !fileLoaded) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            uiManager.handleInput(*event);
        }

        if (uiManager.isInputComplete()) {
            std::string filepath = uiManager.getUserInput();
            
            if (audioProcessor.loadMusic(filepath)) {
                std::cout << "Audio loaded successfully!\n";
                audioProcessor.play();
                fileLoaded = true;
            } else {
                std::cerr << "Failed to load audio file!" << std::endl;
                uiManager.reset();
            }
        }

        window.clear(sf::Color::Black);
        uiManager.draw(window);
        window.display();
    }

    sf::Clock clock;

    // Main game loop
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