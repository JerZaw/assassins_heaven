#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class AnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> rec_vec,pom_rec_vec;
    int current=0;
    int my_fps;
    float verticalspeed;
    float horizontalspeed;
    float acceleration;
    sf::Time dlugi_czas = sf::Time::Zero;
    int pressed = 0;
    enum { CHANGED_LEFT, CHANGED_RIGHT } side_state = CHANGED_RIGHT;
    bool jumping = false;
public:

    AnimatedSprite(const int &fps=1, const float &ver_speed=100,const float &hor_speed = 250, const float &acceler = 800){
        this->my_fps = fps;
        this->verticalspeed = ver_speed;
        this->horizontalspeed = hor_speed;
        this->acceleration = acceler;
    };

    void SetHorizontalSpeed(float arg_horizontalspeed){
        this->horizontalspeed=arg_horizontalspeed;
    }

    float GetHorizontalSpeed(){
        return this->horizontalspeed;
    }

    void add_animation_frame(const sf::IntRect &rect){
        rec_vec.emplace_back(rect);
    }

    void start_jump_animation(){
        current = 0;
        dlugi_czas = sf::Time::Zero;
        std::swap(rec_vec,pom_rec_vec);
        jumping = true;
    }

    void add_pom_animation_frame(const sf::IntRect &rect){
        pom_rec_vec.emplace_back(rect);
    }

    void accelerate(float added_acceleration){
        acceleration+=added_acceleration;
    }

    virtual void vertical_step(const sf::Time &elapsed, const sf::Window &okno){
        this->move(0,this->verticalspeed*elapsed.asSeconds());
        if(this->verticalspeed<100000){
            this->verticalspeed+=this->acceleration*elapsed.asSeconds();
        }
    }

    void step(const sf::Time &elapsed, const sf::Window &okno){ //wymaga restartu zegara, odpowiada za poruszanie we wszystkie strony oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){//zmiana klatek
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==int(rec_vec.size())-1){
                this->current=0;
                if(jumping){
                    jumping = false;
                    std::swap(rec_vec,pom_rec_vec);
                }
            }
            this->dlugi_czas = sf::Time::Zero;
        }

        vertical_step(elapsed,okno);

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

    float GetAcceleration(){
        return this->acceleration;
    }

    void check_hero_move(const sf::Window &okno){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            this->pressed = 1;
            if (this->getGlobalBounds().left+this->getGlobalBounds().width > okno.getSize().x){
                this->move(-(this->getGlobalBounds().left + this->getGlobalBounds().width - okno.getSize().x),0);
            }
            if(side_state==CHANGED_LEFT){
                this->setScale(0.2,0.2);
                this->move(-this->getGlobalBounds().width,0);
                side_state = CHANGED_RIGHT;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->pressed = 2;
            if (this->getGlobalBounds().left < 0){
                this->move(-this->getGlobalBounds().left,0);
            }
            if(side_state==CHANGED_RIGHT){
                this->setScale(-0.2,0.2);
                this->move(this->getGlobalBounds().width,0);
                side_state = CHANGED_LEFT;
            }
        }
        else this->pressed = 0;
    }
};

#endif // ANIMATEDSPRITE_H
