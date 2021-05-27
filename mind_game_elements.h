#ifndef MINDGAMEELEMENTS_H
#define MINDGAMEELEMENTS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <animatedsprite.h>
#include <cstdlib>
#include <ctime>
#include <scoretable.h>
#include <Chronometer.hpp>
#include <platformwithequation.h>
#include <vector>
#include <animatedsprite.h>
#include <cmath>
#include <iomanip>
#include <sstream>

class MindGameElements
{
private:
    std::vector<PlatformWithEquation> platforms;
    std::vector<std::pair<std::string,bool>> answers;
    int difficulty;
    int platform_count;
    sf::Texture elements_textures;
    sf::IntRect platform_texture_rect;
    sf::Texture hero_texture;
    const sf::Font *font;
    sf::RenderWindow *okno;
    sftools::Chronometer *chrono;
    int character_size = 30;
    std::string equation;
public:
    MindGameElements(){};
    MindGameElements(const int &arg_difficulty,const sf::Texture &arg_elements_textures, const sf::IntRect &arg_platform_texture_rect,
                     const sf::Texture &arg_hero_texture, const sf::Font *arg_font, sf::RenderWindow *arg_okno,
                     sftools::Chronometer *arg_chrono){
        this->difficulty = arg_difficulty;
        this->elements_textures = arg_elements_textures;
        this->platform_texture_rect = arg_platform_texture_rect;
        this->hero_texture = arg_hero_texture;
        this->font = arg_font;
        this->okno = arg_okno;
        this->chrono = arg_chrono;
        generate_platforms();
    };

    void generate_platforms(){
        switch (this->difficulty) {
        case 0:platform_count=2;break;
        case 1:platform_count=rand()%2+2;break;
        case 2:platform_count=rand()%3;break;
        case 3:platform_count=rand()%2+3;break;
        }

        generate_equation_and_answers();

        for(int i=0;i<platform_count;i++){
            platforms.emplace_back(generate_platform(i));
        }
    }

    float float_round(const float &a){ //zaokrągla do dwóch miejsc po przecinku, żeby nie były za długie liczby
        return round(a*100)/100;
    }

    void generate_equation_and_answers(){
        float a,b;
        float c;
        enum operation{ DODAWANIE,ODEJMOWANIE,MNOZENIE,DZIELENIE/*POTEGOWANIE,PIERWIASTEK*/} operation_type;
        switch (this->difficulty) {//w zależności od difficulty losuje działanie i składowe
        case 0:a=rand()%10;b=rand()%5;operation_type=DODAWANIE;break;
        case 1:a=rand()%20;b=rand()%20;operation_type=operation(rand()%2);break;
        case 2:operation_type=operation(rand()%3);
            if(operation_type==DODAWANIE || operation_type==ODEJMOWANIE){
                a=rand()%50;b=rand()%50;
            }
            else{
                a=rand()%10+1;b=rand()%19+1;
            }
            break;
        case 3:operation_type=operation(rand()%4);
            if(operation_type==DODAWANIE || operation_type==ODEJMOWANIE){
                a=rand()%200;b=rand()%100;
            }
            else{
                a=rand()%99+1;b=rand()%9+1;
            }
            break;
        }

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << a;

        switch (operation_type) {//dodaje składowe do stringa
        case DODAWANIE:
            c=a+b;
            stream<<" + ";
            break;
        case ODEJMOWANIE:
            c=a-b;
            stream<<" - ";
            break;
        case MNOZENIE:
            c=a*b;
            stream<<" * ";
            break;
        case DZIELENIE:
            c=float_round(a/b);
            stream<<" / ";
            break;
        }

        int solution_place = rand()%platform_count;

        stream << std::fixed << std::setprecision(2) << b << " = ";
        this->equation = stream.str();

        for(int i=0;i<platform_count;i++){//dodaje dobre rozwiązanie lub losuje złe niewylosowane wcześniej
            std::stringstream answer_stream;
            if(i==solution_place){
                answer_stream << std::fixed << std::setprecision(2) << c;
                answers.emplace_back(answer_stream.str(),true);
            }
            else{
                float addon;
                do{
                    addon = rand()%10+1;
                    int mnoznik=rand()%2;
                    if(mnoznik==0){
                        addon=-addon;
                    }
                }
                while(std::find_if(answers.begin(),answers.end(),[&c,&addon]
                     (const std::pair<std::string,bool> &el){return el.first==std::to_string(c+addon);})!=answers.end());

                answer_stream << std::fixed << std::setprecision(2) << c+addon;
                answers.emplace_back(answer_stream.str(),false);
            }
        }
    }

