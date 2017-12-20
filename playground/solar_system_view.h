#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "solar_system_model.h"

// Draws the sun.
class SunView {
 public:
    SunView(const Sun& sun, const sf::Texture& texture) : sun_(sun), texture_(texture) {
        sprite_.setTexture(texture_);
    }
    void Draw(sf::RenderWindow* window);
 private:
    // Link to the model.
    const Sun& sun_;
    
    // Texture to use for the model.
    sf::Texture texture_;
    // Sprite to use for the model
    sf::Sprite sprite_;
};

// Top level view class
class SolarSystemView {
 public:
    SolarSystemView(const SolarSystem& system);
    void Draw(sf::RenderWindow* window);
 private:
    const SolarSystem& system_;
    std::unique_ptr<SunView> sun_;
};


