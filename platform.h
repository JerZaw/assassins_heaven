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
    std::vector<std::vector<int>> coin_chances = {{16,24,28,30,100},{12,24,32,36,100},{10,24,34,40,100},{10,26,40,46,100}};
    std::vector<int> current_coin_chances;
    //int difficulty;
public:
    Platform(){};
    Platform(const sf::Texture &arg_texture){
        this->texture = arg_texture;

        //current_coin_chances = coin_chances[arg_difficulty];
        //this->difficulty = arg_difficulty;
        //std::cerr<<difficulty<<std::endl;
        //current_coin_chances.assign(coin_chances[arg_difficulty].begin(),coin_chances[arg_difficulty].end());

    };

    void SetDifficulty(const int &arg_difficulty){
        //this->difficulty = arg_difficulty;
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

    void random_coin(){
        int pom = rand()%100;
        SmallElementCoin *pom_coin;
        if(pom < current_coin_chances[0]){
            pom_coin = new SmallElementCoin(1,0,elements_textures);
        }
        else if(pom < current_coin_chances[1]){
            pom_coin = new SmallElementCoin(2,0,elements_textures);
        }
        else if(pom < current_coin_chances[2]){
            pom_coin = new SmallElementCoin(4,0,elements_textures);
        }
        else if(pom < current_coin_chances[3]){
            pom_coin = new TaskElement(0,0,assassin_logo_texture);pom_coin->setScale(0.3,0.3);
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
