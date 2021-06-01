#ifndef FIGHTING_GAME_ELEMENTS_H
#define FIGHTING_GAME_ELEMENTS_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <arrow.h>
#include <fightinggameanimatedsprite.h>
#include <targetplatform.h>
#include <Chronometer.hpp>
#include <scoretable.h>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

class fighting_game_elements
{
private:
    int difficulty=0;
    int platform_count=2;
    sf::Texture elements_textures;
    sf::IntRect platform_texture_rect;
    sf::Texture hero_texture;
    const sf::Font *font;
    sf::RenderWindow *okno;
    sftools::Chronometer *chrono;
    int character_size = 30;
    std::string str_equation;
    FightingGameAnimatedSprite ludek;
    int good_points = 0;
    int how_many_tasks;
    int current_task_num = 0;
    sf::Time max_task_time = sf::seconds(15);
    sf::Time current_task_time = sf::Time::Zero;
    sf::Text start_text;
    bool started = false;
    bool countdown_started = false;
    std::vector<ScoreTable*> scoretables;
public:
    fighting_game_elements(){};
    fighting_game_elements(const int &arg_difficulty,const sf::Texture &arg_elements_textures, const sf::IntRect &arg_platform_texture_rect,
                           const sf::Texture &arg_hero_texture, const sf::Font *arg_font, sf::RenderWindow *arg_okno,
                           sftools::Chronometer *arg_chrono){
        this->difficulty = arg_difficulty;
        this->elements_textures = arg_elements_textures;
        this->platform_texture_rect = arg_platform_texture_rect;
        this->hero_texture = arg_hero_texture;
        this->font = arg_font;
        this->okno = arg_okno;
        this->chrono = arg_chrono;
        this->how_many_tasks = (rand()%2+1)*(this->difficulty+1);

        create_ludek();

        int text_size = 40;
        sf::IntRect back_score_rect(0,0,200,80);
        ScoreTable *pom_table = new ScoreTable(elements_textures,font, okno,back_score_rect,
                                               sf::Vector2f(okno->getSize().x/8-back_score_rect.width/2,15),
                                               sf::Vector2f(okno->getSize().x/8,15),
                                               std::to_string(current_task_num)+'/'+std::to_string(how_many_tasks),
                                               text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);

        text_size = 40;
        back_score_rect = sf::IntRect(0,0,200,80);
        pom_table = new ScoreTable(elements_textures,font, okno,back_score_rect,
                                   sf::Vector2f(okno->getSize().x-okno->getSize().x/4-back_score_rect.width/2,15),
                                   sf::Vector2f(okno->getSize().x-okno->getSize().x/4,15),
                                   "Punkty: " + std::to_string(good_points),
                                   text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);

        text_size = 40;
        back_score_rect = sf::IntRect(0,0,150,80);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << (max_task_time-current_task_time).asSeconds();

        pom_table = new ScoreTable(elements_textures,font, okno,back_score_rect,
                                   sf::Vector2f(okno->getSize().x/8 + 200-back_score_rect.width/2,15),
                                   sf::Vector2f(okno->getSize().x/8 + 200,15),
                                   stream.str(),
                                   text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);

        sf::Text pom_text(L"Naciśnij klawisz ENTER by rozpocząć grę",*font,70);
        pom_text.setPosition(okno->getSize().x/2 - pom_text.getGlobalBounds().width/2,okno->getSize().y/2-70);
        pom_text.setFillColor(sf::Color(200,200,200,128));
        this->start_text = pom_text;

        //new_task();
    };

    bool tasks_finished(){
        return current_task_num-1==how_many_tasks;
    }

    void new_task(){

        current_task_time = sf::Time::Zero;
        current_task_num++;

        scoretables.erase(scoretables.begin()+3,scoretables.end());

        generate_scoretables();

        ludek.setPosition(600,500);

        scoretables[0]->update(std::to_string(current_task_num)+'/'+std::to_string(how_many_tasks));
        scoretables[0]->settextonmiddle(-40);
        scoretables[1]->update("Punkty: " + std::to_string(good_points));
        scoretables[1]->settextonmiddle(-40);


    }

