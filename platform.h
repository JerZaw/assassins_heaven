#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Platform : public sf::Sprite
{
public:
    Platform();
    virtual void step(const sf::Time &elapsed){};
};

#endif // PLATFORM_H
