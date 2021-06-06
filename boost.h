#ifndef BOOST_H
#define BOOST_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Boost : public sf::Sprite
{
private:
    int price;
    int boost_height;
    sf::Texture texture;
public:
    Boost(const int &arg_price, const int &arg_boost_height, const sf::Texture &arg_texture, const sf::IntRect &texture_rect){
        this->price = arg_price;
        this->boost_height = arg_boost_height;
        this->texture = arg_texture;
        this->setTexture(texture);
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
