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
#include <Shop.h>
#include <movingbackground.h>
#include <stationarybackground.h>
#include <read_textures.h>

class JumpingGameElements
{
private:
    std::vector<Platform *> platformpointers;
    int difficulty = 0;
    float speed = 30, last_speed;
    sf::Texture elements_textures;
    sf::Texture current_hero_texture;
    sf::IntRect current_long_platform_texture_rect;
    sf::IntRect current_small_platform_texture_rect;
    sf::IntRect current_long_timed_platform_texture_rect;
    sf::IntRect current_small_timed_platform_texture_rect;
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
    Shop *shop;
    const sf::Time MAXshopworkingtime = sf::seconds(12);
    sf::Time shopworkingtime = sf::Time::Zero;
    int boost_height = 0;
    bool boost_bought = false;
    MovingBackground *background;
    StationaryBackground *stationary_background;
    sf::Texture back_texture;
    bool boost_started = false;
public:
    JumpingGameElements(const int &count, const int &arg_difficulty, sf::RenderWindow *arg_okno, sftools::Chronometer *arg_chrono){
        this->okno = arg_okno;
        this->current_hero_texture = hero_texture;
        this->create_ludek();
        this->difficulty = arg_difficulty;
        this->elements_textures = jumping_elements_textures;
        this->chrono1 = arg_chrono;
        this->font = &font_comica_bold;
        this->back_texture = jumping_back_textures;

        background = new MovingBackground(back_texture,arg_okno);

        stationary_background = new StationaryBackground(arg_okno);

        countdown = new CountDown(font,this->okno);

        ScoreTable pom_table(scoreboards_textures,font, okno,sf::IntRect(0,68,238,60),sf::Vector2f(okno->getSize().x/2 - 119,5),sf::Vector2f(600,5));
        pom_table.settextonmiddle(-30);
        points_table = pom_table;

        ScoreTable pom2_table(scoreboards_textures,font,okno,sf::IntRect(0,0,200,60),sf::Vector2f(5,5),sf::Vector2f(63,15));
        money_table = pom2_table;

        shop = new Shop(okno);
        shop->update_position(sf::Vector2f(10,okno->getSize().y - shop->GetShopBounds().height - 10));

        std::string str_pom;

        std::ifstream odczyt_money("assets/money.txt");
        odczyt_money >> str_pom;
        money = std::stoi(str_pom);
        odczyt_money.close();
        money_table.update(money);

        std::ifstream odczyt("assets/highscores.txt");
        odczyt >> str_pom;
        highscore.first = str_pom.substr(0,str_pom.find('-'));
        highscore.second = std::stoi(str_pom.substr(str_pom.find('-')+1,str_pom.size()-1));
        odczyt.close();

        ScoreTable pom3_table(scoreboards_textures,font,okno,sf::IntRect(101,182,350,60),
                              sf::Vector2f(800,5),sf::Vector2f(850,15),
                              "HS: "+ highscore.first + "   " + std::to_string(highscore.second));
        pom3_table.settextonmiddle(-37);
        highscore_table = pom3_table;


        this->current_long_platform_texture_rect = sf::IntRect(0,288,380,94);
        this->current_small_platform_texture_rect = sf::IntRect(214,1662,200,100);
        this->current_long_timed_platform_texture_rect = sf::IntRect(0,384,380,94);
        this->current_small_timed_platform_texture_rect = sf::IntRect(382,204,200,100);
        for(int i=0;i<count;i++){
            this->platformpointers.emplace_back(this->random_platform(this->difficulty));
            this->platformpointers[i]->SetDifficulty(this->difficulty);
            int a=rand()%2;
            if(a==0){
                this->platformpointers[i]->setScale(0.3,0.3);
                this->platformpointers[i]->setTextureRect(this->current_long_platform_texture_rect);
            }
            else{
                this->platformpointers[i]->setScale(0.4,0.4);
                this->platformpointers[i]->setTextureRect(this->current_small_platform_texture_rect);
            }
            this->platformpointers[i]->setTexture(this->elements_textures);
            if(i==0){
                this->platformpointers[i]->setPosition(600,850);
            }
            else this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
            this->platformpointers[i]->SetMiddle();
            this->platformpointers[i]->random_coin(current_long_platform_texture_rect);
        }

        //       TaskElement task(0,0,assassin_logo_texture,current_long_platform_texture_rect); //DO TESTÓW
        //       task.picked(chrono1);
    }

