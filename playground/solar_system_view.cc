#include "solar_system_view.h"

#include <SFML/Graphics.hpp>
#include "solar_system_model.h"

SolarSystemView::SolarSystemView(const SolarSystem& system) : system_(system) {
    // Texture for the sun.
    sf::Texture texture;
    if (!texture.loadFromFile("playground/Img/sun.png"))
    {
        // error...
    }
    
    // Create members from the model.
    sun_.reset(new SunView(system_.sun(), texture));
}

void SolarSystemView::Draw(sf::RenderWindow* window) {
    sun_->Draw(window);
}

void SunView::Draw(sf::RenderWindow* window) {
    //sf::CircleShape shape(sun_.radius());
    sprite_.setPosition(sun_.x(), sun_.y());
    window->draw(sprite_);
}
