#include "UIManager.h"
#include <iostream>

UIManager::UIManager() : isInputting(true) {
    // Initialize input box
    inputBox.setSize(sf::Vector2f(600.0f, 50.0f));
    inputBox.setPosition(sf::Vector2f(300.0f, 400.0f));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Green);
    inputBox.setOutlineThickness(2.0f);
}

bool UIManager::loadFont(const std::string& fontPath) {
    // Try to load from assets first
    if (font.openFromFile(fontPath)) {
        setupText();
        return true;
    }
    
    // Fallback: use system font on Windows
    if (font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        setupText();
        return true;
    }
    
    std::cerr << "Failed to load any font!" << std::endl;
    return false;
}

void UIManager::setupText() {
    titleText.setFont(font);
    titleText.setString("Music Visualizer");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(300.0f, 100.0f));
    
    instructionText.setFont(font);
    instructionText.setString("Enter audio file path:");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(sf::Vector2f(300.0f, 350.0f));
}

void UIManager::handleInput(sf::Event event) {
    if (!isInputting) return;
    
    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>()) {
        if (textEvent->unicode == '\b' && !userInput.empty()) {
            // Backspace
            userInput.pop_back();
        } else if (textEvent->unicode == '\r') {
            // Enter key - finish input
            isInputting = false;
        } else if (textEvent->unicode >= 32 && textEvent->unicode < 127) {
            // Regular character
            userInput += static_cast<char>(textEvent->unicode);
        }
    }
}

void UIManager::draw(sf::RenderWindow& window) {
    if (!isInputting) return;
    
    window.draw(titleText);
    window.draw(instructionText);
    window.draw(inputBox);
    
    // Draw input text
    sf::Text inputText(font);  // Initialize with font
    inputText.setString(userInput);
    inputText.setCharacterSize(18);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(sf::Vector2f(310.0f, 410.0f));
    window.draw(inputText);
}

std::string UIManager::getUserInput() const {
    return userInput;
}

bool UIManager::isInputComplete() const {
    return !isInputting && !userInput.empty();
}

void UIManager::reset() {
    userInput.clear();
    isInputting = true;
}