    void step(const sf::Time &elapsed){

        if(started){

        }
        else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
                countdown_started=true;
            }
            if(countdown_started){
                current_task_time+=elapsed;
                if(current_task_time<sf::seconds(1)){
                    start_text.setString("3");
                    start_text.setCharacterSize(100);
                    start_text.setPosition(okno->getSize().x/2 -
                                           start_text.getGlobalBounds().width/2,
                                           okno->getSize().y/2-start_text.getCharacterSize());
                }
                else if(current_task_time<sf::seconds(2)){
                    start_text.setString("2");
                }
                else if(current_task_time<sf::seconds(3)){
                    start_text.setString("1");
                }
                else{
                    this->started=true;
                    current_task_time=sf::Time::Zero;
                }
            }
        }

    }

    void create_ludek(){
        FightingGameAnimatedSprite pom_ludek(8,800,100);
        pom_ludek.setTexture(this->hero_texture);
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 1 frame of animation
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 2 frame
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 3 frame
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 4 frame
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 5 frame
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 6 frame
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 7 frame
        pom_ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 8 frame
        pom_ludek.setTextureRect(sf::IntRect(14,6,19,31));

        ludek = pom_ludek;
        ludek.setPosition(5,okno->getSize().y-ludek.getGlobalBounds().height-5);
    }

    void draw(){
        if(!started){
            okno->draw(start_text);
        }
        else{
            for(auto &el : scoretables){
                el->draw();
            }
            okno->draw(ludek);
        }
    }

    void generate_scoretables(){
        switch (this->difficulty) {
        case 0:platform_count=2;break;
        case 1:platform_count=rand()%2+2;break;
        case 2:platform_count=3;break;
        case 3:platform_count=rand()%2+3;break;
        }

        generate_equation_and_answers();

        for(int i=0;i<platform_count;i++){
            //scoretables.emplace_back(generate_platform(i));
        }

        int text_size = 50;
        sf::IntRect back_equation_rect(0,0,450,80);
        ScoreTable *pom_table = new ScoreTable(elements_textures,font, okno,back_equation_rect,
                                               sf::Vector2f(okno->getSize().x/2-back_equation_rect.width/2,15),sf::Vector2f(okno->getSize().x/2,15),str_equation,text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);
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
        this->str_equation = stream.str();

        //        for(int i=0;i<platform_count;i++){//dodaje dobre rozwiązanie lub losuje złe niewylosowane wcześniej
        //            std::stringstream answer_stream;
        //            if(i==solution_place){
        //                answer_stream << std::fixed << std::setprecision(2) << c;
        //                answers.emplace_back(answer_stream.str(),true);
        //            }
        //            else{
        //                float addon;
        //                do{
        //                    addon = rand()%10+1;
        //                    int mnoznik=rand()%2;
        //                    if(mnoznik==0){
        //                        addon=-addon;
        //                    }
        //                }
        //                while(std::find_if(answers.begin(),answers.end(),[&c,&addon]
        //                                   (const std::pair<std::string,bool> &el){return el.first==std::to_string(c+addon);})!=answers.end());

        //                answer_stream << std::fixed << std::setprecision(2) << c+addon;
        //                answers.emplace_back(answer_stream.str(),false);
        //            }
        //        }
        //    }

        //    ScoreTable* generate_platform(int current_count){//generuje platformę z równaniem losowo wygenerowanym; platformy w równej odległości
        //        sf::Vector2f plat_pos(float(okno->getSize().x)/this->platform_count*(current_count+1.0/2)-this->platform_texture_rect.width/2,400);
        //        ScoreTable *pom_platform = new PlatformWithEquation(elements_textures,font,okno,platform_texture_rect,plat_pos,plat_pos,
        //                                                            answers[current_count].first,character_size,answers[current_count].second);
        //        return pom_platform;

    }

    std::pair<int,int> summary_data(){
        std::pair<int,int> parka(good_points,how_many_tasks);
        return parka;
    }

};
#endif // FIGHTING_GAME_ELEMENTS_H
