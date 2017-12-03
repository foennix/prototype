#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    // Set the Icon
    sf::Image icon;
    //if (!icon.loadFromFile(resourcePath() + "icon.png")) {
    //    return EXIT_FAILURE;
    //}
    //window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load a sprite to display
    sf::Texture texture;
    //if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
    //    return EXIT_FAILURE;
    //}
    sf::Sprite sprite(texture);
    
    // Create a graphical text to display
    //sf::Font font;
    //if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
    //    return EXIT_FAILURE;
    //}
    //sf::Text text("Hello SFML", font, 50);
    //text.setFillColor(sf::Color::Black);
    
    // Load a music to play
    //sf::Music music;
    //if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
    //    return EXIT_FAILURE;
    //}
    
    // Play the music
    //music.play();
    
    sf::CircleShape shape(50);
    
    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));
    
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
        }
        
        // Clear screen
        window.clear(sf::Color::Blue);
        
        // Draw the sprite
        window.draw(sprite);
        
        // draw the shape
        window.draw(shape);
        
        // Draw the string
        //window.draw(text);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
