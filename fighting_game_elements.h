#ifndef FIGHTING_GAME_ELEMENTS_H
#define FIGHTING_GAME_ELEMENTS_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <arrow.h>
#include <fightinggameanimatedsprite.h>
#include <Chronometer.hpp>
#include <scoretable.h>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <target.h>
#include <read_textures.h>

class fighting_game_elements
{
private:
    int difficulty=0;
    int target_count=2;
    sf::Texture elements_textures;
    sf::IntRect platform_texture_rect;
    sf::Texture my_hero_texture;
    const sf::Font *font;
    sf::RenderWindow *okno;
    sftools::Chronometer *chrono;
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
    std::vector<Arrow*> arrows;
    int max_arrows_count = 5;
    int current_arrow_counter = 0;
    std::vector<Target*> targets;
    bool single_finished = false;
    int single_targets_hit = 0;
    int max_single_points = 0;
public:
    fighting_game_elements(){};
    fighting_game_elements(const int &arg_difficulty,const sf::IntRect &arg_platform_texture_rect,
                           sf::RenderWindow *arg_okno,
                           sftools::Chronometer *arg_chrono){
        this->difficulty = arg_difficulty;
        this->elements_textures = fighting_elements_textures;
        this->platform_texture_rect = arg_platform_texture_rect;
        this->my_hero_texture = hero_texture;
        this->font = &font_comica_bold;
        this->okno = arg_okno;
        this->chrono = arg_chrono;
        this->how_many_tasks = (rand()%2+1)*(this->difficulty+1);

        for(int i=0;i<max_arrows_count;i++){
            arrows.emplace_back(nullptr);
        }

        for(int i=0;i<10;i++){//maks 10 celów
            targets.emplace_back(nullptr);
        }

        create_ludek();

        int text_size = 40;
        sf::IntRect back_score_rect(275,246,200,80);
        ScoreTable *pom_table = new ScoreTable(scoreboards_textures,font, okno,back_score_rect,
                                               sf::Vector2f(okno->getSize().x/8-back_score_rect.width/2,15),
                                               sf::Vector2f(okno->getSize().x/8,15),
                                               std::to_string(current_task_num)+'/'+std::to_string(how_many_tasks),
                                               text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);

        text_size = 40;
        back_score_rect = sf::IntRect(2,328,250,80);
        pom_table = new ScoreTable(scoreboards_textures,font, okno,back_score_rect,
                                   sf::Vector2f(okno->getSize().x-okno->getSize().x/4-back_score_rect.width/2,15),
                                   sf::Vector2f(okno->getSize().x-okno->getSize().x/4,15),
                                   "Points: " + std::to_string(good_points),
                                   text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);

        text_size = 40;
        back_score_rect = sf::IntRect(101,246,150,80);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << (max_task_time-current_task_time).asSeconds();

        pom_table = new ScoreTable(scoreboards_textures,font, okno,back_score_rect,
                                   sf::Vector2f(okno->getSize().x/8 + 200-back_score_rect.width/2,15),
                                   sf::Vector2f(okno->getSize().x/8 + 200,15),
                                   stream.str(),
                                   text_size);
        pom_table->settextonmiddle(-text_size);
        scoretables.emplace_back(pom_table);

        sf::Text pom_text(L"Press ENTER to start the game",*font,70);
        pom_text.setPosition(okno->getSize().x/2 - pom_text.getGlobalBounds().width/2,okno->getSize().y/2-70);
        pom_text.setFillColor(sf::Color(0,0,0,128));
        this->start_text = pom_text;

        new_task();
    };

    bool tasks_finished(){
        return current_task_num-1==how_many_tasks;
    }

    void new_task(){

        current_task_time = sf::Time::Zero;
        current_task_num++;

        for(unsigned long long i=0;i<arrows.size();i++){
            delete arrows[i];
            arrows[i] = nullptr;
        }

        for(unsigned long long i=0;i<targets.size();i++){
            delete targets[i];
            targets[i] = nullptr;
        }

        generate_targets();

        scoretables[0]->update(std::to_string(current_task_num)+'/'+std::to_string(how_many_tasks));
        scoretables[0]->settextonmiddle(-40);
        scoretables[1]->update("Punkty: " + std::to_string(good_points));
        scoretables[1]->settextonmiddle(-40);

        single_finished = false;
        single_targets_hit = 0;

        if(!tasks_finished()){
            max_single_points+=target_count;
        }
    }

