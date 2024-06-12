#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "particle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulation");
    window.setFramerateLimit(60);

    sf::Font font;
    
    if (!font.loadFromFile("../resources/fonts/Roboto-Medium.ttf"))
    {
        std::cout << "Error loading Font";       
    }

    sf::Clock clock;
    const float timeStep = 1.0f / 60.0f;
    float accumulator = 0.0f;

    Particle particle(0.f, 0.f, 50.f);

    sf::Vector2f gravity = {0.0f, 10.f};

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        particle.update(deltaTime);
        
        particle.accelerate(gravity);

        accumulator += deltaTime;

        while (accumulator >= timeStep)
        {
            particle.accelerate(gravity * timeStep);
            particle.update(timeStep);
            accumulator -= timeStep;
        }

        // Render
        window.clear(sf::Color(37,37,37));
        
        particle.draw(window);

        window.display();
    }

    return 0;
}

