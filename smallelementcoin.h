#ifndef SMALLELEMENTCOIN_H
#define SMALLELEMENTCOIN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

class SmallElementCoin : public sf::Sprite
{
private:
    int value;
    float speed_x;
public:
    SmallElementCoin(){};
    SmallElementCoin(const int &arg_value,const float &arg_speed_x, const sf::Texture &texture, const sf::IntRect &texture_rect){
        value = arg_value;
        this->speed_x = arg_speed_x;
        this->setTexture(texture);
        this->setTextureRect(texture_rect);
        this->setColor(pick_coin_color());
    }

    sf::Color pick_coin_color(){
        switch (value) {
        case 1: return sf::Color::Green;break;
        case 2: return sf::Color::Blue;break;
        default: return sf::Color::Magenta;break;
        }
    }

    void step(const sf::Time &elapsed, const float &speed_y){
        this->move(speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());
    } 

    int picked(){
        this->move(-1000,-1000);
        return value;
    }


};

#endif // SMALLELEMENTCOIN_H
