#ifndef MOVINGBACKGROUND_H
#define MOVINGBACKGROUND_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <read_textures.h>

class MovingBackground
{
private:
    sf::Sprite background1,background2;
    sf::Texture texture;
    std::vector<sf::IntRect> texture_rects_vec = {sf::IntRect(0,0,3000,2500),
                                                  sf::IntRect(0,2500,3000,2500),
                                                  sf::IntRect(0,5000,3000,2500),
                                                  sf::IntRect(0,7500,3000,2500)};
    sf::IntRect current_texture_rect = sf::IntRect(0,0,3000,2500);
    sf::RenderWindow *okno;
public:
    MovingBackground(){};
    MovingBackground(const sf::Texture &arg_texture, sf::RenderWindow *arg_okno):
    texture(arg_texture),okno(arg_okno){

        background1.setTexture(this->texture);
        background1.setTextureRect(texture_rects_vec[0]);
        background1.setScale(0.4,0.4);
        background2=background1;
        background1.setPosition(0,0);
        background2.setPosition(0,-background2.getGlobalBounds().height);
    }

    void SetTextureRect(const int &difficulty){
        current_texture_rect = texture_rects_vec[difficulty];
    }

    void draw(){
        okno->draw(background1);
        okno->draw(background2);
    }

    void step(const sf::Time &elapsed, const float &speed){
        background1.move(0,elapsed.asSeconds()*speed);
        background2.move(0,elapsed.asSeconds()*speed);

        if(background1.getPosition().y > okno->getSize().y){
            background1.setPosition(0,-background1.getGlobalBounds().height);
            if(background1.getTextureRect() != current_texture_rect){
                background1.setTextureRect(current_texture_rect);
            }
        }
        else if(background2.getPosition().y > okno->getSize().y){
            background2.setPosition(0,-background2.getGlobalBounds().height);
            if(background2.getTextureRect() != current_texture_rect){
                background2.setTextureRect(current_texture_rect);
            }
        }
    }
};

#endif // MOVINGBACKGROUND_H
