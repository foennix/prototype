#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "solar_system_model.h"
#include "solar_system_view.h"

const int kWindowWidth = 1600;
const int kWindowHeight = 1200;

struct ViewPort {
    int scroll_offset_x;
    int scroll_offset_y;
    float zoom_level; // 1.0 is standard size. 0.25 zooms out. 4 zooms in.
};

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Zoomable Starfield.");

    SolarSystem system;
    SolarSystemView solar_system_view(system);
  
    ViewPort port;
    port.scroll_offset_x = 0;
    port.scroll_offset_y = 0;
    port.zoom_level = 1.0;
    sf::View view;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // TODO: Key manager class
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                port.scroll_offset_x += 10;
                std::cout << "Scrolling left" << std::endl;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                port.scroll_offset_x -= 10;
                std::cout << "Scrolling right" << std::endl;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                port.scroll_offset_y += 10;
                std::cout << "Scrolling left" << std::endl;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                port.scroll_offset_y -= 10;
                std::cout << "Scrolling right" << std::endl;
            }
            // TODO: This should be done via an enum or array and a class that keeps track of the current position in the enum.
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) {
                port.zoom_level = 0.25;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) {
                port.zoom_level = 2.0;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Equal) {
                port.zoom_level = 1.0;
            }
            
            // Capture and print mouse events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Mouse clicked: " << event.mouseButton.x << "/" << event.mouseButton.y << std::endl;
            }
            
        }
        
        // Clear screen
        window.clear(sf::Color::Black);
        
        // Apply transformation for scrolling and zooming. The problem with this is that UI will also be scrolled and zoomed :-/. Maybe one can ignore the view when drawing dialog boxes?
        view.setCenter(port.scroll_offset_x, port.scroll_offset_y);
        view.setSize(kWindowWidth / port.zoom_level, kWindowHeight / port.zoom_level);
        std::cout << "View size: " << view.getSize().x << "/" << view.getSize().y << std::endl;
        window.setView(view);
        
        // Draw the solar system.
        solar_system_view.Draw(&window);
        
        
        // Circle below will use default view. This means we can draw UI elements here.
        window.setView(window.getDefaultView());
        
        // Attempt to draw a circle independent of the view
        int circle_x = 0;
        int circle_y = 0;
        int radius = 150;
        sf::CircleShape shape(radius);
        shape.setPosition(circle_x, circle_y);
        shape.setFillColor(sf::Color::White);
        
        window.draw(shape);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}

