#ifndef TARGET_H
#define TARGET_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <read_textures.h>

class Target : public sf::Sprite
{
private:
    sf::Texture texture;
    bool was_hit = false;
public:
    Target(){};
    Target(const float &scale, const sf::Texture &arg_texture, const sf::IntRect &texture_rect):
    texture(arg_texture){
        this->setTexture(texture);
        this->setTextureRect(texture_rect);
        this->setScale(scale,scale);
    }

    void hit(){
        this->setColor(sf::Color::Green);
        hit_sound.play();
        was_hit=true;
    }

    bool if_hit(){
        return was_hit;
    }
};

#endif // TARGET_H
