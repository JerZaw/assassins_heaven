#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Platform : public sf::Sprite
{
private:
    bool working = true;
public:
    Platform(){};
    virtual void step(const sf::Time &elapsed){};
    virtual void activate(){};
    virtual void SetMiddle(){};

    void ChangeWorkingState(const bool &czy){
        this->working = czy;
        if(!czy){

        }
    }

    bool Is_working(){
        return this->working;
    }
};

#endif // PLATFORM_H
