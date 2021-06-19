#ifndef JUMPINGSCENE_H
#define JUMPINGSCENE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <gameapps.h>
#include <jumping_game_elements.h>
#include <Chronometer.hpp>
#include <cstdlib>
#include <ctime>
#include <summary.h>
#include <scoresavingelement.h>
#include <read_textures.h>
#include <platform.h>
#include <movingplatform.h>
#include <timedplatform.h>
#include <timedmovingplatform.h>
#include <iostream>
#include <animatedsprite.h>
#include <cmath>
#include <scoretable.h>
#include <countdown.h>
#include <fstream>
#include <Shop.h>
#include <movingbackground.h>
#include <stationarybackground.h>
#include <read_textures.h>

class JumpingScene
{
private:
    sf::RenderWindow window;
    JumpingGameElements* jumping_game;
    sftools::Chronometer chrono;
    bool summary_generated = false;
    bool score_saving = false;
    Summary summary;
    ScoreSavingElement scoresaving;
    float speed = 30, last_speed;
    int difficulty = 0;
    bool hero_alive = true;
    bool was_too_high = false;
    sf::Time high_time;
    int points = 0;
    int money = 0;
    const sf::Font font;
    sf::Texture back_texture;
    MovingBackground background;
    StationaryBackground stationary_background;
    ScoreTable points_table, money_table, highscore_table;
    float hero_jumping_speed = -600;
    CountDown *countdown;
    std::pair<std::string,int> highscore;
    bool new_highscore = false;
    Shop *shop;
    const sf::Time MAXshopworkingtime = sf::seconds(12);
    sf::Time shopworkingtime = sf::Time::Zero;
    int boost_height = 0;
    bool boost_bought = false;
    bool boost_started = false;
public:
    JumpingScene(int w, int h):window(sf::VideoMode(w,h),"ASSASSIN'S HEAVEN",sf::Style::Close),
        summary(4,font_comica_bold,&window),scoresaving(font_comica_bold,&window),
        font(font_comica_bold),back_texture(jumping_back_textures),background(&window),stationary_background(&window),
        points_table(&window,scoreboards_textures,sf::IntRect(0,68,238,60), sf::Vector2f(window.getSize().x/2 - 119,5),sf::Vector2f(600,5)),
        money_table(&window,scoreboards_textures,sf::IntRect(0,0,200,60),sf::Vector2f(5,5),sf::Vector2f(63,15)),
        highscore_table(&window,scoreboards_textures,sf::IntRect(101,182,350,60), sf::Vector2f(800,5),sf::Vector2f(850,15)){

        window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1200)/2,0));
        chrono.reset(true);
        jumping_game_music.play();
        srand(time(0));

        countdown = new CountDown(&window);

        points_table.settextonmiddle(-30);

        shop = new Shop(&window);
        shop->update_position(sf::Vector2f(10,window.getSize().y - shop->GetShopBounds().height - 10));

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

        highscore_table.update("HS: "+ highscore.first + "   " + std::to_string(highscore.second));
        highscore_table.settextonmiddle(-37);