    void step(const sf::Time &elapsed){

        if(started){ //pętla czasowa gry
            if(single_finished){
                sf::sleep(sf::seconds(0.6));
                chrono->add(-chrono->getElapsedTime());
                new_task();
            }
            else{

                current_task_time+=elapsed;

                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << (max_task_time-current_task_time).asSeconds();
                scoretables[2]->update(stream.str());

                if(current_task_time>=max_task_time){
                    single_finished = true;
                }
                else if(single_targets_hit == target_count){
                    single_finished = true;
                    good_points+=5; //+5 punktów za zestrzelenie wszystkich celów na poziomie
                }
                else{
                    ludek.step(elapsed);
                    if(ludek.if_shot_called()){
                        for(int i=0;i<max_arrows_count;i++){ //szukanie wolnego miejsca w wektorze na strzałę
                            if(arrows[i]==nullptr){
                                current_arrow_counter = i;
                                break;
                            }
                            else{
                                current_arrow_counter = -1;
                            }
                        }
                        if(current_arrow_counter!=-1){ //jeśli znalazło miejsce dodaje nową strzałę i strzela
                            arrows[current_arrow_counter]=new Arrow(ludek.shoot(),elements_textures,sf::IntRect(765,421,160,32));
                            arrows[current_arrow_counter]->setScale(0.5,0.5);
                        }
                    }
                    for(auto &el:arrows){ //przesuwanie strzał i sprawdzanie czy uderzają w cele
                        if(el!=nullptr){
                            el->step(elapsed);

                            if(el->getGlobalBounds().left >= okno->getSize().x ||//usuwanie strzały gdy wypadnie poza planszę
                                    el->getGlobalBounds().top >= okno->getSize().y){
                                delete el;
                                el = nullptr;
                                break;
                            }

                            for(int i=0;i<target_count;i++){
                                if(el->getGlobalBounds().intersects(targets[i]->getGlobalBounds()) && !targets[i]->if_hit()){
                                    good_points++; //punkt za każde trafienie, usuwanie strzały po trafieniu
                                    single_targets_hit++;
                                    targets[i]->hit();
                                    delete el;
                                    el = nullptr;
                                    scoretables[1]->update("Punkty: " + std::to_string(good_points));
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        else{ //odliczanie przed grą
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && countdown_started==false){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
                countdown_started=true;
                countdown.play();
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
        FightingGameAnimatedSprite pom_ludek(10,40,2,okno);
        pom_ludek.setTexture(this->my_hero_texture);

        pom_ludek.setTextureRect(sf::IntRect(1,1415,232,439));
        pom_ludek.setScale(0.4,0.4);

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
            for(auto &el : targets){
                if(el!=nullptr){
                    okno->draw(*el);
                }
            }
            for(auto &el : arrows){
                if(el!=nullptr){
                    okno->draw(*el);
                }
            }
            ludek.draw_all();
        }
    }

    void generate_targets(){
        switch (this->difficulty) {
        case 0:target_count=2;break;
        case 1:target_count=rand()%2+2;break;
        case 2:target_count=3;break;
        case 3:target_count=rand()%2+3;break;
        }

        for(int i=0;i<target_count;i++){
            targets[i] = new Target(generate_target());
            generate_position(i);
        }
    }

    void generate_position(const int &count){
        sf::Vector2f pompoz;
        do{//odstępy od granic i od innych celów
            pompoz.x = rand()%(int(okno->getSize().x-200-targets[count]->getGlobalBounds().width))+200;//x odstęp od lewej 200
            pompoz.y = rand()%(int(okno->getSize().y-150-targets[count]->getGlobalBounds().height))+100;//y odstęp od góry 100 i dołu 50
            targets[count]->setPosition(pompoz);
        }
        while(check_target_intersection(count));
    }

    bool check_target_intersection(const int &count){
        if(count==0){return false;}

        for(int i=0;i<count;i++){
            if(targets[i]->getGlobalBounds().intersects(targets[count]->getGlobalBounds())){
                return true;
            }
        }
        return false;
    }

    Target generate_target(){
        float scale;
        switch (difficulty) {
        case 0:scale = 1;break;
        case 1:scale = 1-rand()%2/10.0 -0.1;break;
        case 2:scale = 1-rand()%3/10.0 -0.3;break;
        case 3:scale = 1-rand()%3/10.0 -0.5;break;
        }
        return Target(scale,elements_textures,sf::IntRect(178,465,129,129));
    }

    std::pair<int,int> summary_data(){
        std::pair<int,int> parka(good_points,max_single_points + 5*how_many_tasks);
        return parka;
    }

};
#endif // FIGHTING_GAME_ELEMENTS_H
