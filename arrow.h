#ifndef ARROW_H
#define ARROW_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

class Arrow : public sf::Sprite
{
private:
    sf::Texture texture;
    float acceleration;
    float speed_x,speed_y;    
    int shot_speed_modificator = 4;
public:
    Arrow(const float &starting_speed, const float &arg_acceleration,
          const sf::Vector2f &position, const float &angle):
    acceleration(arg_acceleration),speed_x(starting_speed*cosf(angle)),speed_y(-starting_speed*sinf(angle)){
        this->setPosition(position);
    }

    Arrow(const sf::Texture &arg_texture, const sf::IntRect &texture_rect, const float &starting_speed,
          const float &arg_acceleration, const sf::Vector2f &position, const float &angle):
    texture(arg_texture),acceleration(arg_acceleration),speed_x(starting_speed*cosf(angle)),speed_y(-starting_speed*sinf(angle)){
        this->setTexture(arg_texture);
        this->setTextureRect(texture_rect);
        this->setPosition(position);
    }

    void step(const sf::Time &elapsed){ //poruszanie strzały + obrót według rzutu ukośnego, modyfikator zwiększa szybkość strzały
        this->move(speed_x*shot_speed_modificator*elapsed.asSeconds(),speed_y*shot_speed_modificator*elapsed.asSeconds());
        speed_y+=shot_speed_modificator*acceleration*elapsed.asSeconds();
        this->setRotation(atan2f(speed_y,speed_x) * 180/M_PI);
    }
};

#endif // ARROW_H