    PlatformWithEquation generate_platform(int current_count){//generuje platformę z równaniem losowo wygenerowanym; platformy w równej odległości
        sf::Vector2f plat_pos(float(1500)/this->platform_count*(current_count+1),400);

        std::cerr<<equation<<answers[current_count].first<<" - "<<answers[current_count].second<<std::endl;

        return PlatformWithEquation(elements_textures,font,okno,platform_texture_rect,plat_pos,plat_pos,
                                    answers[current_count].first,character_size,answers[current_count].second);

    }







    //private:
    //    std::vector<Platform *> platformpointers;
    //    int difficulty = 0;
    //    float speed = 30, last_speed;
    //    sf::Texture elements_textures;
    //    sf::Texture current_hero_texture;
    //    sf::IntRect current_platform_texture_rect;
    //    AnimatedSprite ludek;
    //    bool hero_alive = true;
    //    bool was_too_high = false;
    //    sf::Time high_time;
    //    int points = 0;
    //    int money = 0;
    //    ScoreTable points_table, money_table;
    //    sf::RenderWindow *okno;
    //    sftools::Chronometer *chrono1;
    //public:
    //    JumpingGameElements(int count, sf::Texture texture, sf::IntRect texture_rect, int arg_difficulty, sf::Texture hero_texture,
    //                 const sf::Font *arg_font, sf::RenderWindow *arg_okno, sftools::Chronometer *arg_chrono){
    //        this->okno = arg_okno;
    //        this->current_hero_texture = hero_texture;
    //        this->create_ludek();
    //        this->difficulty = arg_difficulty;
    //        this->elements_textures = texture;
    //        this->chrono1 = arg_chrono;

    //        ScoreTable pom_table(elements_textures,arg_font, okno,sf::IntRect(0,0,200,60),sf::Vector2f(600,15));
    //        points_table = pom_table;

    //        ScoreTable pom2_table(elements_textures,arg_font,okno,sf::IntRect(0,0,100,60),sf::Vector2f(0,15));
    //        money_table = pom2_table;

    //        this->current_platform_texture_rect = texture_rect;
    //        for(int i=0;i<count;i++){
    //            this->platformpointers.emplace_back(this->random_platform(this->difficulty));
    //            this->platformpointers[i]->setTexture(this->elements_textures);
    //            this->platformpointers[i]->setTextureRect(this->current_platform_texture_rect);
    //            if(i==0){
    //                this->platformpointers[i]->setPosition(600,850);
    //            }
    //            else this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
    //            this->platformpointers[i]->SetMiddle();
    //            this->platformpointers[i]->random_coin();
    //        }
    //    }

    //    void draw(){
    //        for(auto &el : platformpointers){
    //            el->draw(okno);
    //        }
    //        points_table.draw();
    //        money_table.draw();
    //        okno->draw(ludek);
    //    }

    //    void create_ludek(){
    //        AnimatedSprite pom_ludek(8);
    //        pom_ludek.setTexture(this->current_hero_texture);
    //        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 1 frame of animation
    //        pom_ludek.add_animation_frame(sf::IntRect(65, 6, 19, 31)); // 2 frame
    //        pom_ludek.add_animation_frame(sf::IntRect(115, 6, 19, 31)); // 3 frame
    //        pom_ludek.add_animation_frame(sf::IntRect(167, 6, 20, 30)); // 4 frame
    //        pom_ludek.add_animation_frame(sf::IntRect(216,6,20,31)); // 5 frame
    //        pom_ludek.add_animation_frame(sf::IntRect(266, 6, 20, 31)); // 6 frame
    //        pom_ludek.add_animation_frame(sf::IntRect(317, 6, 20, 31)); // 7 frame
    //        pom_ludek.add_animation_frame(sf::IntRect(366, 6, 20, 30)); // 8 frame
    //        pom_ludek.setTextureRect(sf::IntRect(14,6,19,31));

    //        ludek = pom_ludek;
    //        ludek.setPosition(600,500);
    //    }

