#pragma once

#include <memory>

class Sun {
 public:
    Sun(int x, int y, int radius) : x_(x), y_(y), radius_(radius) {}
    // TODO: Move these into a base class.
    int x() const { return x_; }
    int y() const { return y_; }
    int radius() const { return radius_; }
 private:
    int x_;
    int y_;
    int radius_;
    
};

// Top level model class
class SolarSystem {
 public:
    SolarSystem();
    const Sun& sun() const { return *sun_; }
 private:
    std::unique_ptr<Sun> sun_;
};
