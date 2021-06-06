#ifndef SMALLELEMENTCOIN_H
#define SMALLELEMENTCOIN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <Chronometer.hpp>

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
        case 4: return sf::Color::Magenta;break;
        default: return sf::Color::Black;break;
        }
    }

    void step(const sf::Time &elapsed, const float &speed_y){
        this->move(speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());
    } 

    void SetValue(int arg_value){
        this->value = arg_value;
    }

    virtual std::pair<bool,int> picked(sftools::Chronometer *chron,const int &game_type = 0){
        std::pair<int,int> pom(game_type,value);
        this->move(-1000,-1000);
        return pom;
    }

    virtual void read_data(const int &arg_difficulty){};


};

#endif // SMALLELEMENTCOIN_H
