#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <smallelementcoin.h>
#include <taskelement.h>
#include <read_textures.h>

class Platform : public sf::Sprite
{
private:
    bool working = false;
    SmallElementCoin *coin = nullptr;
    sf::Texture texture;
public:
    Platform(){};
    Platform(const sf::Texture &arg_texture){
        this->texture = arg_texture;
    };
    void step_y(const sf::Time &elapsed, const float &speed_y){
        this->move(0,speed_y*elapsed.asSeconds());
        if(this->coin!=nullptr){
            this->coin->move(0,speed_y*elapsed.asSeconds());
            coin->step(elapsed);
            coin->setPosition(this->getPosition().x + this->getGlobalBounds().width/2 - coin->getGlobalBounds().width/2,
                              this->getPosition().y - 2 - coin->getGlobalBounds().height);
        }


    };

    virtual void activate(){};
    virtual void SetMiddle(){};

    void draw(sf::RenderWindow *okno){
        okno->draw(*this);
        if(this->coin!=nullptr)okno->draw(*this->coin);
    }

    std::pair<bool,int> pick(sftools::Chronometer *chron){
        std::pair<int,int> pom = coin->picked(chron);
        delete coin;
        coin = nullptr;
        return pom;

    }

    SmallElementCoin *GetCoin(){
        return coin;
    }

    void ChangeWorkingState(const bool &czy){
        this->working = czy;
    }

    bool Is_working(){
        return this->working;
    }

    void random_coin(){
        int pom = rand()%12;
        SmallElementCoin *pom_coin;
        switch (pom) {
        case 1 : pom_coin = new SmallElementCoin(1,0,elements_textures);break;
        case 2 : pom_coin = new SmallElementCoin(2,0,elements_textures);break;
        case 4 : pom_coin = new SmallElementCoin(4,0,elements_textures);break;
        case 0 : pom_coin = new TaskElement(0,0,assassin_logo_texture);pom_coin->setScale(0.3,0.3);break;
        default: pom_coin = nullptr;
        }
        if(pom_coin!=nullptr){
            pom_coin->setPosition(this->getPosition().x + this->getGlobalBounds().width/2 - pom_coin->getGlobalBounds().width/2,
                                  this->getPosition().y - 2 - pom_coin->getGlobalBounds().height);
        }
        this->coin = pom_coin;
    }

    ~Platform(){
        delete coin;
    }
};

#endif // PLATFORM_H
