#include "Particle.h"

//constructor - init particle wit pos, vel, col and lifetime
Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, float lifetime)
    : velocity(velocity), lifetime(lifetime), maxLifetime(lifetime) {
        //create small circle for particle
        shape.setRadius(3.0f); //3px radius
        shape.setPosition(position);
        shape.setFillColor(color);
}

//update called every frame to move the particle and fade it
void Particle::update(float deltaTime) {
    // Increase gravity value
    sf::Vector2f gravity(0.0f, 500.0f);  // Increased from 300
    velocity += gravity * deltaTime;
    
    //move particle
    sf::Vector2f newPos = shape.getPosition() + velocity * deltaTime;
    shape.setPosition(newPos);
    
    //reduce lifetime
    lifetime -= deltaTime;
    
    //fade out
    float alpha = (lifetime / maxLifetime) * 255.0f;
    sf::Color color = shape.getFillColor();
    color.a = static_cast<std::uint8_t>(alpha);
    shape.setFillColor(color);
}

//draw particle
void Particle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

//check particle removed?
bool Particle::isAlive() const {
    return lifetime > 0.0f;
}