#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <smallelementcoin.h>
#include <Chronometer.hpp>

class CountDown : public sf::Text
{
private:
    sf::Time time_left = sf::seconds(3);
    bool countdown_started = false;
    const sf::Font *font;
    sf::RenderWindow *okno;
    bool ready = false;
public:
    CountDown(){};
    CountDown(const sf::Font *arg_font,sf::RenderWindow *arg_okno){

        this->font = arg_font;
        this->okno = arg_okno;

        this->setString(L"Naciśnij klawisz ENTER by rozpocząć grę");
        this->setCharacterSize(50);
        this->setFont(*font);
        this->setPosition(okno->getSize().x/2 - this->getGlobalBounds().width/2,okno->getSize().y/2-70);
        this->setFillColor(sf::Color(200,200,200,128));
    };



    bool step_countdown_finished(const sf::Time &elapsed){
        if(time_left <= sf::Time::Zero){
            return true;
        }
        else{
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                ready = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && ready){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
                countdown_started=true;
            }
            if(countdown_started){
                time_left-=elapsed;
                if(time_left<sf::seconds(1)){
                    this->setString("1");

                }
                else if(time_left<sf::seconds(2)){
                    this->setString("2");
                }
                else if(time_left<sf::seconds(3)){
                    this->setString("3");
                    this->setCharacterSize(100);
                    this->setPosition(okno->getSize().x/2 -
                                               this->getGlobalBounds().width/2,
                                               okno->getSize().y/2-this->getCharacterSize());
                }
            }
            return false;
        }
    }

};

#endif // COUNTDOWN_H
