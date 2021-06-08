#ifndef SMALLELEMENTCOIN_H
#define SMALLELEMENTCOIN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <Chronometer.hpp>

class SmallElementCoin : public sf::Sprite
{
private:
    int value;
    float speed_x;
    sf::Time dlugi_czas = sf::Time::Zero;
    std::vector<sf::IntRect> rec_vec;
    int current=0;
    int my_fps = 4;
public:
    SmallElementCoin(){};
    SmallElementCoin(const int &arg_value,const float &arg_speed_x, const sf::Texture &texture){
        value = arg_value;
        this->speed_x = arg_speed_x;
        this->setTexture(texture);
        this->setTextureRect(pick_coin_rect());
        this->setScale(0.4,0.4);
    }

    void step(const sf::Time &elapsed){ //wymaga restartu zegara, odpowiada za poruszanie we wszystkie strony oraz zmianę animacji
        sf::Time pom(sf::milliseconds(1000/this->my_fps));
        this->dlugi_czas+=elapsed;

        if(this->dlugi_czas > pom){//zmiana klatek
            this->setTextureRect(rec_vec[++this->current]);
            if(this->current==int(rec_vec.size())-1){
                this->current=0;
            }
            this->dlugi_czas = sf::Time::Zero;
        }
    }

    sf::IntRect pick_coin_rect(){
        switch (value) {
        case 1:
            rec_vec.emplace_back(sf::IntRect(707,296,84,84));
            rec_vec.emplace_back(sf::IntRect(826,206,66,84));
            rec_vec.emplace_back(sf::IntRect(899,116,50,84));
            rec_vec.emplace_back(sf::IntRect(670,406,15,84));
            break;
        case 2:
            rec_vec.emplace_back(sf::IntRect(584,406,84,84));
            rec_vec.emplace_back(sf::IntRect(852,1003,66,84));
            rec_vec.emplace_back(sf::IntRect(899,1219,50,84));
            rec_vec.emplace_back(sf::IntRect(661,651,15,84));
            ;break;
        case 4:
            rec_vec.emplace_back(sf::IntRect(698,1931,84,84));
            rec_vec.emplace_back(sf::IntRect(829,0,66,84));
            rec_vec.emplace_back(sf::IntRect(897,1574,50,84));
            rec_vec.emplace_back(sf::IntRect(645,651,15,84));
            ;break;
        default:
            my_fps = 23;
            rec_vec.emplace_back(sf::IntRect(1,5,161,204));
            rec_vec.emplace_back(sf::IntRect(180,4,163,207));
            rec_vec.emplace_back(sf::IntRect(365,3,160,207));
            rec_vec.emplace_back(sf::IntRect(547,3,159,208));
            rec_vec.emplace_back(sf::IntRect(733,3,153,208));
            rec_vec.emplace_back(sf::IntRect(919,3,143,208));
            rec_vec.emplace_back(sf::IntRect(1110,4,126,204));
            rec_vec.emplace_back(sf::IntRect(1292,3,124,208));
            rec_vec.emplace_back(sf::IntRect(1480,3,114,208));
            rec_vec.emplace_back(sf::IntRect(1673,3,92,206));
            rec_vec.emplace_back(sf::IntRect(1861,2,79,208));
            rec_vec.emplace_back(sf::IntRect(2053,3,58,207));
            rec_vec.emplace_back(sf::IntRect(2245,4,36,204));
            rec_vec.emplace_back(sf::IntRect(2422,4,37,203));
            rec_vec.emplace_back(sf::IntRect(2587,1,57,207));
            rec_vec.emplace_back(sf::IntRect(2754,1,75,208));
            rec_vec.emplace_back(sf::IntRect(2924,1,92,209));
            rec_vec.emplace_back(sf::IntRect(3093,1,107,209));
            rec_vec.emplace_back(sf::IntRect(3269,2,122,208));
            rec_vec.emplace_back(sf::IntRect(3443,3,135,208));
            rec_vec.emplace_back(sf::IntRect(3619,3,146,208));
            rec_vec.emplace_back(sf::IntRect(3790,3,155,209));
            rec_vec.emplace_back(sf::IntRect(3969,4,158,208));
            ;break;
        }
        return rec_vec[0];
    }

    void step(const sf::Time &elapsed, const float &speed_y){
        this->move(speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());
    }

    void SetValue(int arg_value){
        this->value = arg_value;
    }

    virtual std::pair<bool,int> picked(sftools::Chronometer *chron,const int &game_type = 0){
        std::pair<int,int> pom(game_type,value);
        return pom;
    }

    virtual void read_data(const int &arg_difficulty){};


};

#endif // SMALLELEMENTCOIN_H
