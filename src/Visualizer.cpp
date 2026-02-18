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
        
        previousHeights.push_back(0.0f);  //initialize all to 0
    }
}

void Visualizer::update(const std::vector<float>& frequencies, float deltaTime) {
    for (size_t i = 0; i < bars.size() && i < frequencies.size(); i++) {
        float targetHeight = std::min(frequencies[i] * 5000, 800.0f);
        
        float currentHeight = previousHeights[i];
        float newHeight = currentHeight + (targetHeight - currentHeight) * 0.2f;  //0.2 = smoothing factor
        
        previousHeights[i] = newHeight;
        
        bars[i].setSize(sf::Vector2f(bars[i].getSize().x, newHeight));
        bars[i].setPosition(sf::Vector2f(bars[i].getPosition().x, 800 - newHeight));
        
        float hueValue = newHeight / 800.0f;  //0 to 1
        sf::Color barColor;
        if (hueValue < 0.5f) {
            barColor = sf::Color::Blue;  
        } else if (hueValue < 0.75f) {
            barColor = sf::Color::Green; 
        } else {
            barColor = sf::Color::Red;  
        }
        bars[i].setFillColor(barColor);

         //emit particles frome bar if moving
        if (newHeight > 10.0f) {
            for (int p = 0; p < 2; p++) {
                sf::Vector2f barCenter(bars[i].getPosition().x + bars[i].getSize().x / 2.0f,
                                                    bars[i].getPosition().y);
                sf::Vector2f particleVelocity(0.0f, -200.0f); //move upward
                particles.emplace_back(barCenter, particleVelocity, barColor, 2.0f);  
            }
        }

        
    }   
}

void Visualizer::draw(sf::RenderWindow& window) {
    for (auto& bar : bars) {
        window.draw(bar);
    }
    
    // Draw particles
    for (auto& particle : particles) {
        particle.draw(window);
    }
}