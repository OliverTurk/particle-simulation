#include "particle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Particle::Particle(float initXPos, float initYPos, float radius) 
  : radius(radius), shape(radius), movementFactor(100.f)
{   
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color(255,255,255));
    shape.setPointCount(1000);
    positionCurrent = {initXPos, initYPos};
    positionOld = positionCurrent;
    acceleration = {0.0f, 0.0f};
    shape.setPosition(initXPos, initYPos);
    positionOld = {-1.0f, -1.0f};
}

void Particle::update(float deltaTime)
{   
    sf::Vector2f velocity = positionCurrent - positionOld;

    positionOld = positionCurrent;

    positionCurrent = positionCurrent + velocity + acceleration * deltaTime * deltaTime;
    

    // Boundary Collision
    if (positionCurrent.x - radius < 0)
    {
        positionCurrent.x = radius;
        positionOld.x = positionCurrent.x + velocity.x; 
    }
    else if (positionCurrent.x + radius > 800)
    {
        positionCurrent.x = 800 - radius;
        positionOld.x = positionCurrent.x + velocity.x;
    }

    if (positionCurrent.y - radius < 0)
    {
        positionCurrent.y = radius;
        positionOld.y = positionCurrent.y + velocity.y;
    }
    else if (positionCurrent.y + radius > 600)
    {
        positionCurrent.y = 600 - radius;
        positionOld.y = positionCurrent.y + velocity.y;
    }
    
    std::cout << positionCurrent.y << ", " << positionCurrent.x << "\n";  
    shape.setPosition(positionCurrent);
}

void Particle::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Particle::accelerate(sf::Vector2f acc)
{
   acceleration += acc; 
};

