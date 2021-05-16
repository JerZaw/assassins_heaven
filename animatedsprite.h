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
    float speed=100;
    float acceleration=100;
    sf::Time dlugi_czas = sf::Time::Zero;
public:
    AnimatedSprite(const int &fps=1){
        this->my_fps = fps;
    };

    void add_animation_frame(const sf::IntRect &rect){
        rec_vec.emplace_back(rect);
    }

    void step(sf::Clock &zegar){
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=zegar.getElapsedTime();

        if(this->dlugi_czas > pom){
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==rec_vec.size()-1){
                this->current=0;
            }
            this->dlugi_czas = sf::Time::Zero;
        }
        if(this->speed<10000){
            this->speed+=this->acceleration*zegar.getElapsedTime().asSeconds();}

        this->move(0,this->speed*zegar.restart().asSeconds());
    }

    void SetSpeed(float arg_speed){
        this->speed=arg_speed;
    }
};

#endif // ANIMATEDSPRITE_H
