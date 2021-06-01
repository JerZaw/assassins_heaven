#ifndef ARROW_H
#define ARROW_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

class Arrow : sf::Sprite
{
private:
    sf::Texture texture;
    float speed_x,speed_y;
    float acceleration;
public:
    Arrow(const sf::Texture &arg_texture, const sf::IntRect &texture_rect, const float &starting_speed,
          const float &arg_acceleration, const sf::Vector2f &position, const float &angle){
        this->texture = arg_texture;
        this->setTexture(arg_texture);
        this->setTextureRect(texture_rect);
        this->acceleration = arg_acceleration;
        this->setPosition(position);
        this->rotate(-angle);

        this->speed_x = starting_speed * cosf(angle);
        this->speed_y = -starting_speed * sinf(angle);
    }

    void step(const sf::Time &elapsed){
        this->move(speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());
        //DODAĆ OBRACANIE STRZAŁY -> POCHODNA?? tangens w zależności od obu prędkości?
        speed_y+=acceleration*elapsed.asSeconds();
    }
};

#endif // ARROW_H
