#include "Visualizer.h"
#include <iostream>

Visualizer::Visualizer(int numBars, int windowWidth, int windowHeight) {
    //calculate width of each bar
    float barWidth = windowWidth / static_cast<float>(numBars);

    //create numBars rectangles
    for (int i = 0; i < numBars; i++) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, 0)); //start height 0
        bar.setPosition(sf::Vector2f(static_cast<float>(i) * barWidth, static_cast<float>(windowHeight)));
        bar.setFillColor(sf::Color::Green);
        bars.push_back(bar);
    }
}

void Visualizer::update(const std::vector<float>& frequencies) {
    //loop through every bar
    for (size_t i = 0; i < bars.size() && i < frequencies.size(); i++) {
        //frequency value (0 to 1)
        float freq = frequencies[i];

        //scale to height (* by window height)
        float height = std::min(freq * 5000, 800.0f);  // Amplify and cap at 800

        //set bar height
        bars[i].setSize(sf::Vector2f(bars[i].getSize().x, height));

        //move bar up to make it grow from bottom
        bars[i].setPosition(sf::Vector2f(bars[i].getPosition().x, 800 - height));
        
        // Debug: print first bar info
        if (i == 0) {
            std::cout << "Bar 0: freq=" << freq << " height=" << height 
                      << " pos=(" << bars[i].getPosition().x << "," << bars[i].getPosition().y 
                      << ") size=(" << bars[i].getSize().x << "," << bars[i].getSize().y << ")\n";
        }
    }
}

void Visualizer::draw(sf::RenderWindow& window) {
    std::cout << "Drawing " << bars.size() << " bars\n";
    for (auto& bar : bars) {
        window.draw(bar);
    }
}