    std::pair<std::pair<int,bool>,int> summary_data(){
        std::pair<int,bool> parka(points,new_highscore);
        std::pair<std::pair<int,bool>,int> bigparka(parka,money);
        return bigparka;
    }

    void draw(){
        stationary_background->draw();
        for(auto &el : platformpointers){
            el->draw(okno);
        }
        background->draw();
        points_table.draw();
        money_table.draw();
        highscore_table.draw();
        okno->draw(ludek);

        if(countdown!=nullptr){
            okno->draw(*countdown);
        }

        if(shop!=nullptr){
            shop->draw();
        }
    }

    void create_ludek(){
        AnimatedSprite pom_ludek(10);
        pom_ludek.setTexture(this->current_hero_texture);

        pom_ludek.setScale(0.2,0.2);
        pom_ludek.setTextureRect(sf::IntRect(0,482,328,433));//first frame

        ludek = pom_ludek;
        ludek.setPosition(600,500);

        ludek.setMainrecvec("walk");
    }

    void generate_new(int i){ //podmienia starą platformę na nową random generation
        delete this->platformpointers[i];
        this->platformpointers[i] = this->random_platform(this->difficulty);
        this->platformpointers[i]->SetDifficulty(this->difficulty);
        this->platformpointers[i]->setTexture(this->elements_textures);
        this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
        this->platformpointers[i]->SetMiddle();
        this->platformpointers[i]->random_coin(current_long_platform_texture_rect);

    }

