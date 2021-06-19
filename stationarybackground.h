#ifndef STATIONARYBACKGROUND_H
#define STATIONARYBACKGROUND_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <read_textures.h>

class StationaryBackground
{
private:
    std::vector<sf::IntRect> texture_rects_vec = {sf::IntRect(0,0,3000,2500),
                                                  sf::IntRect(0,2500,3000,2500),
                                                  sf::IntRect(0,5000,3000,2500),
                                                  sf::IntRect(0,7500,3000,2500)};
    sf::IntRect current_texture_rect = sf::IntRect(0,0,3000,2500);
    sf::RenderWindow *okno;
    sf::Sprite current_background,set_background;
    sf::Time my_elapsed = sf::Time::Zero;
public:
    StationaryBackground(){};
    StationaryBackground(sf::RenderWindow *arg_okno):okno(arg_okno){
        current_background.setTexture(stationary_jumping_backgrounds);
        current_background.setTextureRect(sf::IntRect(0,0,3000,2500));
        current_background.setScale(0.4,0.4);

        set_background = current_background;
    }

    void SetTextureRect(const int &difficulty){
        set_background.setTextureRect(texture_rects_vec[difficulty]);
    }

    void draw(){
        if(current_background.getTextureRect()!=set_background.getTextureRect()){
        okno->draw(set_background);
        }
        okno->draw(current_background);
    }

    void step(const sf::Time &elapsed){
        if(current_background.getTextureRect()!=set_background.getTextureRect()){
            my_elapsed+=elapsed;
            if(current_background.getColor().a>0){
                if(my_elapsed>sf::seconds(0.03)){
                    current_background.setColor(sf::Color(current_background.getColor().r,
                                                          current_background.getColor().g,
                                                          current_background.getColor().b,
                                                          current_background.getColor().a-1));
                    my_elapsed = sf::Time::Zero;
                }
            }
            else{
                current_background = set_background;
            }
        }
    }
};

#endif // STATIONARYBACKGROUND_H
