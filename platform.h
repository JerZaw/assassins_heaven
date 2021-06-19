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
    //definiowanie szans dla danych monet
    std::vector<std::vector<int>> coin_chances = {{160,240,280,285,1000},
                                                  {120,240,320,330,1000},
                                                  {100,240,340,355,1000},
                                                  {100,260,400,425,1000}};
    std::vector<int> current_coin_chances;
public:
    Platform(){};
    Platform(const sf::Texture &arg_texture):texture(arg_texture){
    };

    void SetDifficulty(const int &arg_difficulty){
        current_coin_chances = coin_chances[arg_difficulty];
    }

    virtual void step(const sf::Time &elapsed){};

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

    void random_coin(const sf::IntRect &current_long_platform_rect){
        int pom = rand()%1000;
        SmallElementCoin *pom_coin;
        if(pom < current_coin_chances[0]){
            pom_coin = new SmallElementCoin(1,0,jumping_elements_textures);
        }
        else if(pom < current_coin_chances[1]){
            pom_coin = new SmallElementCoin(2,0,jumping_elements_textures);
        }
        else if(pom < current_coin_chances[2]){
            pom_coin = new SmallElementCoin(4,0,jumping_elements_textures);
        }
        else if(pom < current_coin_chances[3]){
            pom_coin = new TaskElement(0,0,assassin_logo_texture, current_long_platform_rect);pom_coin->setScale(0.3,0.3);
        }
        else{
           pom_coin = nullptr;
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
