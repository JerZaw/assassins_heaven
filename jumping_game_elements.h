#ifndef JUMPINGGAMEELEMENTS_H
#define JUMPINGGAMEELEMENTS_H

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
#include <Chronometer.hpp>
#include <countdown.h>
#include <fstream>

class JumpingGameElements
{
private:
    std::vector<Platform *> platformpointers;
    int difficulty = 0;
    float speed = 30, last_speed;
    sf::Texture elements_textures;
    sf::Texture current_hero_texture;
    sf::IntRect current_platform_texture_rect;
    AnimatedSprite ludek;
    bool hero_alive = true;
    bool was_too_high = false;
    sf::Time high_time;
    int points = 0;
    int money = 0;
    ScoreTable points_table, money_table, highscore_table;
    sf::RenderWindow *okno;
    sftools::Chronometer *chrono1;
    float hero_jumping_speed = -600;
    const sf::Font *font;
    CountDown *countdown;
    std::pair<std::string,int> highscore;
    bool new_highscore = false;
public:
    JumpingGameElements(const int &count, const sf::Texture &texture, const sf::IntRect &texture_rect, const int &arg_difficulty, const sf::Texture &hero_texture,
                        const sf::Font *arg_font, sf::RenderWindow *arg_okno, sftools::Chronometer *arg_chrono){
        this->okno = arg_okno;
        this->current_hero_texture = hero_texture;
        this->create_ludek();
        this->difficulty = arg_difficulty;
        this->elements_textures = texture;
        this->chrono1 = arg_chrono;
        this->font = arg_font;

        countdown = nullptr;

        ScoreTable pom_table(elements_textures,arg_font, okno,sf::IntRect(0,0,200,60),sf::Vector2f(500,15),sf::Vector2f(600,15));
        points_table = pom_table;

        ScoreTable pom2_table(elements_textures,arg_font,okno,sf::IntRect(0,0,100,60),sf::Vector2f(0,15),sf::Vector2f(50,15));
        money_table = pom2_table;

        std::string highscore_pom;
        std::ifstream odczyt("assets/highscores.txt");
        odczyt >> highscore_pom;
        highscore.first = highscore_pom.substr(0,highscore_pom.find('-'));
        highscore.second = std::stoi(highscore_pom.substr(highscore_pom.find('-')+1,highscore_pom.size()-1));
        odczyt.close();

        ScoreTable pom3_table(elements_textures,arg_font,okno,sf::IntRect(0,0,350,60),
                              sf::Vector2f(800,15),sf::Vector2f(850,15),
                              "Highscore: "+ highscore.first + "   " + std::to_string(highscore.second));
        highscore_table = pom3_table;
        highscore_table.settextonmiddle(-highscore_table.GetBackground()->getGlobalBounds().height/2);

        this->current_platform_texture_rect = texture_rect;
        for(int i=0;i<count;i++){
            this->platformpointers.emplace_back(this->random_platform(this->difficulty));
            this->platformpointers[i]->setTexture(this->elements_textures);
            this->platformpointers[i]->setTextureRect(this->current_platform_texture_rect);
            if(i==0){
                this->platformpointers[i]->setPosition(600,850);
            }
            else this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
            this->platformpointers[i]->SetMiddle();
            this->platformpointers[i]->random_coin();
            //                        if(platformpointers[i]->GetCoin()!=nullptr){
            //                            this->platformpointers[i]->GetCoin()->read_data(3);
            //                            this->platformpointers[i]->GetCoin()->picked(chrono1); //DO TESTOWANIA MINIGIER
            //                        }
        }
    }

    std::pair<std::pair<int,bool>,int> summary_data(){
        std::pair<int,bool> parka(points,new_highscore);
        std::pair<std::pair<int,bool>,int> bigparka(parka,money);
        return bigparka;
    }

