#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "particle.h"

void updatePositions(std::vector<Particle>& particles, float timeStep);
void drawParticles(sf::RenderWindow& window, std::vector<Particle>& particles);
void checkParticleCollisions(std::vector<Particle>& particles);

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  

    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulation");
    window.setFramerateLimit(60);

    sf::Font font;
    
    if (!font.loadFromFile("../resources/fonts/Roboto-Medium.ttf"))
    {
        std::cout << "Error loading Font";       
    }

    std::vector<Particle> particles = {};

    sf::Clock clock;
    sf::Clock spawnClock;

    const float timeStep = 1.0f / 60.0f;
    const float spawnInterval = 0.1f;
    float accumulator = 0.0f;

    while (window.isOpen())
    {   
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
        {
            Particle particle(0.f, 0.f, 2.f);
            particles.push_back(particle);
            spawnClock.restart();
        }
                
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
        
        while (accumulator >= timeStep)
        {
            updatePositions(particles, timeStep);
            accumulator -= timeStep;
        }

        accumulator += deltaTime;

        // Render
        window.clear(sf::Color(37,37,37));
        
        drawParticles(window, particles);

        window.display();
    }

    return 0;
}

void updatePositions(std::vector<Particle>& particles, float timeStep)
{
    sf::Vector2f gravity = {0.0f, 00.0f};
    
    for (auto& p : particles)
    {
        p.accelerate(gravity);
    }

    checkParticleCollisions(particles);

    for (auto& p : particles)
    {
        p.update(timeStep);
    }
}

void drawParticles(sf::RenderWindow& window, std::vector<Particle>& particles)
{
    for (auto& p : particles)
    {
        p.draw(window);
    }
} 

void checkParticleCollisions(std::vector<Particle>& particles)
{
    for (int i=0; i < particles.size(); i++)
    {
        for (int j=0; j < particles.size(); j++)
        {
            if (i != j)
            {
                sf::Vector2f position1 = particles[i].getPosition();
                sf::Vector2f position2 = particles[j].getPosition();

                float distance = std::sqrt(std::pow(position1.x - position2.x, 2.0) + std::pow(position1.y - position2.y, 2.0));

                if (distance <= particles[i].getRadius() + particles[j].getRadius())
                {   
                   particles[i].resolveCollision(particles[j], distance);
                }
            }
        }
    }
}

