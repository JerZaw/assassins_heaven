#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <platform.h>
#include <movingplatform.h>
#include <timedplatform.h>
#include <timedmovingplatform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Obstacles
{
private:
    std::vector<Platform *> platformpointers;
    int difficulty = 0;
    sf::Texture current_texture;
public:
    Obstacles(int count, sf::Texture texture, sf::IntRect texture_rect, int arg_difficulty){
        this->difficulty = arg_difficulty;
        this->current_texture = texture;
        for(int i=0;i<count;i++){
            this->platformpointers.emplace_back(this->random_platform(this->difficulty));
            this->platformpointers[i]->setTexture(this->current_texture);
            this->platformpointers[i]->setTextureRect(texture_rect);
            if(i==0){
                this->platformpointers[i]->setPosition(600,850);
            }
            else this->platformpointers[i]->setPosition(random_position(i));
            this->platformpointers[i]->SetMiddle();
        }
    }

    sf::Vector2f random_position(int iterator){
        sf::Vector2f vec;
        vec.x = rand()%(1200-int(platformpointers[iterator]->getGlobalBounds().width+1));
        vec.y = rand()%150+20;
        if(iterator==0){
            vec.y+=platformpointers[platformpointers.size()-1]->getPosition().y;
        }
        else{
            vec.y=platformpointers[iterator-1]->getPosition().y-vec.y;
        }

        return vec;
    }

    void SetTexture (sf::Texture texture, sf::IntRect texture_rect){
        this->current_texture = texture;
        for(auto &el : this->platformpointers){
            el->setTexture(current_texture);
            el->setTextureRect(texture_rect);
            el->SetMiddle();
        }
    }

    void SetDifficulty(int arg_difficulty){
        this->difficulty = arg_difficulty;
    }

    int random_pick(int pro0, int pro1, int pro2, int pro3){
        int los=rand()%100;
        int prob[100];
        int i=0;
        while(i<pro0){prob[i]=0;i++;}
        while(i<pro1+pro0){prob[i]=1;i++;}
        while(i<pro2+pro1+pro0){prob[i]=2;i++;}
        while(i<pro3+pro2+pro1+pro0){prob[i]=3;i++;}
        return prob[los];
    }

    Platform *random_platform(const int &difficulty){

        int num,speed,boundary=rand()%40+65,time_=5;
        if(difficulty==1){
            num=this->random_pick(60,40,0,0);
            speed = rand()%30+20;
        }
        else if(difficulty==2){
            num=this->random_pick(20,40,25,15);
            speed = rand()%20+40;
            time_ = rand()%2+3;
        }
        else if(difficulty==3){
            num=this->random_pick(10,35,30,25);
            speed = rand()%20+50;
            time_ = rand()%2+1;
        }
        else num=0;
        Platform* rand_plat;
        switch(num){
        case 1: rand_plat = new MovingPlatform(speed,boundary);break;
        case 2: rand_plat = new TimedPlatform(time_);break;
        case 3: rand_plat = new TimedMovingPlatform(speed,boundary,time_);break;
        default: rand_plat = new Platform;break;
        }
        return rand_plat;
    }

    std::vector<Platform *> GetPlatformsVec(){
        return this->platformpointers;
    }

};

#endif // OBSTACLES_H
