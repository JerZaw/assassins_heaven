#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <read_textures.h>

class AnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::IntRect> current_rec_vec, rec_vec, jumping_rec_vec, walking_rec_vec, idle_rec_vec;
    int current=0;
    int my_fps;
    float verticalspeed;
    float horizontalspeed;
    float acceleration;
    sf::Time dlugi_czas = sf::Time::Zero;
    int pressed = 0;
    enum { CHANGED_LEFT, CHANGED_RIGHT } side_state = CHANGED_RIGHT;
    bool jumping = false;
public:

    AnimatedSprite(const int &fps=1, const float &ver_speed=100,const float &hor_speed = 250, const float &acceler = 800){
        this->my_fps = fps;
        this->verticalspeed = ver_speed;
        this->horizontalspeed = hor_speed;
        this->acceleration = acceler;

        //JUMPING TEXTURE RECTANGLES
        this->add_jumping_animation_frame(sf::IntRect(0,14,282,437)); // 1 frame of animation
        this->add_jumping_animation_frame(sf::IntRect(290, 4, 266, 461)); // 2 frame
        this->add_jumping_animation_frame(sf::IntRect(567, 2, 253, 433)); // 3 frame
        this->add_jumping_animation_frame(sf::IntRect(834, 2, 253, 432)); // 4 frame
        this->add_jumping_animation_frame(sf::IntRect(1134,2,253,432)); // 5 frame
        this->add_jumping_animation_frame(sf::IntRect(1402, 2,253,432)); // 6 frame
        this->add_jumping_animation_frame(sf::IntRect(1677, 2, 274, 425)); // 7 frame
        this->add_jumping_animation_frame(sf::IntRect(1980, 0, 301, 420)); // 8 frame
        this->add_jumping_animation_frame(sf::IntRect(2321, 0, 329, 412)); // 9 frame
        this->add_jumping_animation_frame(sf::IntRect(2685, 0, 329, 412)); // 10 frame

        //RUNNING TEXTURE RECTANGLES
        this->add_walking_animation_frame(sf::IntRect(0,482,328,433)); // 1 frame of animation
        this->add_walking_animation_frame(sf::IntRect(330, 476, 323, 450)); // 2 frame
        this->add_walking_animation_frame(sf::IntRect(655, 472, 321, 446)); // 3 frame
        this->add_walking_animation_frame(sf::IntRect(983, 475, 353, 422)); // 4 frame
        this->add_walking_animation_frame(sf::IntRect(1340,482,354,427)); // 5 frame
        this->add_walking_animation_frame(sf::IntRect(1694, 482,328,427)); // 6 frame
        this->add_walking_animation_frame(sf::IntRect(2031, 476, 323, 448)); // 7 frame
        this->add_walking_animation_frame(sf::IntRect(2357, 472, 316, 431)); // 8 frame
        this->add_walking_animation_frame(sf::IntRect(2678, 474, 318, 405)); // 9 frame
        this->add_walking_animation_frame(sf::IntRect(2998, 482, 328, 422)); // 10 frame

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

        rec_vec = idle_rec_vec;
        current_rec_vec = rec_vec;
    };

    void setMainrecvec(const std::string &action_name){
        if(action_name == "walk"){
            rec_vec = walking_rec_vec;
        }
        else if(action_name == "idle"){
            rec_vec = idle_rec_vec;
        }
        else if(action_name == "jump"){
            rec_vec = jumping_rec_vec;
        }
        current_rec_vec = rec_vec;
    }

    void setrecvec(const std::string &action_name){
        if(action_name == "walk"){
            current_rec_vec = walking_rec_vec;
        }
        else if(action_name == "idle"){
            current_rec_vec = idle_rec_vec;
        }
        else if(action_name == "jump"){
            current_rec_vec = jumping_rec_vec;
        }
    }

    void SetHorizontalSpeed(float arg_horizontalspeed){
        this->horizontalspeed=arg_horizontalspeed;
    }

    float GetHorizontalSpeed(){
        return this->horizontalspeed;
    }

    void add_walking_animation_frame(const sf::IntRect &rect){
        walking_rec_vec.emplace_back(rect);
    }

    void start_jump_animation(){
        jump_sound.play();
        current = 0;
        dlugi_czas = sf::Time::Zero;
        current_rec_vec = jumping_rec_vec;
        jumping = true;
    }

    void add_idle_animation_frame(const sf::IntRect &rect){
        idle_rec_vec.emplace_back(rect);
    }

    void add_jumping_animation_frame(const sf::IntRect &rect){
        jumping_rec_vec.emplace_back(rect);
    }

    void accelerate(float added_acceleration){
        acceleration+=added_acceleration;
    }

    virtual void vertical_step(const sf::Time &elapsed, const sf::Window &okno){
        this->move(0,this->verticalspeed*elapsed.asSeconds());
        if(this->verticalspeed<100000){
            this->verticalspeed+=this->acceleration*elapsed.asSeconds();
        }
    }

    void step(const sf::Time &elapsed, const sf::Window &okno){ //wymaga restartu zegara, odpowiada za poruszanie we wszystkie strony oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){//zmiana klatek
            this->setTextureRect(current_rec_vec[++this->current]);
            if(this->current==int(current_rec_vec.size())-1){
                this->current=0;
                if(jumping){
                    jumping = false;
                    current_rec_vec = rec_vec;
                }
            }
            this->dlugi_czas = sf::Time::Zero;
        }

        vertical_step(elapsed,okno);

        if(this->pressed==1){//ruch prawo lewo
            this->move(elapsed.asSeconds()*this->horizontalspeed,0);
        }
        else if(this->pressed==2){
            this->move(-elapsed.asSeconds()*this->horizontalspeed,0);
        }

        this->check_hero_move(okno);//sprawdzanie ruchu prawo lewo
    }

    void SetVerticalSpeed(float arg_verticalspeed){
        this->verticalspeed=arg_verticalspeed;
    }

    float GetVerticalSpeed(){
        return this->verticalspeed;
    }

    float GetAcceleration(){
        return this->acceleration;
    }

    void check_hero_move(const sf::Window &okno){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            this->pressed = 1;
            if (this->getGlobalBounds().left+this->getGlobalBounds().width > okno.getSize().x){
                this->move(-(this->getGlobalBounds().left + this->getGlobalBounds().width - okno.getSize().x),0);
            }
            if(side_state==CHANGED_LEFT){
                this->setScale(0.2,0.2);
                this->move(-this->getGlobalBounds().width,0);
                side_state = CHANGED_RIGHT;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->pressed = 2;
            if (this->getGlobalBounds().left < 0){
                this->move(-this->getGlobalBounds().left,0);
            }
            if(side_state==CHANGED_RIGHT){
                this->setScale(-0.2,0.2);
                this->move(this->getGlobalBounds().width,0);
                side_state = CHANGED_LEFT;
            }
        }
        else {
                this->pressed = 0;
        }
    }
};

#endif // ANIMATEDSPRITE_H
