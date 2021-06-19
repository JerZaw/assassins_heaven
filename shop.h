#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <Boost.h>
#include <read_textures.h>

class Shop
{
private:
    sf::Sprite background;
    sf::RenderWindow *okno;
    std::vector<Boost> boosts;
    sf::Text text_1,text_2;
public:
    Shop(){};
    Shop(sf::RenderWindow *window):okno(window){

        background.setTexture(scoreboards_textures);
        background.setTextureRect(sf::IntRect(285,0,561,174));
        background.setScale(0.6,0.75);

        boosts.emplace_back(Boost(300,100,sf::IntRect(0,145,70,70)));
        text_1.setString(std::to_string(boosts[0].GetPrice()));
        text_1.setFont(font_comica);
        text_1.setCharacterSize(25);

        boosts.emplace_back(Boost(550,200,sf::IntRect(1,218,70,70)));
        text_2.setFont(font_comica);
        text_2.setString(std::to_string(boosts[1].GetPrice()));
        text_2.setCharacterSize(25);

    }

    sf::FloatRect GetShopBounds(){
        return background.getGlobalBounds();
    }

    void update_position(const sf::Vector2f &shop_position){
        background.setPosition(shop_position);
        boosts[0].setPosition(background.getPosition().x + 30,background.getPosition().y+
                              background.getGlobalBounds().height/2 - boosts[0].getGlobalBounds().height/2 - 7);
        text_1.setPosition(boosts[0].getPosition().x + boosts[0].getGlobalBounds().width + 5,
                background.getPosition().y+background.getGlobalBounds().height/2 - text_1.getCharacterSize());
        boosts[1].setPosition(background.getPosition().x+ 60 +
                              boosts[0].getGlobalBounds().left + boosts[0].getGlobalBounds().width,background.getPosition().y+
                background.getGlobalBounds().height/2 - boosts[1].getGlobalBounds().height/2 - 7);
        text_2.setPosition(boosts[1].getPosition().x + boosts[1].getGlobalBounds().width + 5,
                background.getPosition().y+background.getGlobalBounds().height/2 - text_2.getCharacterSize());
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
        okno->draw(text_1);
        okno->draw(text_2);
    }
};

#endif // SHOP_H
