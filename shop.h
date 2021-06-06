#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <boost.h>

class Shop
{
private:
    sf::Sprite background;
    sf::RenderWindow *okno;
    sf::Texture textures;
    std::vector<Boost> boosts;
    //const int BOOST_COUNT = 2;
public:
    Shop(){};
    Shop(const sf::Texture &elements_texture, sf::RenderWindow *window){
        this->textures = elements_texture;
        this->okno = window;

        background.setTexture(textures);
        background.setTextureRect(sf::IntRect(0,0,200,70));

        boosts.emplace_back(Boost(300,100,textures,sf::IntRect(0,0,50,50)));
        boosts.emplace_back(Boost(600,250,textures,sf::IntRect(0,0,50,50)));

    }

    sf::FloatRect GetShopBounds(){
        return background.getGlobalBounds();
    }

    void update_position(const sf::Vector2f &shop_position){
        background.setPosition(shop_position);
        boosts[0].setPosition(background.getPosition().x+30,background.getPosition().y+10);
        boosts[1].setPosition(background.getPosition().x+80 + boosts[0].getGlobalBounds().width,background.getPosition().y+10);
    }

    int buy(int &player_money, const sf::Vector2f &mouse_position){//w pętli gry aktywowane gdy gracz kliknie w obrębie sklepu
        for(unsigned long long i=0;i<boosts.size();i++){
            if(boosts[i].getGlobalBounds().contains(mouse_position)){
                return boosts[i].buyboost(player_money);
            }
        }
        return 0;
    }

    void draw(){
        okno->draw(background);
        for(auto &el : boosts){
            okno->draw(el);
        }
    }
};

#endif // SHOP_H
