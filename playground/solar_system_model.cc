#include "solar_system_model.h"

SolarSystem::SolarSystem() {
    sun_.reset(new Sun(250, 250, 50));
    
}
