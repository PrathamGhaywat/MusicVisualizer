#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Music Visualizer");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const auto event = window.waitEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}