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
    float verticalspeed;
    float horizontalspeed;
    float acceleration;
    sf::Time dlugi_czas = sf::Time::Zero;
    int pressed = 0;
public:

    AnimatedSprite(const int &fps=1, const float &ver_speed=100,const float &hor_speed = 250, const float &acceler = 800){
        this->my_fps = fps;
        this->verticalspeed = ver_speed;
        this->horizontalspeed = hor_speed;
        this->acceleration = acceler;
    };

    void add_animation_frame(const sf::IntRect &rect){
        rec_vec.emplace_back(rect);
    }

    void accelerate(float added_acceleration){
        acceleration+=added_acceleration;
    }

    void step(const sf::Time &elapsed, const sf::Window &okno){ //wymaga restartu zegara, odpowiada za poruszanie we wszystkie strony oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){//zmiana klatek
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==int(rec_vec.size())-1){
                this->current=0;
            }
            this->dlugi_czas = sf::Time::Zero;
        }

        if(this->getGlobalBounds().top + this->getGlobalBounds().height < okno.getSize().y){
            this->move(0,this->verticalspeed*elapsed.asSeconds());
            if(this->verticalspeed<10000){
                this->verticalspeed+=this->acceleration*elapsed.asSeconds();
            }
        }

        if(this->pressed==1){//ruch prawo lewo
            this->move(elapsed.asSeconds()*this->horizontalspeed,0);
        }
        else if(this->pressed==2){
            this->move(-elapsed.asSeconds()*this->horizontalspeed,0);
        }

        this->check_hero_move(okno);//sprawdzanie ruchu prawo lewo
    }

    void SetVerticalSpeed(float arg_verticalspeed){
        this->verticalspeed=arg_verticalspeed;
    }

    float GetVerticalSpeed(){
        return this->verticalspeed;
    }

    void check_hero_move(const sf::Window &okno){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            this->pressed = 1;
            if (this->getGlobalBounds().left+this->getGlobalBounds().width > okno.getSize().x){
                this->move(-(this->getGlobalBounds().left + this->getGlobalBounds().width - okno.getSize().x),0);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->pressed = 2;
            if (this->getGlobalBounds().left < 0){
                this->move(-this->getGlobalBounds().left,0);
            }
        }
        else this->pressed = 0;
    }
};

#endif // ANIMATEDSPRITE_H
