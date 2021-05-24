#ifndef GAMEELEMENTS_H
#define OBSTACLES_H

#include <platform.h>
#include <movingplatform.h>
#include <timedplatform.h>
#include <timedmovingplatform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <animatedsprite.h>
#include <cmath>
#include <scoretable.h>

class GameElements
{
private:
    std::vector<Platform *> platformpointers;
    int difficulty = 0;
    float speed = 20, last_speed;
    sf::Texture current_element_texture;
    sf::Texture current_hero_texture;
    sf::IntRect current_platform_texture_rect;
    AnimatedSprite ludek;
    bool hero_alive = true;
    bool was_too_high = false;
    sf::Time high_time;
    int points = 0;
    ScoreTable score_table;
public:
    GameElements(int count, sf::Texture texture, sf::IntRect texture_rect, int arg_difficulty, sf::Texture hero_texture,
                 const sf::Font *arg_font){
        this->current_hero_texture = hero_texture;
        this->create_ludek();
        this->difficulty = arg_difficulty;
        this->current_element_texture = texture;

        ScoreTable pom_table(current_element_texture,arg_font);
        score_table = pom_table;

        this->current_platform_texture_rect = texture_rect;
        for(int i=0;i<count;i++){
            this->platformpointers.emplace_back(this->random_platform(this->difficulty));
            this->platformpointers[i]->setTexture(this->current_element_texture);
            this->platformpointers[i]->setTextureRect(this->current_platform_texture_rect);
            if(i==0){
                this->platformpointers[i]->setPosition(600,850);
            }
            else this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
            this->platformpointers[i]->SetMiddle();
        }
    }

    void create_ludek(){
        AnimatedSprite pom_ludek(8);
        pom_ludek.setTexture(this->current_hero_texture);
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 1 frame of animation
        pom_ludek.add_animation_frame(sf::IntRect(65, 6, 19, 31)); // 2 frame
        pom_ludek.add_animation_frame(sf::IntRect(115, 6, 19, 31)); // 3 frame
        pom_ludek.add_animation_frame(sf::IntRect(167, 6, 20, 30)); // 4 frame
        pom_ludek.add_animation_frame(sf::IntRect(216,6,20,31)); // 5 frame
        pom_ludek.add_animation_frame(sf::IntRect(266, 6, 20, 31)); // 6 frame
        pom_ludek.add_animation_frame(sf::IntRect(317, 6, 20, 31)); // 7 frame
        pom_ludek.add_animation_frame(sf::IntRect(366, 6, 20, 30)); // 8 frame
        pom_ludek.setTextureRect(sf::IntRect(14,6,19,31));

        ludek = pom_ludek;
        ludek.setPosition(600,500);
    }

    void generate_new(int i){ //podmienia starą platformę na nową random generation
        this->platformpointers[i] = this->random_platform(this->difficulty);
        this->platformpointers[i]->setTexture(this->current_element_texture);
        this->platformpointers[i]->setTextureRect(this->current_platform_texture_rect);
        this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
        this->platformpointers[i]->SetMiddle();

    }

    void step(const sf::Time &elapsed, const sf::Window &okno){

        if(points>15)difficulty=1;
        else if(points>30)difficulty=2;
        else if(points>45)difficulty=3;

        for(int i=0;i<int(platformpointers.size());i++){
            platformpointers[i]->step(elapsed);
            platformpointers[i]->move(0,speed*((difficulty+1.0)*2.0)*elapsed.asSeconds());
            if(platformpointers[i]->Is_working()){
                if(ludek.getGlobalBounds().intersects(sf::FloatRect(platformpointers[i]->getGlobalBounds().left,
                                                                    platformpointers[i]->getGlobalBounds().top,
                                                                    platformpointers[i]->getGlobalBounds().width, 1))){ //zderzenie z górą platformy
                    if(ludek.GetVerticalSpeed()>0){
                        ludek.SetVerticalSpeed(-600);
                        platformpointers[i]->activate();
                    }
                }
            }
            if(platformpointers[i]->getGlobalBounds().top>okno.getSize().y){
                this->generate_new(i);
                points++;
            }
            else if(platformpointers[i]->getGlobalBounds().top > 0){
                platformpointers[i]->ChangeWorkingState(true);
            }
            if(ludek.getPosition().y>okno.getSize().y){
                this->hero_alive=false;
            }
        }
        ludek.step(elapsed);
        ludek.check_hero_move(okno);

        if(ludek.getPosition().y < 250){//przesuwanie planszy gdy gracz wyskoczy ponad okno
            if(!this->was_too_high){
                this->last_speed = this->speed;
                this->was_too_high = true;
                //this->speed = fabs(ludek.GetVerticalSpeed());
                //this->ludek.SetVerticalSpeed(fabs(ludek.GetVerticalSpeed())*2);
            }
            else{
                this->speed+=500*elapsed.asSeconds();
                this->ludek.SetVerticalSpeed(ludek.GetVerticalSpeed()+ 2000*elapsed.asSeconds());
            }
        }
        else if(this->was_too_high /*&& ludek.getPosition().y>300*/){
            if(this->speed > this->last_speed){
                this->speed -=1500*elapsed.asSeconds();
            }
            else {
                this->was_too_high = false;
                this->speed = this->last_speed;
            }
        }
        score_table.update(points);
    }

    bool Game_alive(){
        return this->hero_alive;
    }

    AnimatedSprite GetLudek(){
        return this->ludek;
    }

    ScoreTable GetScoreTable(){
        return this->score_table;
    }

    float random_position_y(int iterator){
        float vec_y;
        vec_y = rand()%50+50;
        if(iterator==0){
            vec_y+=platformpointers[platformpointers.size()-1]->getPosition().y;
        }
        else{
            vec_y=platformpointers[iterator-1]->getPosition().y-vec_y;
        }
        return vec_y;
    }

    float random_position_x(int iterator){
        float vec_x;
        float last_x;
        if(iterator==0){
            last_x = platformpointers[platformpointers.size()-1]->getPosition().x;
        }
        else{
            last_x = platformpointers[iterator-1]->getPosition().x;
        }

        do{
            int pluspom = rand()%2;
            int pom = rand()%300+100;
            if(pluspom==0){
                pom*=-1;
            }
            vec_x = last_x + pom;
        }
        while(vec_x + platformpointers[iterator]->getGlobalBounds().width > 1200-int(platformpointers[iterator]->getGlobalBounds().width+5)
              || vec_x < 5);

        return vec_x;




        //        if(iterator==0){
        //            do{
        //            vec_x = rand()%(1200-int(platformpointers[iterator]->getGlobalBounds().width+1));
        //            }
        //            while(vec_x<(platformpointers[platformpointers.size()-1]->getPosition().x-60)
        //                  ||vec_x>(platformpointers[platformpointers.size()-1]->getPosition().x +
        //                  platformpointers[platformpointers.size()-1]->getGlobalBounds().width + 60));
        //        }
        //        else{
        //            do{
        //            vec_x = rand()%(1200-int(platformpointers[iterator]->getGlobalBounds().width+1));
        //            }
        //            while(vec_x>(platformpointers[iterator-1]->getPosition().x-60)
        //                  &&vec_x<(platformpointers[iterator-1]->getPosition().x +
        //                  platformpointers[iterator-1]->getGlobalBounds().width+60));
        //        }

        //        return vec_x;
    }

    void SetTexture (sf::Texture texture, sf::IntRect texture_rect){
        this->current_element_texture = texture;
        for(auto &el : this->platformpointers){
            el->setTexture(current_element_texture);
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

#endif // GAMEELEMENTS_H
