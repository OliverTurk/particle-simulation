#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle
{
  public:
    Particle(float initXPos, float initYPos, float radius);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void accelerate(sf::Vector2f acceleration);

  private:
    float radius;
    float movementFactor;
    sf::CircleShape shape;
    sf::Vector2f positionCurrent;
    sf::Vector2f positionOld;
    sf::Vector2f acceleration;
};

#endif
