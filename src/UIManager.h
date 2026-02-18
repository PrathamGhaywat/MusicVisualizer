#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

class UIManager {
private:
    sf::Font font;
    sf::Text titleText = sf::Text(font);
    sf::Text instructionText = sf::Text(font);
    sf::RectangleShape inputBox;
    std::string userInput;
    bool isInputting;
    
public:
    UIManager();
    
    bool loadFont(const std::string& fontPath);
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);
    std::string getUserInput() const;
    bool isInputComplete() const;
    void reset();
};

#endif