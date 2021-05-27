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
    int current_difficulty;

public:
    TaskElement(){};
    TaskElement(const int &arg_value,const float &arg_speed_x, const sf::Texture &texture,
                const sf::IntRect &texture_rect)
        : SmallElementCoin(arg_value,arg_speed_x,texture,texture_rect){
        task_type = Tasks(rand()%2);
    }

    void read_data(const int &arg_difficulty){
        this->current_difficulty = arg_difficulty;
    }

    int fighting_game(const int &arg_difficulty);
    int mind_game(const int &arg_difficulty);

    std::pair<bool,int> picked(sftools::Chronometer *chron, const bool &game_type = 0){
        chron->pause();
        task_type=MIND; //do celów testowania, potem do usunięcia
        if(task_type == FIGHT){
            this->SetValue(fighting_game(current_difficulty));
            std::cerr<<"fighting game\n\n";
        }
        else{
            this->SetValue(mind_game(current_difficulty));
            std::cerr<<"mind game\n\n";
        }
        return SmallElementCoin::picked(chron,task_type);
        chron->reset(true);
    }


};

#endif // TASKELEMENT_H
