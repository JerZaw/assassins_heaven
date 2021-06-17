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
    bool activated = false;
    float time_step;
public:
    TimedPlatform(const float &arg_disappear_time,const sf::Texture &arg_texture):
        Platform(arg_texture){
        this->disappear_time = arg_disappear_time;
        time_step = 255/disappear_time;
    }
    TimedPlatform(float arg_disappear_time){
        this->disappear_time = arg_disappear_time;
        time_step = 255/disappear_time;
    }

    void step(const sf::Time &elapsed){
        if(activated){ //zaczyna blednąć według swojego czasu, potem niewidzialne teleportuje się poza okno, wymaga resetu zegara
                this->visibility-=elapsed.asSeconds()*time_step;
                if(visibility>0)
                    this->setColor(sf::Color(255,255,255,this->visibility));
                else{
                    this->ChangeWorkingState(false);
            }
        }
    }

    void activate(){
        this->activated=true;
    }
};

#endif // TIMEDPLATFORM_H
