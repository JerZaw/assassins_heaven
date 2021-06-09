#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include <platform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MovingPlatform : public virtual Platform
{
private:
    int speed;
    int moving_boundary;
    float x_srodka=600;
public:

    MovingPlatform(int arg_speed, int arg_moving_boundary,const sf::Texture &arg_texture):
        Platform(arg_texture){
        this->speed = arg_speed;
        this->moving_boundary = arg_moving_boundary;
    }

    void step(const sf::Time &elapsed){ //przesuwa platformę w jedną stronę aż dotknie granicy, potem w drugą stronę itd, wymaga resetu zegara
        this->move(speed*elapsed.asSeconds(),0);
        if(this->GetCoin()!=nullptr)this->GetCoin()->move(speed*elapsed.asSeconds(),0);
        if(this->getPosition().x+this->getGlobalBounds().width > x_srodka+moving_boundary){
            this->speed=-abs(this->speed);
        }
        else if(this->getPosition().x < x_srodka-moving_boundary){
            this->speed=abs(this->speed);
        }
    }

    void SetMiddle(){ //podczas ustawiania pozycji liczy środek X platformy, by potem w step przesuwać aż bok się zetknie z Xsr+-granica
        this->x_srodka = (this->getPosition().x+this->getPosition().x+this->getGlobalBounds().width)/2;
        if(this->getGlobalBounds().width > 2*moving_boundary){ //granica musi mieścić w środku platformę, inaczej się nie rusza
            std::cerr<<"uwaga ustawiam speed=0, za mala granica ruchu co do wielkosci platformy\n";
            this->speed=0;
        }
    }

};

#endif // MOVINGPLATFORM_H