    //    void generate_new(int i){ //podmienia starą platformę na nową random generation
    //        this->platformpointers[i] = this->random_platform(this->difficulty);
    //        this->platformpointers[i]->setTexture(this->elements_textures);
    //        this->platformpointers[i]->setTextureRect(this->current_platform_texture_rect);
    //        this->platformpointers[i]->setPosition(random_position_x(i),random_position_y(i));
    //        this->platformpointers[i]->SetMiddle();
    //        this->platformpointers[i]->random_coin();

    //    }

    //    void step(const sf::Time &elapsed, const sf::Window &okno){

    //        if(points>45){
    //            difficulty=3;
    //        }
    //        else if(points>30){
    //            difficulty=2;;
    //        }
    //        else if(points>15){
    //            difficulty=1;
    //        }

    //        speed+=elapsed.asSeconds()*3;  //przyspieszanie całości z biegiem czasu
    //        last_speed+=elapsed.asSeconds()*3;
    //        ludek.accelerate(elapsed.asSeconds()*3);

    //        for(int i=0;i<int(platformpointers.size());i++){
    //            platformpointers[i]->step_y(elapsed,this->speed);
    //            platformpointers[i]->step(elapsed);

    //            if(platformpointers[i]->Is_working()){
    //                if(ludek.getGlobalBounds().intersects(sf::FloatRect(platformpointers[i]->getGlobalBounds().left,
    //                                                                    platformpointers[i]->getGlobalBounds().top,
    //                                                                    platformpointers[i]->getGlobalBounds().width, 1))){ //zderzenie z górą platformy
    //                    if(ludek.GetVerticalSpeed()>100){
    //                        ludek.SetVerticalSpeed(-600);
    //                        platformpointers[i]->activate();
    //                        if(platformpointers[i]->GetCoin()!=nullptr){
    //                            std::pair<bool,int> pom = platformpointers[i]->GetCoin()->picked(chrono1);
    //                            if(pom.first==0)
    //                            money+=pom.second;
    //                            else{

    //                            }
    //                            money_table.update(money);
    //                        }
    //                    }
    //                }
    //            }
    //            if(platformpointers[i]->getPosition().y>okno.getSize().y){
    //                this->generate_new(i);
    //                points++;
    //                points_table.update(points);
    //            }
    //            else if(platformpointers[i]->getGlobalBounds().top > 0){
    //                platformpointers[i]->ChangeWorkingState(true);
    //            }

    //            if(ludek.getPosition().y>okno.getSize().y){
    //                this->hero_alive=false;
    //            }
    //        }
    //        ludek.step(elapsed,okno);
    //        check_if_too_high(elapsed);
    //    }

    //    void check_if_too_high(const sf::Time &elapsed){ //może by zrobić move zamiast zmieniać prędkość?

    //        if(ludek.getPosition().y < 200){//przesuwanie planszy gdy gracz wyskoczy ponad okno
    //            if(!this->was_too_high){
    //                this->last_speed = this->speed;
    //                this->was_too_high = true;
    //                //this->speed = fabs(ludek.GetVerticalSpeed());
    //                //this->ludek.SetVerticalSpeed(fabs(ludek.GetVerticalSpeed())*2);
    //            }
    //            else{
    //                this->speed+=70*elapsed.asSeconds();
    //                if(ludek.getPosition().y<0){
    //                    ludek.SetVerticalSpeed(ludek.GetVerticalSpeed() + 800*elapsed.asSeconds());
    //                }//this->ludek.SetVerticalSpeed(ludek.GetVerticalSpeed() - 75*elapsed.asSeconds());
    //            }
    //        }
    //        else if(this->was_too_high /*&& ludek.getPosition().y>300*/){
    //            if(this->speed > this->last_speed){
    //                this->speed -=120*elapsed.asSeconds();
    //            }
    //            else {
    //                this->was_too_high = false;
    //                this->speed = this->last_speed;
    //            }
    //        }

    //        //        if(ludek.getPosition().y < 200){//przesuwanie planszy gdy gracz wyskoczy ponad okno
    //        //            if(!this->was_too_high){
    //        //                this->last_speed = this->speed;
    //        //                this->was_too_high = true;
    //        //                //this->speed = fabs(ludek.GetVerticalSpeed());
    //        //                //this->ludek.SetVerticalSpeed(fabs(ludek.GetVerticalSpeed())*2);
    //        //            }
    //        //            else{
    //        //                this->speed+=500*elapsed.asSeconds();
    //        //                //this->ludek.SetVerticalSpeed(ludek.GetVerticalSpeed()+ 2000*elapsed.asSeconds());
    //        //            }
    //        //        }
    //        //        else if(this->was_too_high /*&& ludek.getPosition().y>300*/){
    //        //            if(this->speed > this->last_speed){
    //        //                this->speed -=1500*elapsed.asSeconds();
    //        //            }
    //        //            else {
    //        //                this->was_too_high = false;
    //        //                this->speed = this->last_speed;
    //        //            }
    //        //        }
    //    }

