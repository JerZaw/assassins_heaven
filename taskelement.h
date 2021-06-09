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
    enum Tasks{ FIGHT=2, MIND=1 } task_type;
    int current_difficulty;
public:
    TaskElement(){};
    TaskElement(const int &arg_value,const float &arg_speed_x, const sf::Texture &texture)
        : SmallElementCoin(arg_value,arg_speed_x,texture){
        task_type = Tasks(rand()%2+1);
    }

    void read_data(const int &arg_difficulty){
        this->current_difficulty = arg_difficulty;
    }

    int fighting_game(const int &arg_difficulty);
    int mind_game(const int &arg_difficulty);

    std::pair<bool,int> picked(sftools::Chronometer *chron, const int &game_type = 0){
            chron->pause();
            //        task_type=FIGHT; //do celów testowania, potem do usunięcia
            if(task_type == FIGHT){
                this->SetValue(fighting_game(current_difficulty));
            }
            else{
                this->SetValue(mind_game(current_difficulty));
            }
        return SmallElementCoin::picked(chron,task_type);
    }


};

#endif // TASKELEMENT_H
