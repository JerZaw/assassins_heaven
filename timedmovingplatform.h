#ifndef TIMEDMOVINGPLATFORM_H
#define TIMEDMOVINGPLATFORM_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <movingplatform.h>
#include <timedplatform.h>

class TimedMovingPlatform : public MovingPlatform, public TimedPlatform
{
public:
    TimedMovingPlatform(int arg_speed, int arg_moving_boundary, int arg_disappear_time) :
        MovingPlatform(arg_speed, arg_moving_boundary),TimedPlatform(arg_disappear_time){
    }
    void step(const sf::Time &elapsed){ //łączy funkcjonalności step z wyższych klas
        this->MovingPlatform::step(elapsed);
        this->TimedPlatform::step(elapsed);
    }

};

#endif // TIMEDMOVINGPLATFORM_H
