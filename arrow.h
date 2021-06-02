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
    float speed_x,speed_y;
    float acceleration;
    int shot_speed_modificator = 4;
public:
    Arrow(Arrow arrow, const sf::Texture &arg_texture, const sf::IntRect &texture_rect){
        *this = arrow;
        this->texture = arg_texture;
        this->setTexture(texture);
        this->setTextureRect(texture_rect);
    }

    Arrow(const float &starting_speed, const float &arg_acceleration,
          const sf::Vector2f &position, const float &angle){
        this->acceleration = arg_acceleration;
        this->setPosition(position);
        //this->rotate(-angle);

        this->speed_x = starting_speed * cosf(angle);
        this->speed_y = -starting_speed * sinf(angle);
    }
    Arrow(const sf::Texture &arg_texture, const sf::IntRect &texture_rect, const float &starting_speed,
          const float &arg_acceleration, const sf::Vector2f &position, const float &angle){
        this->texture = arg_texture;
        this->setTexture(arg_texture);
        this->setTextureRect(texture_rect);
        this->acceleration = arg_acceleration;
        this->setPosition(position);
        //this->rotate(-angle);

        this->speed_x = starting_speed * cosf(angle);
        this->speed_y = -starting_speed * sinf(angle);
    }

    void step(const sf::Time &elapsed){ //poruszanie strzały + obrót według rzutu ukośnego, modyfikator zwiększa szybkość strzały
        this->move(speed_x*shot_speed_modificator*elapsed.asSeconds(),speed_y*shot_speed_modificator*elapsed.asSeconds());
        speed_y+=shot_speed_modificator*acceleration*elapsed.asSeconds();
        this->setRotation(atan2f(speed_y,speed_x) * 180/M_PI);
    }
};

#endif // ARROW_H
