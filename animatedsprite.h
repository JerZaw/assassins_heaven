#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class AnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> rec_vec;
    int current=0;
    int my_fps;
    float verticalspeed=100;
    float horizontalspeed=250;
    float acceleration=800;
    sf::Time dlugi_czas = sf::Time::Zero;
    int pressed = 0;
public:
    AnimatedSprite(const int &fps=1){
        this->my_fps = fps;
    };

    void add_animation_frame(const sf::IntRect &rect){
        rec_vec.emplace_back(rect);
    }

    void step(const sf::Time &elapsed){ //restartuje zegar samo w sobie, odpowiada za poruszanie we wszystkie strony oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==int(rec_vec.size())-1){
                this->current=0;
            }
            this->dlugi_czas = sf::Time::Zero;
        }
        if(this->verticalspeed<10000){
            this->verticalspeed+=this->acceleration*elapsed.asSeconds();}

        this->move(0,this->verticalspeed*elapsed.asSeconds());

        if(this->pressed==1){
            this->move(elapsed.asSeconds()*this->horizontalspeed,0);
        }
        else if(this->pressed==2){
            this->move(-elapsed.asSeconds()*this->horizontalspeed,0);
        }
    }

    void SetVerticalSpeed(float arg_verticalspeed){
        this->verticalspeed=arg_verticalspeed;
    }

    float GetVerticalSpeed(){
        return this->verticalspeed;
    }

    void SetPress(int change_to){
        this->pressed=change_to;
    }
};

#endif // ANIMATEDSPRITE_H
