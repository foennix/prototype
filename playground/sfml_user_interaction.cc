#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "dialog_box.h"

class OkHandler : public ClickHandler {
    virtual void Fire() override;
};

void OkHandler::Fire() {
    std::cout << "Ok pressed" << std::endl;
}

class CancelHandler : public ClickHandler {
    virtual void Fire() override;
};

void CancelHandler::Fire() {
    std::cout << "Cancel pressed" << std::endl;
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Simple Dialogbox.");
    
    sf::CircleShape shape(50);
    
    
    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));
    
    sf::Font font;
    if (!font.loadFromFile("playground/Fonts/arial.ttf")) {  // Better have this as top level and depend on it from top level binary.
        return EXIT_FAILURE;
    }
    //sf::Text text("Hello SFML", font, 50);
    //text.setFillColor(sf::Color::Black);
    
    DialogBox box(font, "Test Test Test Test Test \nTest Test Test\nTest", {"Ok", "Cancel"}, {new OkHandler(), new CancelHandler()}, 75, 20);  // Ownership of handlers where?
    
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Capture and print mouse events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Mouse clicked: " << event.mouseButton.x << "/" << event.mouseButton.y << std::endl;
            }
            
            box.EvaluateEvent(event);
        }
        
        // Clear screen
        window.clear(sf::Color::White);
        
        // draw the shape
        window.draw(shape);
        
        // Draw the dialog box
        box.Draw(&window);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
