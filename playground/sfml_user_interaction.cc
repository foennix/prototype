#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Dialogbox.");
    
    sf::CircleShape shape(50);
    
    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));
    
    sf::Font font;
    if (!font.loadFromFile("playground/Fonts/arial.ttf")) {  // Better have this as top level and depend on it from top level binary.
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);
    
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
        }
        
        // Clear screen
        window.clear(sf::Color::White);
        
        // draw the shape
        window.draw(shape);
        
        // Draw the string
        window.draw(text);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
