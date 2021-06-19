#ifndef TASKELEMENT_H
#define TASKELEMENT_H

#include <read_textures.h>
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
    sf::IntRect my_long_platform_texture_rect;
public:
    TaskElement(){};
    TaskElement(const int &arg_value,const float &arg_speed_x, const sf::Texture &texture,
                const sf::IntRect &current_long_platform_rect)
        : SmallElementCoin(arg_value,arg_speed_x,texture),my_long_platform_texture_rect(current_long_platform_rect){

        task_type = Tasks(rand()%2+1);
    }

    void read_data(const int &arg_difficulty){
        this->current_difficulty = arg_difficulty;
    }

    int fighting_game(const int &arg_difficulty);
    int mind_game(const int &arg_difficulty, const sf::IntRect &current_long_platform_rect);

    void play_my_sound(){
        task_coin_sound.play();
    }

    std::pair<bool,int> picked(sftools::Chronometer *chron, const int &game_type = 0){
        chron->pause();
        jumping_game_music.stop();
        if(task_type == FIGHT){
            fighting_music.play();
            this->SetValue(fighting_game(current_difficulty));
            fighting_music.stop();
        }
        else{
            mind_music.play();
            this->SetValue(mind_game(current_difficulty, my_long_platform_texture_rect));
            mind_music.stop();
        }
        jumping_game_music.play();

        return SmallElementCoin::picked(chron,task_type);
    }


};

#endif // TASKELEMENT_H
