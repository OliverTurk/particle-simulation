#include "particle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Particle::Particle(float initXPos, float initYPos, float radius) 
  : radius(radius), shape(radius), movementFactor(100.f)
{   
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color(255,255,255));
    shape.setPointCount(10000);
    positionCurrent = {initXPos, initYPos};
    positionOld = positionCurrent;
    acceleration = {0.0f, 0.0f};
    shape.setPosition(initXPos, initYPos);
    positionOld = {-10.0f, -10.0f};
}

void Particle::update(float deltaTime)
{    
    velocity = positionCurrent - positionOld;

    positionOld = positionCurrent;

    positionCurrent = positionCurrent + velocity + acceleration * deltaTime * deltaTime;
    
    checkBoundaryCollision();

    std::cout << positionCurrent.y << ", " << positionCurrent.x << "\n";  
    shape.setPosition(positionCurrent);
}

void Particle::checkBoundaryCollision() 
{
    const float friction = 0.997f;
    
    if (positionCurrent.x - radius < 0)
    {
        positionCurrent.x = radius;
        positionOld.x = (positionCurrent.x + velocity.x) * friction; 
    }
    else if (positionCurrent.x + radius > 800)
    {
        positionCurrent.x = 800 - radius;
        positionOld.x = (positionCurrent.x + velocity.x) * friction;
    }

    if (positionCurrent.y - radius < 0)
    {
        positionCurrent.y = radius;
        positionOld.y = (positionCurrent.y + velocity.y) * friction;
    }
    else if (positionCurrent.y + radius > 600)
    {   
        positionCurrent.y = 600 - radius;
        positionOld.y = (positionCurrent.y + velocity.y) * friction;
    }
}

void Particle::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Particle::accelerate(sf::Vector2f acc)
{
    acceleration += acc; 
}

void Particle::resolveCollision(Particle& other, float distance)
{   
    sf::Vector2f delta = positionCurrent - other.getPosition();
    float overlap = 0.5f * (distance - radius - other.getRadius());

    positionCurrent -= delta * (overlap / distance);
    
    sf::Vector2f tempPosition = other.getPosition();
    tempPosition += delta * (overlap / distance);
    other.updatePosition(tempPosition);
}

sf::Vector2f Particle::getPosition()
{
    return positionCurrent;
}

void Particle::updatePosition(sf::Vector2f newPosition)
{
    positionCurrent = newPosition;
}

float Particle::getRadius()
{
  return radius;
}
