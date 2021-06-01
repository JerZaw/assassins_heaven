#ifndef FIGHTINGGAMEANIMATEDSPRITE_H
#define FIGHTINGGAMEANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class FightingGameAnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> rec_vec;
    int current=0;
    int my_fps;
    float shot_velocity = 250;
    float shot_angle = 45*M_PI/180; //kąt w radianach
    float angle_changing_speed;
    float velocity_changing_speed = 40;
    float acceleration;
    sf::Time dlugi_czas = sf::Time::Zero;
    std::vector<sf::CircleShape> aiming_dots;
    int how_many_aiming_dots=50;
    sf::RenderWindow *okno;
public:
    FightingGameAnimatedSprite(){};
    FightingGameAnimatedSprite(const int &fps, const float &acceler,
                               const float &arg_angle_changing_speed, sf::RenderWindow *arg_okno){
        this->my_fps = fps;
        this->acceleration = acceler;
        this->angle_changing_speed = arg_angle_changing_speed;
        this->okno = arg_okno;

        for(int i=0;i<how_many_aiming_dots;i++){
            sf::CircleShape circle(10);
            circle.setFillColor(sf::Color(0,0,0,255));
            aiming_dots.emplace_back(circle);
        }
        aiming_dots[0].setFillColor(sf::Color::Cyan);
        aiming_dots[how_many_aiming_dots-1].setFillColor(sf::Color::Magenta);
    };

    void update_aiming_dots(){
        //z wzorów na rzut ukośny
        float v0_y = -shot_velocity * sinf(shot_angle);
        float v0_x = shot_velocity * cosf(shot_angle);
        float flight_time = 2*v0_y/-acceleration;
        float road_x = v0_x * flight_time;
        float road_y = 2*(v0_y*flight_time + acceleration*flight_time*flight_time/2);
        float road = road_x+fabs(road_y);
        float circles_distance = road/how_many_aiming_dots; //ZROBIĆ COŚ ŻEBY NIE BYŁY ZA GĘSTO KULKI
        //ZMIENIAJĄCA SIĘ ILOŚĆ W ZALEŻNOŚCI OD DROGI?
        //ZMNIEJSZAJĄCE SIĘ KULKI IM DALEJ?

        float a = -acceleration/(2*v0_x*v0_x);
        float b = tanf(shot_angle);

        for(int i=0;i<how_many_aiming_dots;i++){
            float x = circles_distance*i;
            aiming_dots[i].setPosition(x,okno->getSize().y - aiming_dots[i].getGlobalBounds().height-(a*x*x + b*x));
           //std::cerr<<a*x*x + b*x<<std::endl;
        }
    }

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
        update_aiming_dots();
    }

    void check_aiming_move(const sf::Time &elapsed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            if(shot_angle<1.570796326794897){ //kąt 90st w radianach
                shot_angle+=elapsed.asSeconds()*this->angle_changing_speed;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(shot_angle>0){
                shot_angle-=elapsed.asSeconds()*this->angle_changing_speed;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            shot_velocity+=velocity_changing_speed*elapsed.asSeconds();
            if(shot_velocity>250 || shot_velocity<50){
                velocity_changing_speed*=-1;
            }
        }
    }

    void draw_all(){
        okno->draw(*this);
        for(auto &el : aiming_dots){
            okno->draw(el);
        }

    }
};

#endif // FIGHTINGGAMEANIMATEDSPRITE_H