    //    bool Game_alive(){
    //        return this->hero_alive;
    //    }

    //    float random_position_y(int iterator){
    //        float vec_y;
    //        switch (this->difficulty) {
    //        case 0 :  vec_y = rand()%2;break;
    //        case 1 :  vec_y = rand()%6;break;
    //        case 2 :  vec_y = rand()%12;break;
    //        case 3 :  vec_y = rand()%20;break;
    //        default:  vec_y = rand()%2;break;
    //        }

    //        if(iterator==0){
    //            vec_y = platformpointers[platformpointers.size()-1]->getPosition().y - vec_y
    //                    - platformpointers[platformpointers.size()-1]->getGlobalBounds().height;
    //        }
    //        else{
    //            vec_y = platformpointers[iterator-1]->getPosition().y - vec_y
    //                    - platformpointers[platformpointers.size()-1]->getGlobalBounds().height;
    //        }
    //        return vec_y;
    //    }

    //    float random_position_x(int iterator){
    //        float vec_x;
    //        float last_x,last_width;
    //        if(iterator==0){
    //            last_x = platformpointers[platformpointers.size()-1]->getPosition().x;
    //            last_width = platformpointers[platformpointers.size()-1]->getGlobalBounds().width;
    //        }
    //        else{
    //            last_x = platformpointers[iterator-1]->getPosition().x;
    //            last_width = platformpointers[iterator-1]->getGlobalBounds().width;
    //        }

    //        do{
    //            int pluspom = rand()%2;
    //            int pom = rand()%300+100;
    //            if(pluspom==0){
    //                vec_x = last_x - pom - last_width;
    //            }
    //            else{
    //                vec_x = last_x + pom + last_width;
    //            }
    //        }
    //        while(vec_x + platformpointers[iterator]->getGlobalBounds().width > 1200-int(platformpointers[iterator]->getGlobalBounds().width+5)
    //              || vec_x < 5);

    //        return vec_x;
    //    }

    //    void SetPlatformTextureRect (const sf::IntRect &texture_rect){
    //        for(auto &el : this->platformpointers){
    //            el->setTextureRect(texture_rect);
    //            el->SetMiddle();
    //        }
    //    }

    //    void SetDifficulty(int arg_difficulty){
    //        this->difficulty = arg_difficulty;
    //    }

    //    int random_pick(int pro0, int pro1, int pro2, int pro3){
    //        int los=rand()%100;
    //        int prob[100];
    //        int i=0;
    //        while(i<pro0){prob[i]=0;i++;}
    //        while(i<pro1+pro0){prob[i]=1;i++;}
    //        while(i<pro2+pro1+pro0){prob[i]=2;i++;}
    //        while(i<pro3+pro2+pro1+pro0){prob[i]=3;i++;}
    //        return prob[los];
    //    }

    //    Platform *random_platform(const int &difficulty){

    //        int num,speed,boundary=rand()%40+65,time_=5;
    //        if(difficulty==1){
    //            num=this->random_pick(60,40,0,0);
    //            speed = rand()%30+20;
    //        }
    //        else if(difficulty==2){
    //            num=this->random_pick(20,40,25,15);
    //            speed = rand()%20+40;
    //            time_ = rand()%2+3;
    //        }
    //        else if(difficulty==3){
    //            num=this->random_pick(10,35,30,25);
    //            speed = rand()%20+50;
    //            time_ = rand()%2+1;
    //        }
    //        else num=0;
    //        Platform* rand_plat;
    //        switch(num){
    //        case 1: rand_plat = new MovingPlatform(speed,boundary,elements_textures);break;
    //        case 2: rand_plat = new TimedPlatform(time_,elements_textures);break;
    //        case 3: rand_plat = new TimedMovingPlatform(speed,boundary,time_,elements_textures);break;
    //        default: rand_plat = new Platform(elements_textures);break;
    //        }
    //        return rand_plat;
    //    }
};

#endif // MINDGAMEELEMENTS_H