    void draw(){
        for(auto &el : platformpointers){
            el->draw(okno);
        }
        points_table.draw();
        money_table.draw();
        highscore_table.draw();
        okno->draw(ludek);

        if(countdown!=nullptr){
            okno->draw(*countdown);
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
        delete this->platformpointers[i];
        this->platformpointers[i] = this->random_platform(this->difficulty);
        this->platformpointers[i]->setTexture(this->elements_textures);
        this->platformpointers[i]->setTextureRect(this->current_platform_texture_rect);
        this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
        this->platformpointers[i]->SetMiddle();
        this->platformpointers[i]->random_coin();

    }

    void step(const sf::Time &elapsed, const sf::Window &okno){
        if(countdown==nullptr){

            if(points>45){
                difficulty=3;
            }
            else if(points>30){
                difficulty=2;
            }
            else if(points>15){
                difficulty=1;
            }

            speed+=elapsed.asSeconds()*3;  //przyspieszanie całości z biegiem czasu
            last_speed+=elapsed.asSeconds()*3;
            ludek.accelerate(elapsed.asSeconds()*3);
            hero_jumping_speed-=elapsed.asSeconds()*3;

            if(points>highscore.second){
                highscore.second = points;
                highscore_table.update("NEW Highscore! - " + std::to_string(highscore.second));
                new_highscore = true;
            }

            for(int i=0;i<int(platformpointers.size());i++){
                platformpointers[i]->step_y(elapsed,this->speed);
                platformpointers[i]->step(elapsed);

                if(platformpointers[i]->Is_working()){
                    if(ludek.getGlobalBounds().intersects(sf::FloatRect(platformpointers[i]->getGlobalBounds().left,
                                                                        platformpointers[i]->getGlobalBounds().top,
                                                                        platformpointers[i]->getGlobalBounds().width, 1))){ //zderzenie z górą platformy
                        if(ludek.GetVerticalSpeed()>100){
                            ludek.SetVerticalSpeed(hero_jumping_speed);
                            platformpointers[i]->activate();
                            if(platformpointers[i]->GetCoin()!=nullptr && //czy zderza się z pieniążkiem jeżeli istnieje
                                    ludek.getGlobalBounds().intersects(platformpointers[i]->GetCoin()->getGlobalBounds())){
                                platformpointers[i]->GetCoin()->read_data(this->difficulty);
                                std::pair<int,int> pom = platformpointers[i]->GetCoin()->picked(chrono1);
                                if(pom.first!=0)
                                {
                                    chrono1->reset(true);
                                    std::cerr<<"new countdown\n";
                                    countdown = new CountDown(font,this->okno);
                                }
                                money+=pom.second;
                                money_table.update(money);
                            }
                        }
                    }
                }
                if(platformpointers[i]->getPosition().y>okno.getSize().y){
                    this->generate_new(i);
                    points++;
                    points_table.update(points);
                }
                else if(platformpointers[i]->getGlobalBounds().top > 0){//platformy działają tylko gdy są w oknie
                    platformpointers[i]->ChangeWorkingState(true);
                }

                if(ludek.getPosition().y + ludek.getGlobalBounds().height > okno.getSize().y){//śmierć gdy poniżej okna
                    this->hero_alive=false;
                }
            }
            ludek.step(elapsed,okno);
            check_if_too_high(elapsed);
        }
        else{
            if(countdown->step_countdown_finished(elapsed)){
                delete countdown;
                countdown=nullptr;
            }
        }
    }


    void check_if_too_high(const sf::Time &elapsed){ //może by zrobić move zamiast zmieniać prędkość?

        if(ludek.getPosition().y < 200){//przesuwanie planszy gdy gracz wyskoczy ponad okno
            if(!this->was_too_high){
                this->last_speed = this->speed;
                this->was_too_high = true;
                //this->speed = fabs(ludek.GetVerticalSpeed());
                //this->ludek.SetVerticalSpeed(fabs(ludek.GetVerticalSpeed())*2);
            }
            else{
                this->speed+=70*elapsed.asSeconds();
                if(ludek.getPosition().y<0){
                    ludek.SetVerticalSpeed(ludek.GetVerticalSpeed() + 800*elapsed.asSeconds());
                }//this->ludek.SetVerticalSpeed(ludek.GetVerticalSpeed() - 75*elapsed.asSeconds());
            }
        }
        else if(this->was_too_high /*&& ludek.getPosition().y>300*/){
            if(this->speed > this->last_speed){
                this->speed -=200*elapsed.asSeconds();
            }
            else {
                this->was_too_high = false;
                this->speed = this->last_speed;
            }
        }

        //        if(ludek.getPosition().y < 200){//przesuwanie planszy gdy gracz wyskoczy ponad okno
        //            if(!this->was_too_high){
        //                this->last_speed = this->speed;
        //                this->was_too_high = true;
        //                //this->speed = fabs(ludek.GetVerticalSpeed());
        //                //this->ludek.SetVerticalSpeed(fabs(ludek.GetVerticalSpeed())*2);
        //            }
        //            else{
        //                this->speed+=500*elapsed.asSeconds();
        //                //this->ludek.SetVerticalSpeed(ludek.GetVerticalSpeed()+ 2000*elapsed.asSeconds());
        //            }
        //        }
        //        else if(this->was_too_high /*&& ludek.getPosition().y>300*/){
        //            if(this->speed > this->last_speed){
        //                this->speed -=1500*elapsed.asSeconds();
        //            }
        //            else {
        //                this->was_too_high = false;
        //                this->speed = this->last_speed;
        //            }
        //        }
    }

    bool Game_alive(){
        return this->hero_alive;
    }

    float random_position_y(int iterator){
        float vec_y;
        switch (this->difficulty) {
        case 0 :  vec_y = rand()%2;break;
        case 1 :  vec_y = rand()%6;break;
        case 2 :  vec_y = rand()%12;break;
        case 3 :  vec_y = rand()%20;break;
        default:  vec_y = rand()%2;break;
        }

        if(iterator==0){
            vec_y = platformpointers[platformpointers.size()-1]->getPosition().y - vec_y
                    - platformpointers[platformpointers.size()-1]->getGlobalBounds().height;
        }
        else{
            vec_y = platformpointers[iterator-1]->getPosition().y - vec_y
                    - platformpointers[platformpointers.size()-1]->getGlobalBounds().height;
        }
        return vec_y;
    }

    float random_position_x(int iterator){
        float vec_x;
        float last_x,last_width;
        if(iterator==0){
            last_x = platformpointers[platformpointers.size()-1]->getPosition().x;
            last_width = platformpointers[platformpointers.size()-1]->getGlobalBounds().width;
        }
        else{
            last_x = platformpointers[iterator-1]->getPosition().x;
            last_width = platformpointers[iterator-1]->getGlobalBounds().width;
        }

        do{
            int pluspom = rand()%2;
            int pom = rand()%300+100;
            if(pluspom==0){
                vec_x = last_x - pom - last_width;
            }
            else{
                vec_x = last_x + pom + last_width;
            }
        }
        while(vec_x + platformpointers[iterator]->getGlobalBounds().width > 1200-int(platformpointers[iterator]->getGlobalBounds().width+5)
              || vec_x < 5);

        return vec_x;
    }

    void SetPlatformTextureRect (const sf::IntRect &texture_rect){
        for(auto &el : this->platformpointers){
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
        case 1: rand_plat = new MovingPlatform(speed,boundary,elements_textures);break;
        case 2: rand_plat = new TimedPlatform(time_,elements_textures);break;
        case 3: rand_plat = new TimedMovingPlatform(speed,boundary,time_,elements_textures);break;
        default: rand_plat = new Platform(elements_textures);break;
        }
        return rand_plat;
    }

};

#endif // JUMPINGGAMEELEMENTS_H
