#ifndef FIGHTINGGAMEANIMATEDSPRITE_H
#define FIGHTINGGAMEANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <arrow.h>
#include <read_textures.h>

class FightingGameAnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> rec_vec, idle_rec_vec, throwing_rec_vec;
    int current=0;
    int my_fps;
    float shot_velocity = 250;
    float shot_angle = 45*M_PI/180; //kąt w radianach
    float acceleration;
    float angle_changing_speed;
    float velocity_changing_speed = 80;
    sf::Time dlugi_czas = sf::Time::Zero;
    std::vector<sf::CircleShape> aiming_dots;
    int how_many_aiming_dots;
    int max_aiming_dots=30;
    sf::RenderWindow *okno;
    bool shot_made = false;
    bool space_pressed = false;
    bool throwing = false;
public:
    FightingGameAnimatedSprite(){};
    FightingGameAnimatedSprite(const int &fps, const float &acceler,
                               const float &arg_angle_changing_speed, sf::RenderWindow *arg_okno):
        my_fps(fps),acceleration(acceler),angle_changing_speed(arg_angle_changing_speed),okno(arg_okno){

        //IDLE TEXTURE RECTANGLES
        this->add_idle_animation_frame(sf::IntRect(1,1415,232,439)); // 1 frame of animation
        this->add_idle_animation_frame(sf::IntRect(242,1416, 231,438)); // 2 frame
        this->add_idle_animation_frame(sf::IntRect(480,1416, 229,438)); // 3 frame
        this->add_idle_animation_frame(sf::IntRect(721,1417,228,437)); // 4 frame
        this->add_idle_animation_frame(sf::IntRect(958,1418,227,436)); // 5 frame
        this->add_idle_animation_frame(sf::IntRect(1191,1419,226,435)); // 6 frame
        this->add_idle_animation_frame(sf::IntRect(1426,1418,227,436)); // 7 frame
        this->add_idle_animation_frame(sf::IntRect(1661,1417,228,437)); // 8 frame
        this->add_idle_animation_frame(sf::IntRect(1896,1416,229,438)); // 9 frame
        this->add_idle_animation_frame(sf::IntRect(2134,1416,231,438)); // 10 frame

        //THROWING TEXTURE RECTANGLES
        this->add_throwing_animation_frame(sf::IntRect(0,1878,257,425)); // 1 frame of animation
        this->add_throwing_animation_frame(sf::IntRect(261,1867,240,438)); // 2 frame
        this->add_throwing_animation_frame(sf::IntRect(513,1861,314,444)); // 3 frame
        this->add_throwing_animation_frame(sf::IntRect(844,1861,303,443)); // 4 frame
        this->add_throwing_animation_frame(sf::IntRect(1156,1861,299,443)); // 5 frame
        this->add_throwing_animation_frame(sf::IntRect(1464,1861,297,443)); // 6 frame
        this->add_throwing_animation_frame(sf::IntRect(1770,1861,295,442)); // 7 frame
        this->add_throwing_animation_frame(sf::IntRect(2078,1861,323,446)); // 8 frame
        this->add_throwing_animation_frame(sf::IntRect(2409,1863,292,444)); // 9 frame
        this->add_throwing_animation_frame(sf::IntRect(2715,1869,241,437)); // 10 frame

        for(int i=0;i<max_aiming_dots;i++){//kulki ze zmniejszającą się średnicą
            sf::CircleShape circle(1);
            circle.setFillColor(sf::Color(0,0,0,255));
            circle.setRadius(3-i*0.1);
            aiming_dots.emplace_back(circle);
        }

        rec_vec = idle_rec_vec;
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

        aiming_dots[0].setPosition(100,okno->getSize().y - 70);
        for(int i=1;i<how_many_aiming_dots;i++){ //tworzenie kulek celujących
            float x = circles_distance*i + aiming_dots[0].getGlobalBounds().left;
            aiming_dots[i].setPosition(x,okno->getSize().y - aiming_dots[i].getGlobalBounds().height
                                       -(a*(x-100)*(x-100) + b*(x-100)) - 65);
        }
        for(unsigned long long i=how_many_aiming_dots;i<aiming_dots.size();i++){
            aiming_dots[i].setPosition(-100,-100);
        }
    }

    void add_throwing_animation_frame(const sf::IntRect &rect){
        throwing_rec_vec.emplace_back(rect);
    }

    void add_idle_animation_frame(const sf::IntRect &rect){
        idle_rec_vec.emplace_back(rect);
    }

    void step(const sf::Time &elapsed){ //wymaga restartu zegara, odpowiada za zmianę kąta, moc strzału oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){//zmiana klatek
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==int(rec_vec.size())-1){
                this->current=0;
                if(throwing){
                    throwing = false;
                    rec_vec = idle_rec_vec;
                }
            }
            if(throwing && this->current == 3){
                shot_made = true;
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
            throw_sound.play();
            start_throw_animation();
        }
    }

    void start_throw_animation(){
        current = 0;
        dlugi_czas = sf::Time::Zero;
        rec_vec = throwing_rec_vec;
        throwing = true;
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
        return Arrow(fighting_elements_textures,sf::IntRect(765,421,160,32),pom_shot_velocity,
                     acceleration,aiming_dots[0].getPosition(),shot_angle);
    }

    void draw_all(){
        okno->draw(*this);
        for(auto &el : aiming_dots){
            okno->draw(el);
        }

    }
};

#endif // FIGHTINGGAMEANIMATEDSPRITE_H
