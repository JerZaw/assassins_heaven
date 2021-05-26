#ifndef TASKELEMENT_H
#define TASKELEMENT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <smallelementcoin.h>
#include <Chronometer.hpp>

class TaskElement : public SmallElementCoin
{
private:
    enum Tasks{ FIGHT, MIND } task_type;

public:
    TaskElement(){};
    TaskElement(const int &arg_value,const float &arg_speed_x, const sf::Texture &texture,
                const sf::IntRect &texture_rect)
        : SmallElementCoin(arg_value,arg_speed_x,texture,texture_rect){
        task_type = Tasks(rand()%2);
    }

    int fighting_game();
    int mind_game();

    std::pair<bool,int> picked(sftools::Chronometer *chron, const bool &game_type = 0){
        chron->pause();
        task_type=MIND; //do celów testowania, potem do usunięcia
        if(task_type == FIGHT){
            this->SetValue(fighting_game());
        }
        else{
            this->SetValue(mind_game());
        }
        return SmallElementCoin::picked(chron,task_type);
        chron->reset(true);
    }


};

#endif // TASKELEMENT_H
