#ifndef MINDGAMEANIMATEDSPRITE_H
#define MINDGAMEANIMATEDSPRITE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <animatedsprite.h>

class MindGameAnimatedSprite : public AnimatedSprite
{
private:
    float jumping_speed;
    int space_press_count = 0;
    bool space_pressed = false;
public:
    MindGameAnimatedSprite(const int &fps=1, const float &ver_speed=100,const float &hor_speed = 250, const float &acceler = 400,
                           const float &arg_jumping_speed = -600)
        :AnimatedSprite(fps,ver_speed,hor_speed,acceler){
        this->jumping_speed = arg_jumping_speed;
        setMainrecvec("idle");
    };

    void step(const sf::Time &elapsed, const sf::Window &okno){
        AnimatedSprite::step(elapsed,okno);
        check_jump(elapsed);

        if(this->getGlobalBounds().top < 0){
            this->SetVerticalSpeed(1);
        }

        check_animation(okno);
    }

    void check_animation(const sf::Window &okno){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            setrecvec("walk");
        }
        else if(this->getGlobalBounds().top + this->getGlobalBounds().height >= okno.getSize().y){
            setrecvec("idle");
        }
    }

    void vertical_step(const sf::Time &elapsed, const sf::Window &okno){
        if(this->getGlobalBounds().top + this->getGlobalBounds().height < okno.getSize().y){
            this->move(0,this->GetVerticalSpeed()*elapsed.asSeconds());
            if(this->GetVerticalSpeed()<100000){
                this->SetVerticalSpeed(this->GetVerticalSpeed()+this->GetAcceleration()*elapsed.asSeconds());
            }
        }
        else{
            this->SetVerticalSpeed(0);
            //this->setrecvec("idle");
            this->setPosition(this->getPosition().x,okno.getSize().y - this->getGlobalBounds().height);
        }
    }

    void check_jump(const sf::Time &elapsed){//double jump, trzeba puścić spację pomiędzy skokami
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !space_pressed && space_press_count != 2){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia

            this->SetVerticalSpeed(jumping_speed);
            this->move(0,this->GetVerticalSpeed()*elapsed.asSeconds());
            this->start_jump_animation();
            space_pressed = true;
            space_press_count++;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            space_pressed = false;
        }

        if(this->GetVerticalSpeed() == 0){
            space_press_count = 0;
        }
    }
};

#endif // MINDGAMEANIMATEDSPRITE_H