//        TaskElement task(0,10,jumping_elements_textures,sf::IntRect(0,288,380,94)); //DO TESTOWANIA MINIGIER
//        task.picked(&chrono);
    };

    void set_jumping_game(JumpingGameElements* ptr){
        jumping_game = ptr;

        jumping_game->Platform_generate_new(random_platform(),rand()%2,0,difficulty);
        jumping_game->PlatformSetNewPosition(0,sf::Vector2f(window.getSize().x/2,window.getSize().y-30));

        for(int i=1;i<jumping_game->GetPlatformCount();i++){
            jumping_game->Platform_generate_new(random_platform(),rand()%2,i,difficulty);
            jumping_game->PlatformSetNewPosition(i,sf::Vector2f(random_position_x(i),random_position_y(i)));
        }
    }

    void draw(){
        window.clear(sf::Color::Black);

        back_draw();
        jumping_game->draw(&window);
        hud_draw();

        window.display();
    }

    void back_draw(){
        stationary_background.draw();
        background.draw();
    }

    void hud_draw(){
        points_table.draw();
        money_table.draw();
        highscore_table.draw();

        if(shop!=nullptr){
            shop->draw();
        }
        if(countdown!=nullptr){
            window.draw(*countdown);
        }

    }

    void window_loop(){
        while (window.isOpen()) {

            sf::Event event;
            // draw everything here...
            if(Game_alive()){

                step(chrono.reset_if());
                // draw everything here...
                draw();
            }
            else if(!summary_generated){
                if(summary_data().first.second){
                    summary.update(L"NEW HIGHSCORE!!!",
                                   L"Congratulations! You got " + std::to_wstring(summary_data().first.first)
                                   + L" points",
                                   L"AND you have " +
                                   std::to_wstring(summary_data().second) + L" coins",
                                   L"Do you want to save your score?");
                }
                else{
                    summary.update(L"YOU DIED",
                                   L"Congratulations! You got " + std::to_wstring(summary_data().first.first)
                                   + L" points",
                                   L"AND " +
                                   std::to_wstring(summary_data().second) + L" coins",
                                   L"Do you want to save your score?");
                }
                summary.create_buttons(menu_button_textures);
                summary.update_main_game();
                summary_generated=true;
            }
            else if(!score_saving){
                summary.draw();
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                std::string pom_chosenbutton = summary.YesOrNo(mouse_position);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(pom_chosenbutton=="no"){
                        click.play();
                        window.close();
                    }
                    else if(pom_chosenbutton=="yes"){
                        click.play();
                        score_saving=true;
                        scoresaving.SetScore(summary_data().first.first);
                    }
                }
            }
            else{
                while (window.pollEvent(event)) {
                    scoresaving.step(event);
                }
                scoresaving.draw();
            }

            // check all the window's events that were triggered since the last iteration of the loop
            while (window.pollEvent(event)) {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
    }

    std::pair<std::pair<int,bool>,int> summary_data(){
        std::pair<int,bool> parka(points,new_highscore);
        std::pair<std::pair<int,bool>,int> bigparka(parka,money);
        return bigparka;
    }

    void step(const sf::Time &elapsed){
        if(countdown==nullptr){

            if(shop!=nullptr){
                shopworkingtime+=elapsed;
                if(shopworkingtime < MAXshopworkingtime){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
                jumping_game->HeroSetVerticalSpeed(0);
                jumping_game->HeroSetRecVec("jump");

                if((fabs(jumping_game->HeroGetGlobalBounds().left + jumping_game->HeroGetGlobalBounds().width/2 - window.getSize().x/2)>1 ||
                    fabs(jumping_game->HeroGetGlobalBounds().top + jumping_game->HeroGetGlobalBounds().height/2 - window.getSize().y/2)>1)
                        && boost_started==false){
                    if(jumping_game->HeroGetGlobalBounds().top + jumping_game->HeroGetGlobalBounds().height/2 < window.getSize().y/2){
                        jumping_game->HeroMove(0,boost_speed*elapsed.asSeconds());
                    }
                    else if(jumping_game->HeroGetGlobalBounds().top + jumping_game->HeroGetGlobalBounds().height/2 > window.getSize().y/2){
                        jumping_game->HeroMove(0,-boost_speed*elapsed.asSeconds());
                    }

                    if(jumping_game->HeroGetGlobalBounds().left + jumping_game->HeroGetGlobalBounds().width/2 < window.getSize().x/2){
                        jumping_game->HeroMove(boost_speed*elapsed.asSeconds(),0);
                    }
                    else if(jumping_game->HeroGetGlobalBounds().left + jumping_game->HeroGetGlobalBounds().width/2 > window.getSize().x/2){
                        jumping_game->HeroMove(-boost_speed*elapsed.asSeconds(),0);
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
                    jumping_game->HeroSetVerticalSpeed(speed);
                }
            }

            for(int i=0;i<int(jumping_game->GetPlatformCount());i++){
                jumping_game->PlatformFullStep(i,elapsed,speed);

                if(jumping_game->PlatformGetWotkingState(i) && boost_bought==false){
                    if(jumping_game->PlatformGetGlobalBounds(i).
                            intersects(jumping_game->HeroGetGlobalBounds())){ //zderzenie z aktywowaną platformą
                        if(jumping_game->HeroGetVerticalSpeed() - speed >0){
                            jumping_game->HeroSetVerticalSpeed(hero_jumping_speed);
                            jumping_game->HeroStartJumpAnimation();
                            jumping_game->PlatformActivate(i);
                        }
                    }

                    if(jumping_game->PlatformGetCoin(i)!=nullptr && //czy zderza się z pieniążkiem jeżeli istnieje
                            jumping_game->HeroGetGlobalBounds().intersects(jumping_game->PlatformGetCoin(i)->getGlobalBounds())){
                        jumping_game->PlatformGetCoin(i)->read_data(this->difficulty);
                        jumping_game->PlatformGetCoin(i)->play_my_sound();
                        std::pair<int,int> pom = jumping_game->PlatformPick(i,chrono);
                        if(pom.first!=0)
                        {
                            chrono.reset(true);
                            countdown = new CountDown(&window);
                        }
                        money+=pom.second;
                        money_table.update(money);
                    }
                }

                if(jumping_game->PlatformGetGlobalBounds(i).top>window.getSize().y){
                    jumping_game->Platform_generate_new(random_platform(),rand()%2,i,difficulty);
                    jumping_game->PlatformSetNewPosition(i,sf::Vector2f(random_position_x(i),random_position_y(i)));
                    points++;
                    points_table.update(points);
                    points_table.settextonmiddle(-30);
                }
                else if(jumping_game->HeroGetGlobalBounds().top + jumping_game->HeroGetGlobalBounds().height <
                        jumping_game->PlatformGetGlobalBounds(i).top){//platformy działają tylko gdy były niżej od stóp ludka
                    jumping_game->PlatformChangeWorkingState(i,true);
                }
            }

            if(points>450){
                difficulty=3;
                jumping_game->set_new_platform_texture_rects(sf::IntRect(0,96,380,94),
                                                             sf::IntRect(382,408,200,100),
                                                             sf::IntRect(0,192,380,94),
                                                             sf::IntRect(232,1288,200,100));
                background.SetTextureRect(difficulty);
                stationary_background.SetTextureRect(difficulty);
            }
            else if(points>300){
                difficulty=2;
                jumping_game->set_new_platform_texture_rects(sf::IntRect(0,768,380,94),
                                                             sf::IntRect(214,1764,200,100),
                                                             sf::IntRect(0,480,380,94),
                                                             sf::IntRect(382,306,200,100));
                background.SetTextureRect(difficulty);
                stationary_background.SetTextureRect(difficulty);
            }
            else if(points>150){
                difficulty=1;
                jumping_game->set_new_platform_texture_rects(sf::IntRect(0,672,380,94),
                                                             sf::IntRect(209,1879,200,100),
                                                             sf::IntRect(0,1056,380,94),
                                                             sf::IntRect(382,102,200,100));
                background.SetTextureRect(difficulty);
                stationary_background.SetTextureRect(difficulty);
            }

            if(jumping_game->HeroGetGlobalBounds().top + jumping_game->HeroGetGlobalBounds().height > window.getSize().y){//śmierć gdy poniżej okna
                this->hero_alive=false;
                death.play();

                std::ofstream zapis_money("assets/money.txt", std::ios::trunc);
                zapis_money << std::to_string(money);
                zapis_money.close();
            }

            background.step(elapsed,speed);
            stationary_background.step(elapsed);

            speed+=elapsed.asSeconds()*1.06;  //przyspieszanie całości z biegiem czasu
            last_speed+=elapsed.asSeconds()*1.06;
            //            hero_jumping_speed=-20*speed; //skakanie i przyspieszenie hero zostają w takim samym stosunku do prędkości gry, nie działa
            //            jumping_game->HeroSetAcceleration(-hero_jumping_speed*1.33);

            hero_jumping_speed=(speed-630); //skakanie i przyspieszenie hero zostają w stałej odległości do prędkości gry, działa
            jumping_game->HeroSetAcceleration(speed+770);
            //std::cerr<<speed<<'\t'<<hero_jumping_speed<<'\t'<<ludek.GetAcceleration()<<std::endl;

            check_if_too_high(elapsed);
            jumping_game->HeroStep(elapsed,window);

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

        if(jumping_game->HeroGetGlobalBounds().top < 200){//przesuwanie planszy gdy gracz wyskoczy ponad window
            if(!this->was_too_high){
                this->last_speed = this->speed;
                this->was_too_high = true;
            }
            else{
                this->speed+=125*elapsed.asSeconds();
                if(jumping_game->HeroGetGlobalBounds().top<0){
                    jumping_game->HeroSetVerticalSpeed(jumping_game->HeroGetVerticalSpeed() + 1200*elapsed.asSeconds());
                }
            }
        }
        else if(this->was_too_high){//spowalnianie zpowrotem to poprzedniej prędkości
            if(this->speed > this->last_speed){
                this->speed -=600*elapsed.asSeconds();
            }
            else {
                this->was_too_high = false;
                this->speed = this->last_speed;
            }
        }
    }

    bool Game_alive(){
        return this->hero_alive;
    }

    float random_position_y(int iterator){
        float vec_y;
        switch (this->difficulty) {
        case 0 :  vec_y = rand()%15+10;break;
        case 1 :  vec_y = rand()%25+20;break;
        case 2 :  vec_y = rand()%35+30;break;
        case 3 :  vec_y = rand()%45+40;break;
        default:  break;
        }

        if(iterator==0){
            vec_y = jumping_game->PlatformGetGlobalBounds(jumping_game->GetPlatformCount()-1).top - vec_y
                    - jumping_game->PlatformGetGlobalBounds(jumping_game->GetPlatformCount()-1).height;
        }
        else{
            vec_y = jumping_game->PlatformGetGlobalBounds(iterator-1).top - vec_y
                    - jumping_game->PlatformGetGlobalBounds(iterator-1).height;
        }
        return vec_y;
    }

    float random_position_x(int iterator){
        float vec_x;
        float last_x,last_width;
        if(iterator==0){
            last_x = jumping_game->PlatformGetGlobalBounds(jumping_game->GetPlatformCount()-1).left;
            last_width = jumping_game->PlatformGetGlobalBounds(jumping_game->GetPlatformCount()-1).width;
        }
        else{
            last_x = jumping_game->PlatformGetGlobalBounds(iterator-1).left;
            last_width =  jumping_game->PlatformGetGlobalBounds(iterator-1).width;
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
        while(vec_x + jumping_game->PlatformGetGlobalBounds(iterator).width > 1200-
              int(jumping_game->PlatformGetGlobalBounds(iterator).width+5)
              || vec_x < 5);

        return vec_x;
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

    Platform *random_platform(){

        int num,speed,boundary=rand()%40+65;
        float time_=1;
        if(difficulty==1){
            num=this->random_pick(60,40,0,0);
            speed = rand()%30+20;
        }
        else if(difficulty==2){
            num=this->random_pick(20,40,25,15);
            speed = rand()%20+40;
            time_ = (rand()%4+2)/10.0;
        }
        else if(difficulty==3){
            num=this->random_pick(10,35,30,25);
            speed = rand()%20+50;
            time_ = (rand()%4+8)/10.0;
        }
        else num=0;

        Platform* rand_plat;
        switch(num){
        case 1: rand_plat = new MovingPlatform(speed,boundary);break;
        case 2: rand_plat = new TimedPlatform(time_);break;
        case 3: rand_plat = new TimedMovingPlatform(speed,boundary,time_);break;
        default: rand_plat = new Platform();break;
        }
        return rand_plat;
    }

    ~JumpingScene(){
        jumping_game_music.stop();
    }
};

#endif // JUMPINGSCENE_H
