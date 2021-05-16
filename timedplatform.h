#ifndef TIMEDPLATFORM_H
#define TIMEDPLATFORM_H

#include <platform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TimedPlatform : public Platform
{
private:
    int disappear_time;
    int visibility = 255;
    sf::Time currenttime = sf::Time::Zero;
public:
    TimedPlatform(int arg_disappear_time){
        this->disappear_time = arg_disappear_time;
    }
    void step(const sf::Time &elapsed){
        this->currenttime+=elapsed;
        if(this->currenttime.asSeconds()>this->disappear_time){ //po danym czasie zaczyna blednąć, potem niewidzialne teleportuje się poza okno, wymaga resetu zegara
            this->visibility-=5;
            if(visibility>0)
                this->setColor(sf::Color(255,255,255,this->visibility));
            else{
                this->setPosition(-1000,-1000);
            }
        }
    }
};

#endif // TIMEDPLATFORM_H
