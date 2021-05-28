#ifndef MINDGAMEANIMATEDSPRITE_H
#define MINDGAMEANIMATEDSPRITE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <animatedsprite.h>

class MindGameAnimatedSprite : public AnimatedSprite
{
private:
    float jumping_speed = -320 ;
    int space_press_count = 0;
    bool space_pressed = false;
public:
    MindGameAnimatedSprite(const int &fps=1, const float &ver_speed=100,const float &hor_speed = 250, const float &acceler = 400)
        :AnimatedSprite(fps,ver_speed,hor_speed,acceler){
    };

    void step(const sf::Time &elapsed, const sf::Window &okno){
        AnimatedSprite::step(elapsed,okno);
        check_jump(elapsed,okno);

    }

    void check_jump(const sf::Time &elapsed, const sf::Window &okno){//double jump, trzeba puścić spację pomiędzy skokami
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !space_pressed && space_press_count != 2){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia

            this->SetVerticalSpeed(jumping_speed);
            this->move(0,this->GetVerticalSpeed()*elapsed.asSeconds());
            space_pressed = true;
            space_press_count++;
        }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                space_pressed = false;
            }

        if(this->getGlobalBounds().top + this->getGlobalBounds().height >= okno.getSize().y){
            space_press_count = 0;
        }
        }
};

#endif // MINDGAMEANIMATEDSPRITE_H
