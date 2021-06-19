#ifndef BOOST_H
#define BOOST_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <read_textures.h>

class Boost : public sf::Sprite
{
private:
    int price;
    int boost_height;
public:
    Boost(const int &arg_price, const int &arg_boost_height, const sf::IntRect &texture_rect):
    price(arg_price),boost_height(arg_boost_height){
        this->setTexture(scoreboards_textures);
        this->setTextureRect(texture_rect);
    }

    int GetPrice(){
        return price;
    }

    int GetBoostHeight(){
        return boost_height;
    }

    int buyboost(int &player_money){
        if(player_money>=price){
            player_money-=price;
            return boost_height;
        }
        else{
            this->setColor(sf::Color::Red);
            return 0;
        }

    }
};

#endif // BOOST_H
