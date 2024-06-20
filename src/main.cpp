#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "particle.h"

void updatePositions(std::vector<Particle>& particles, float timeStep);
void drawParticles(sf::RenderWindow& window, std::vector<Particle>& particles);
void checkParticleCollisions(std::vector<Particle> particles);

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
    const float spawnInterval = 5.0f;
    float accumulator = 0.0f;

    for (int i=0; i < 2; i++) 
    {
        Particle particle(0.f, 0.f, 30.f);
        particles.push_back(particle);
    }

    while (window.isOpen())
    {   
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
        {
            Particle particle(0.f, 0.f, 30.f);
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
    sf::Vector2f gravity = {0.0f, 100.0f};
    
    for (auto& p : particles)
    {
        p.accelerate(gravity);
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

void checkParticleCollisions(std::vector<Particle> particles)
{
    for (auto& p : particles)
    {
        
    }
}

