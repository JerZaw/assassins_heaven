#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include <platform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MovingPlatform : public Platform
{
private:
    int speed;
    int moving_boundary;
public:

    MovingPlatform(int arg_speed, int arg_moving_boundary){
        this->speed = arg_speed;
        this->moving_boundary = arg_moving_boundary;
    }
    void step(const sf::Time &elapsed){ //przesuwa platformę w jedną stronę aż dotknie granicy, potem w drugą stronę itd, wymaga resetu zegara
        this->move(speed*elapsed.asSeconds(),0);
        if(this->getGlobalBounds().left+this->getGlobalBounds().width > moving_boundary
                || this->getGlobalBounds().left < -1*moving_boundary){
            speed*=-1;
        }
    }

};

#endif // MOVINGPLATFORM_H
