#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.h"

class Visualizer {
    private:
        std::vector<sf::RectangleShape> bars; //store bar shapes
        std::vector<float> previousHeights;
        std::vector<Particle> particles;
    
    public:
        Visualizer(int numBars, int windowWidth, int windowHeight);

        //update bars based on frequency data
        void update(const std::vector<float>& frequencies, float deltaTime);

        //draw all bars to window
        void draw(sf::RenderWindow& window);
};

#endif