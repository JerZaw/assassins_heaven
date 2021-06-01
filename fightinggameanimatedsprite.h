#ifndef FIGHTINGGAMEANIMATEDSPRITE_H
#define FIGHTINGGAMEANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class FightingGameAnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> rec_vec;
    int current=0;
    int my_fps;
    float shot_velocity = 0;
    float shot_angle = 45;
    float angle_changing_speed;
    float acceleration;
    sf::Time dlugi_czas = sf::Time::Zero;
    std::vector<sf::CircleShape> aiming_dots;
    int how_many_aiming_dots=20;
public:
    FightingGameAnimatedSprite(const int &fps=1, const float &acceler = 800, const float &arg_angle_changing_speed = 50){
        this->my_fps = fps;
        this->acceleration = acceler;
        this->angle_changing_speed = arg_angle_changing_speed;

        for(int i=0;i<how_many_aiming_dots;i++){
            sf::CircleShape circle(10);
            circle.setFillColor(sf::Color(0,0,0,255));
            //DODAĆ FUNKCJĘ OKREŚLAJĄCĄ POZYCJĘ AIMING DOTS I PRZEMIESZCZAJĄCĄ JE
            //z równania toru rzutu ukośnego? ciągle liczy po zmianie?
            //zmiana parametrów przesuwa wierzchołek paraboli? -> z postaci kanonicznej f kwadratowej?
            // b = tg(alpha)
            // a = -acceleration/(2 * v0^2 * cos^2(alpha))
        }
    };

    void add_animation_frame(const sf::IntRect &rect){
        rec_vec.emplace_back(rect);
    }

    void step(const sf::Time &elapsed){ //wymaga restartu zegara, odpowiada za zmianę kąta, moc strzału oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){//zmiana klatek
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==int(rec_vec.size())-1){
                this->current=0;
            }
            this->dlugi_czas = sf::Time::Zero;
        }

        check_aiming_move(elapsed);
    }

    void check_aiming_move(const sf::Time &elapsed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            if(shot_angle<90){
                shot_angle+=elapsed.asSeconds()*this->angle_changing_speed;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(shot_angle>0){
                shot_angle-=elapsed.asSeconds()*this->angle_changing_speed;
            }
        }
    }
};

#endif // FIGHTINGGAMEANIMATEDSPRITE_H
