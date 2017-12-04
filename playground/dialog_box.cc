#include "dialog_box.h"

#include <iostream>

DialogBox::DialogBox(const sf::Font& font, std::string text, std::vector<std::string> options, std::vector<ClickHandler*> handler, int x, int y) : x_(x), y_(y), background_(sf::Vector2<float>(800, 400)),draggable_area_(sf::Vector2<float>(800, 30)),  text_(text, font, 28), dragged_(false), x_offset_dragged_(0), y_offset_dragged_(0), handler_(handler), selection_(-1) {
    
    // Does text know its width and height? Then we could use that to construct the shapes.
    
    background_.setFillColor(sf::Color::Yellow);
    background_.setOutlineColor(sf::Color::Black);
    background_.setOutlineThickness(2.0);
    
    
    draggable_area_.setFillColor(sf::Color::Blue);
    
   
    text_.setFillColor(sf::Color::Black);
    for (std::string option : options) {
        options_.push_back(sf::Text(option, font, 28));
        options_.back().setFillColor(sf::Color::Black);
    }
}
void DialogBox::Draw(sf::RenderWindow* window) {
    background_.setPosition(x_, y_);  // TODO: Check if rotations work better with position or origin here (and ordering of transforms!).
    draggable_area_.setPosition(x_, y_);
    text_.setPosition(x_ + 5, y_ + 35);
    window->draw(background_);
    window->draw(draggable_area_);
    window->draw(text_);
    
    int i = 0;
    for (sf::Text& option : options_) {
        option.setPosition(x_ + 5, y_ + 100 + 30 * i);
        if (selection_ == i) {
            option.setFillColor(sf::Color::Red);
        } else {
            option.setFillColor(sf::Color::Black);  // only do when it was selected?
        }
        i++;
        window->draw(option);
    }
    
}
void DialogBox::EvaluateEvent(sf::Event event) {
    // TODO: This needs to take z levels into account for overlapping boxes.
    // TODO: Get a strategy for global/local coordinates etc.
    
    // On Mouse down we enable dragging if in the draggable area. On Mouse movement we drag if dragging is enabled. On Mouse up we disable dragging.
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        std::cout << "Dialog Box captured: Mouse clicked: " << event.mouseButton.x << "/" << event.mouseButton.y << std::endl;
        if (event.mouseButton.x > draggable_area_.getPosition().x && event.mouseButton.x < draggable_area_.getPosition().x + 800 &&
            event.mouseButton.y > draggable_area_.getPosition().y && event.mouseButton.y < draggable_area_.getPosition().y + 30) {
            std::cout << "And was in draggable area." << std::endl;
            dragged_ = true;
            // Save position of the Mouse relative to the window, so we can drag.
            x_offset_dragged_ = event.mouseButton.x - draggable_area_.getPosition().x;
            y_offset_dragged_ = event.mouseButton.y - draggable_area_.getPosition().y;
        }
    }
    
    if (event.type == sf::Event::MouseButtonReleased && dragged_) {
        dragged_ = false;
    }
    
    if (event.type == sf::Event::MouseMoved && dragged_) {
        std::cout << "Moving: " << event.mouseMove.x << "/" << event.mouseMove.y << std::endl;
        // Adjust position of the window.
        x_ = event.mouseMove.x - x_offset_dragged_;
        y_ = event.mouseMove.y - y_offset_dragged_;
    }
    
    // We highlight text that is hovered over by the mouse and keep track of selections.
    if (event.type == sf::Event::MouseMoved) {
        int i = 0;
        selection_ = -1;
        for (sf::Text& option : options_) {
            if (option.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                selection_ = i;
                std::cout << "Setting selection to: " << i << std::endl;
            }
            i++;
        }
    }
    
    // Fire handler when clicks occur over buttons.
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && selection_ >= 0) {
        handler_[selection_]->Fire();
    }
}
