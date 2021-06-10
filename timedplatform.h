#ifndef TIMEDPLATFORM_H
#define TIMEDPLATFORM_H

#include <platform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TimedPlatform : public virtual Platform
{
private:
    float disappear_time;
    float visibility = 255;
    sf::Time currenttime = sf::Time::Zero;
    bool activated = false;
public:
    TimedPlatform(const float &arg_disappear_time,const sf::Texture &arg_texture):
        Platform(arg_texture){
        this->disappear_time = arg_disappear_time;
    }
    TimedPlatform(float arg_disappear_time){
        this->disappear_time = arg_disappear_time;
    }

    void step(const sf::Time &elapsed){
        if(activated){
            this->currenttime+=elapsed;
            if(this->currenttime.asSeconds()>this->disappear_time){ //po danym czasie zaczyna blednąć, potem niewidzialne teleportuje się poza okno, wymaga resetu zegara
                this->visibility-=0.01;
                if(visibility>0)
                    this->setColor(sf::Color(255,255,255,this->visibility));
                else{
                    this->ChangeWorkingState(false);
                    //this->setPosition(600,1050); //pozycja poza oknem, żeby program wykrył, że platforma skończyła funkcjonalność
                }
            }
        }
    }

    void activate(){
        this->activated=true;
    }
};

#endif // TIMEDPLATFORM_H
