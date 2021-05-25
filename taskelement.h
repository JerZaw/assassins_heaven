#ifndef TASKELEMENT_H
#define TASKELEMENT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <smallelementcoin.h>

class TaskElement : public SmallElementCoin
{
private:
    enum Tasks{ FIGHT, MIND } task_type;
public:
    TaskElement(){};
    TaskElement(const int &arg_value,const float &arg_speed_x,
                const float &arg_speed_y, const sf::Texture &texture,
                const sf::IntRect &texture_rect) : SmallElementCoin(arg_value,arg_speed_x,texture,texture_rect){
        task_type = Tasks(rand()%2);
    }

    int picked(){/////?????
        return SmallElementCoin::picked();
    }
};

#endif // TASKELEMENT_H