    void step(const sf::Time &elapsed){
        if(countdown==nullptr){

            if(shop!=nullptr){
                shopworkingtime+=elapsed;
                if(shopworkingtime < MAXshopworkingtime){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
                        if(shop->GetShopBounds().contains(mouse_position)){

                            boost_height = shop->buy(money,mouse_position);
                            if(boost_height != 0){
                                boost_bought = true;
                                delete shop;
                                shop = nullptr;
                                shopworkingtime = sf::Time::Zero;
                                money_table.update(money);
                            }
                        }
                    }
                }
                else{
                    delete shop;
                    shop = nullptr;
                }
            }

            if(boost_bought){//na środek ekranu i potem boost
                int boost_speed = 300;
                ludek.SetVerticalSpeed(0);
                ludek.setrecvec("jump");

                if((fabs(ludek.getGlobalBounds().left + ludek.getGlobalBounds().width/2 - okno->getSize().x/2)>1 ||
                    fabs(ludek.getGlobalBounds().top + ludek.getGlobalBounds().height/2 - okno->getSize().y/2)>1)
                        && boost_started==false){
                    if(ludek.getGlobalBounds().top + ludek.getGlobalBounds().height/2 < okno->getSize().y/2){
                        ludek.move(0,boost_speed*elapsed.asSeconds());
                    }
                    else if(ludek.getGlobalBounds().top + ludek.getGlobalBounds().height/2 > okno->getSize().y/2){
                        ludek.move(0,-boost_speed*elapsed.asSeconds());
                    }

                    if(ludek.getGlobalBounds().left + ludek.getGlobalBounds().width/2 < okno->getSize().x/2){
                        ludek.move(boost_speed*elapsed.asSeconds(),0);
                    }
                    else if(ludek.getGlobalBounds().left + ludek.getGlobalBounds().width/2 > okno->getSize().x/2){
                        ludek.move(-boost_speed*elapsed.asSeconds(),0);
                    }
                }
                else{
                    boost_started = true;
                }

                if(points<boost_height){
                    speed+=elapsed.asSeconds()*1000;  //przyspieszanie całości z biegiem czasu
                }
                else if(speed>31){
                    speed-=elapsed.asSeconds()*3000;//zwolnienie całości z biegiem czasu
                }
                else{
                    boost_bought = false;
                    ludek.SetVerticalSpeed(speed);
                }
            }

            for(int i=0;i<int(platformpointers.size());i++){
                platformpointers[i]->step_y(elapsed,this->speed);
                platformpointers[i]->step(elapsed);

                if(platformpointers[i]->Is_working() && boost_bought==false){
                    if(sf::FloatRect(platformpointers[i]->getGlobalBounds().left,
                                     platformpointers[i]->getGlobalBounds().top+0.1,
                                     platformpointers[i]->getGlobalBounds().width, -0.2).
                            intersects(sf::FloatRect(ludek.getGlobalBounds().left,
                                                     ludek.getGlobalBounds().top + ludek.getGlobalBounds().height-1,
                                                     ludek.getGlobalBounds().width, 1))){ //zderzenie z górą platformy
                        if(ludek.GetVerticalSpeed()>30){
                            ludek.SetVerticalSpeed(hero_jumping_speed);
                            ludek.start_jump_animation();
                            platformpointers[i]->activate();
                        }
                    }

                    if(platformpointers[i]->GetCoin()!=nullptr && //czy zderza się z pieniążkiem jeżeli istnieje
                            ludek.getGlobalBounds().intersects(platformpointers[i]->GetCoin()->getGlobalBounds())){
                        platformpointers[i]->GetCoin()->read_data(this->difficulty);
                        platformpointers[i]->GetCoin()->play_my_sound();
                        std::pair<int,int> pom = platformpointers[i]->pick(chrono1);
                        if(pom.first!=0)
                        {
                            chrono1->reset(true);
                            countdown = new CountDown(font,this->okno);
                        }
                        money+=pom.second;
                        money_table.update(money);
                    }
                }
                if(platformpointers[i]->getPosition().y>okno->getSize().y){
                    this->generate_new(i);
                    points++;
                    points_table.update(points);
                    points_table.settextonmiddle(-30);
                }
                else if(platformpointers[i]->getGlobalBounds().top > 0){//platformy działają tylko gdy są w oknie
                    platformpointers[i]->ChangeWorkingState(true);
                }
            }

            if(points>450){
                difficulty=3;
                this->current_long_platform_texture_rect = sf::IntRect(0,96,380,94);
                this->current_small_platform_texture_rect = sf::IntRect(382,408,200,100);
                this->current_long_timed_platform_texture_rect = sf::IntRect(0,192,380,94);
                this->current_small_timed_platform_texture_rect = sf::IntRect(232,1288,200,100);
                background->SetTextureRect(difficulty);
                stationary_background->SetTextureRect(difficulty);
            }
            else if(points>300){
                difficulty=2;
                this->current_long_platform_texture_rect = sf::IntRect(0,768,380,94);
                this->current_small_platform_texture_rect = sf::IntRect(214,1764,200,100);
                this->current_long_timed_platform_texture_rect = sf::IntRect(0,480,380,94);
                this->current_small_timed_platform_texture_rect = sf::IntRect(382,306,200,100);
                background->SetTextureRect(difficulty);
                stationary_background->SetTextureRect(difficulty);
            }
            else if(points>150){
                difficulty=1;
                this->current_long_platform_texture_rect = sf::IntRect(0,672,380,94);
                this->current_small_platform_texture_rect = sf::IntRect(209,1879,200,100);
                this->current_long_timed_platform_texture_rect = sf::IntRect(0,1056,380,94);
                this->current_small_timed_platform_texture_rect = sf::IntRect(382,102,200,100);
                background->SetTextureRect(difficulty);
                stationary_background->SetTextureRect(difficulty);
            }

            if(ludek.getPosition().y + ludek.getGlobalBounds().height > okno->getSize().y){//śmierć gdy poniżej okna
                this->hero_alive=false;
                death.play();

                std::ofstream zapis_money("assets/money.txt", std::ios::trunc);
                zapis_money << std::to_string(money);
                zapis_money.close();
            }

            background->step(elapsed,speed);
            stationary_background->step(elapsed);

            speed+=elapsed.asSeconds()*1.1;  //przyspieszanie całości z biegiem czasu
            last_speed+=elapsed.asSeconds()*1.1;
            hero_jumping_speed=speed-670;

            ludek.step(elapsed,*okno);
            check_if_too_high(elapsed);

            if(points>highscore.second){
                if(!new_highscore){
                    minigame_end_horns.play();
                }
                highscore.second = points;
                highscore_table.update("NEW Highscore! - " + std::to_string(highscore.second));
                highscore_table.settextonmiddle(-37);
                new_highscore = true;
            }
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
                this->speed+=125*elapsed.asSeconds();
                if(ludek.getPosition().y<0){
                    ludek.SetVerticalSpeed(ludek.GetVerticalSpeed() + 1200*elapsed.asSeconds());
                }//this->ludek.SetVerticalSpeed(ludek.GetVerticalSpeed() - 75*elapsed.asSeconds());
            }
        }
        else if(this->was_too_high /*&& ludek.getPosition().y>300*/){
            if(this->speed > this->last_speed){
                this->speed -=400*elapsed.asSeconds();
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
        case 0 :  vec_y = rand()%15;break;
        case 1 :  vec_y = rand()%25;break;
        case 2 :  vec_y = rand()%35;break;
        case 3 :  vec_y = rand()%45;break;
        default:  break;
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

        int num,speed,boundary=rand()%40+65;
        float time_=1;
        if(difficulty==1){
            num=this->random_pick(60,40,0,0);
            speed = rand()%30+20;
        }
        else if(difficulty==2){
            num=this->random_pick(20,40,25,15);
            speed = rand()%20+40;
            time_ = (rand()%4+5)/10.0;
        }
        else if(difficulty==3){
            num=this->random_pick(10,35,30,25);
            speed = rand()%20+50;
            time_ = (rand()%4+1)/10.0;
        }
        else num=0;

        int a = rand()%2;
        Platform* rand_plat;
        switch(num){
        case 1: rand_plat = new MovingPlatform(speed,boundary,elements_textures);
            if(a==0){
                rand_plat->setScale(0.3,0.3);
                rand_plat->setTextureRect(current_long_platform_texture_rect);
            }
            else{
                rand_plat->setScale(0.4,0.4);
                rand_plat->setTextureRect(current_small_platform_texture_rect);
            }
            break;
        case 2: rand_plat = new TimedPlatform(time_,elements_textures);
            if(a==0){
                rand_plat->setScale(0.3,0.3);
                rand_plat->setTextureRect(current_long_timed_platform_texture_rect);
            }
            else{
                rand_plat->setScale(0.4,0.4);
                rand_plat->setTextureRect(current_small_timed_platform_texture_rect);
            }
            break;
        case 3: rand_plat = new TimedMovingPlatform(speed,boundary,time_,elements_textures);
            if(a==0){
                rand_plat->setScale(0.3,0.3);
                rand_plat->setTextureRect(current_long_timed_platform_texture_rect);
            }
            else{
                rand_plat->setScale(0.4,0.4);
                rand_plat->setTextureRect(current_small_timed_platform_texture_rect);
            }
            break;
        default: rand_plat = new Platform(elements_textures);
            if(a==0){
                rand_plat->setScale(0.3,0.3);
                rand_plat->setTextureRect(current_long_platform_texture_rect);
            }
            else{
                rand_plat->setScale(0.4,0.4);
                rand_plat->setTextureRect(current_small_platform_texture_rect);
            }
            break;
        }
        return rand_plat;
    }

};

#endif // JUMPINGGAMEELEMENTS_H
