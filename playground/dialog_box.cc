#include "dialog_box.h"

#include <iostream>

namespace {
const int kTitleBarHeight = 30;
const int kTextSize = 28;  // Make a parameter?
const int kMarginBetweenOptions = 2;
const int kMarginTextTitle = 5;
const int kOptionsMargin = 100;  // Margin between text and options.
const int kHorizontalMargin = 30; // Horizontal margin between text and dialog box border. Half of this on each side.
}  // namespace

DialogBox::DialogBox(const sf::Font& font, std::string text, std::vector<std::string> options, std::vector<ClickHandler*> handler, int x, int y) : x_(x), y_(y), background_(sf::Vector2<float>(800, 400)),titlebar_(sf::Vector2<float>(800, kTitleBarHeight)),  text_(text, font, kTextSize), dragged_(false), x_offset_dragged_(0), y_offset_dragged_(0), handler_(handler), selection_(-1) {
    
    background_.setFillColor(sf::Color::Yellow);
    background_.setOutlineColor(sf::Color::Black);
    background_.setOutlineThickness(2.0);
    titlebar_.setFillColor(sf::Color::Cyan);
    titlebar_.setOutlineColor(sf::Color::Black);
    titlebar_.setOutlineThickness(2.0);
    
    std::cout << "Height of text: " << text_.getGlobalBounds().height << std::endl;
    float height = kMarginTextTitle + text_.getGlobalBounds().height + kOptionsMargin;
    std::cout << "Height: " << height << std::endl;
    float width = text_.getGlobalBounds().width + kHorizontalMargin;
    text_.setFillColor(sf::Color::Black);
    for (std::string option : options) {
        options_.push_back(sf::Text(option, font, kTextSize));
        options_.back().setFillColor(sf::Color::Black);
        height += (kTextSize + kMarginBetweenOptions);
        std::cout << "Height: " << height << std::endl;
        width = std::max((float)width, options_.back().getGlobalBounds().width + kHorizontalMargin);
    }
    background_.setSize(sf::Vector2<float>(width, height));
    titlebar_.setSize(sf::Vector2<float>(width, kTitleBarHeight));
    
}
void DialogBox::Draw(sf::RenderWindow* window) {
    background_.setPosition(x_, y_);  // TODO: Check if rotations work better with position or origin here (and ordering of transforms!).
    titlebar_.setPosition(x_, y_);
    text_.setPosition(x_ + kHorizontalMargin / 2, y_ + kTitleBarHeight + kMarginTextTitle);
    window->draw(background_);
    window->draw(titlebar_);
    window->draw(text_);
    
    int i = 0;
    for (sf::Text& option : options_) {
        option.setPosition(x_ + kHorizontalMargin / 2, y_ + text_.getGlobalBounds().height + kOptionsMargin + (kTextSize + kMarginBetweenOptions) * i);
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
        if (titlebar_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "And was in draggable area." << std::endl;
            dragged_ = true;
            // Save position of the Mouse relative to the window, so we can drag.
            x_offset_dragged_ = event.mouseButton.x - titlebar_.getPosition().x;
            y_offset_dragged_ = event.mouseButton.y - titlebar_.getPosition().y;
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
