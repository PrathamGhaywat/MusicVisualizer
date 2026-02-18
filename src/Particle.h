#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
    private:
        sf::CircleShape shape;
        sf::Vector2f velocity;
        float lifetime;
        float maxLifetime;
    
    public:
        Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, float lifetime);

        //update particle postion and lifetime
        void update(float deltaTime);

        //draw
        void draw(sf::RenderWindow& window);

        //is particle still alive?
        bool isAlive() const;
};

#endif