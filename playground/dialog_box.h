// A simple configurable multiple choice dialog box for use in SFML.

#include <SFML/Graphics.hpp>
#include "click_handler.h"

class DialogBox {
 public:
    DialogBox(const sf::Font& font, std::string text, std::vector<std::string> options, std::vector<ClickHandler*> handler, int x, int y);
    void Draw(sf::RenderWindow* window);
    void EvaluateEvent(sf::Event event);
 private:
    int x_;
    int y_;
    
    sf::RectangleShape background_;
    sf::RectangleShape draggable_area_;
    sf::Text text_;
    std::vector<sf::Text> options_;
    
    bool dragged_;
    int x_offset_dragged_;
    int y_offset_dragged_;
    
    std::vector<ClickHandler*> handler_;
    int selection_;
};
