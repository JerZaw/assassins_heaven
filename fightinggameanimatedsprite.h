#ifndef FIGHTINGGAMEANIMATEDSPRITE_H
#define FIGHTINGGAMEANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <arrow.h>

class FightingGameAnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> rec_vec;
    int current=0;
    int my_fps;
    float shot_velocity = 250;
    float shot_angle = 45*M_PI/180; //kąt w radianach
    float angle_changing_speed;
    float velocity_changing_speed = 80;
    float acceleration;
    sf::Time dlugi_czas = sf::Time::Zero;
    std::vector<sf::CircleShape> aiming_dots;
    int how_many_aiming_dots;
    int max_aiming_dots=30;
    sf::RenderWindow *okno;
    bool shot_made = false;
    bool space_pressed = false;
public:
    FightingGameAnimatedSprite(){};
    FightingGameAnimatedSprite(const int &fps, const float &acceler,
                               const float &arg_angle_changing_speed, sf::RenderWindow *arg_okno){
        this->my_fps = fps;
        this->acceleration = acceler;
        this->angle_changing_speed = arg_angle_changing_speed;
        this->okno = arg_okno;

        for(int i=0;i<max_aiming_dots;i++){//kulki ze zmniejszającą się średnicą
            sf::CircleShape circle(1);
            circle.setFillColor(sf::Color(0,0,0,255));
            circle.setRadius(3-i*0.1);
            aiming_dots.emplace_back(circle);
        }
    };

    void update_aiming_dots(){
        //z wzorów na rzut ukośny
        float v0_y = -shot_velocity * sinf(shot_angle);
        float v0_x = shot_velocity * cosf(shot_angle);
        float flight_time = 2*v0_y/-acceleration;
        float road_x = v0_x * flight_time;
        float road_y = 2*(v0_y*flight_time + acceleration*flight_time*flight_time/2);
        float road = road_x+fabs(road_y);
        how_many_aiming_dots = road/100;
        float circles_distance = road/10/how_many_aiming_dots;
        //MOŻE POPRAWIĆ ODLEGŁOŚCI, ILOŚCI KULEK?

        float a = -acceleration/(2*v0_x*v0_x);
        float b = tanf(shot_angle);

        for(int i=0;i<how_many_aiming_dots;i++){ //tworzenie kulek celujących
            float x = circles_distance*i + 50;
            aiming_dots[i].setPosition(x,okno->getSize().y - aiming_dots[i].getGlobalBounds().height-(a*x*x + b*x));
        }
        for(unsigned long long i=how_many_aiming_dots;i<aiming_dots.size();i++){
            aiming_dots[i].setPosition(-100,-100);
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){//zwiększenie kąta przy sprawdzeniu kątów granicznych
            if(shot_angle<1.308996938995747){ //kąt 75st w radianach
                shot_angle+=elapsed.asSeconds()*this->angle_changing_speed;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(shot_angle>0.523598775598299){//kąt 30st w radianach
                shot_angle-=elapsed.asSeconds()*this->angle_changing_speed;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //po wciśnięciu spacji zmiana mocy podczas trzymania
            space_pressed = true;
            shot_velocity+=velocity_changing_speed*elapsed.asSeconds();
            if(shot_velocity>350 || shot_velocity<150){
                velocity_changing_speed*=-1;
            }
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && space_pressed==true){ //po puszczeniu spacji strzał
            space_pressed = false;
            shot_made = true;
        }
    }

    bool if_shot_called(){
        if(shot_made){
            shot_made = false;
            return true;
        }
        else{
            return false;
        }
    }

    Arrow shoot(){
        float pom_shot_velocity = shot_velocity;
        shot_velocity = 150;
        velocity_changing_speed=fabs(velocity_changing_speed); //strzał i ustawienie początkowej mocy strzału
        return Arrow(pom_shot_velocity,acceleration,aiming_dots[0].getPosition(),shot_angle);
    }

    void draw_all(){
        okno->draw(*this);
        for(auto &el : aiming_dots){
            okno->draw(el);
        }

    }
};

#endif // FIGHTINGGAMEANIMATEDSPRITE_H
