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
#include <scoretable.h>
#include <mindgameanimatedsprite.h>
#include <read_textures.h>

enum Answer{NOANSWER=-1,RIGHT=1,WRONG = 0};

class MindGameElements
{
private:
    std::vector<ScoreTable*> platforms;
    std::vector<std::pair<std::string,bool>> answers;
    int difficulty=0;
    int platform_count=2;
    sf::Texture elements_textures;
    sf::IntRect platform_texture_rect;
    const sf::Font *font;
    sf::RenderWindow *okno;
    sftools::Chronometer *chrono;
    int character_size = 30;
    std::string str_equation;
    MindGameAnimatedSprite ludek;
    float ludek_last_horizontal_speed;
    Answer answer = WRONG;
    int good_points = 0;
    int how_many_tasks;
    int current_task_num = 0;
    sf::Time max_task_time = sf::seconds(15);
    sf::Time current_task_time;
    sf::Text start_text;
    bool started = false;
    bool countdown_started = false;
public:
    MindGameElements(){};
    MindGameElements(const int &arg_difficulty, const sf::IntRect &arg_platform_texture_rect,
                     sf::RenderWindow *arg_okno, sftools::Chronometer *arg_chrono){
        this->difficulty = arg_difficulty;
        this->elements_textures = jumping_elements_textures;
        this->platform_texture_rect = arg_platform_texture_rect;
        this->font = &font_comica_bold;
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
        platforms.emplace_back(pom_table);

        text_size = 40;
        back_score_rect = sf::IntRect(0,0,200,80);
        pom_table = new ScoreTable(elements_textures,font, okno,back_score_rect,
                                   sf::Vector2f(okno->getSize().x-okno->getSize().x/4-back_score_rect.width/2,15),
                                   sf::Vector2f(okno->getSize().x-okno->getSize().x/4,15),
                                   "Punkty: " + std::to_string(good_points),
                                   text_size);
        pom_table->settextonmiddle(-text_size);
        platforms.emplace_back(pom_table);

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
        platforms.emplace_back(pom_table);

        sf::Text pom_text(L"Naciśnij klawisz ENTER by rozpocząć grę",*font,70);
        pom_text.setPosition(okno->getSize().x/2 - pom_text.getGlobalBounds().width/2,okno->getSize().y/2-70);
        pom_text.setFillColor(sf::Color(200,200,200,128));
        this->start_text = pom_text;

        new_task();
    };

    bool tasks_finished(){
        return current_task_num-1==how_many_tasks;
    }

    void new_task(){

        current_task_time = sf::Time::Zero;
        current_task_num++;
        good_points+=answer;
        answer = NOANSWER;

        for(unsigned long long i=3;i<platforms.size();i++){
            delete platforms[i];
        }
        platforms.erase(platforms.begin()+3,platforms.end());
        answers.clear();

        generate_platforms();

        ludek.setPosition(600,500);

        platforms[0]->update(std::to_string(current_task_num)+'/'+std::to_string(how_many_tasks));
        platforms[0]->settextonmiddle(-40);
        platforms[1]->update("Punkty: " + std::to_string(good_points));
        platforms[1]->settextonmiddle(-40);


    }

    void step(const sf::Time &elapsed){

        if(started){

            if(answer!=NOANSWER){
                sf::sleep(sf::seconds(0.6));
                chrono->add(-chrono->getElapsedTime());
                new_task();
            }
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << (max_task_time-current_task_time).asSeconds();
            platforms[2]->update(stream.str());

            current_task_time+=elapsed;
            ludek.step(elapsed,*okno);

            if(current_task_time>=max_task_time){
                answer = WRONG;
            }

            for(auto &el : platforms){ //aktywacja przy skoku od góry + zderzenia
                if(ludek.getGlobalBounds().
                        intersects(sf::FloatRect(el->GetBackground()->getGlobalBounds().left,
                                                 el->GetBackground()->getGlobalBounds().top+0.1,
                                                 0.1,
                                                 el->GetBackground()->getGlobalBounds().height-0.1))){
                    ludek.move(-(ludek.GetHorizontalSpeed()+10)*elapsed.asSeconds(),0);
                    this->ludek_last_horizontal_speed = ludek.GetHorizontalSpeed();
                    ludek.SetHorizontalSpeed(0);
                }
                else if(ludek.getGlobalBounds().
                        intersects(sf::FloatRect(el->GetBackground()->getGlobalBounds().left + el->GetBackground()->getGlobalBounds().width - 0.1,
                                                 el->GetBackground()->getGlobalBounds().top+0.1,
                                                 0.1,
                                                 el->GetBackground()->getGlobalBounds().height-0.1))){
                    ludek.move((ludek.GetHorizontalSpeed()+10)*elapsed.asSeconds(),0);
                    this->ludek_last_horizontal_speed = ludek.GetHorizontalSpeed();
                    ludek.SetHorizontalSpeed(0);
                }
                else if(ludek.GetHorizontalSpeed()==0){
                    ludek.SetHorizontalSpeed(this->ludek_last_horizontal_speed);
                }

                if(ludek.getGlobalBounds().
                        intersects(sf::FloatRect(el->GetBackground()->getGlobalBounds().left,
                                                 el->GetBackground()->getGlobalBounds().top,
                                                 el->GetBackground()->getGlobalBounds().width, 0.1))){
                    if(el->picked()){
                        answer = RIGHT;
                    }
                    else{
                        answer = WRONG;
                    }
                    ludek.SetVerticalSpeed(0);
                }
                else if(ludek.getGlobalBounds().
                        intersects(sf::FloatRect(el->GetBackground()->getGlobalBounds().left,
                                                 el->GetBackground()->getGlobalBounds().top + el->GetBackground()->getGlobalBounds().height,
                                                 el->GetBackground()->getGlobalBounds().width, -0.1))){
                    ludek.SetVerticalSpeed(1);
                }
            }
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
        MindGameAnimatedSprite pom_ludek(10,100,400,2600,-1200);
        pom_ludek.setTexture(hero_texture);
        //JUMPING TEXTURE RECTANGLES
        pom_ludek.add_pom_animation_frame(sf::IntRect(0,14,282,437)); // 1 frame of animation
        pom_ludek.add_pom_animation_frame(sf::IntRect(290, 4, 266, 461)); // 2 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(567, 2, 253, 433)); // 3 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(834, 2, 253, 432)); // 4 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(1134,2,253,432)); // 5 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(1402, 2,253,432)); // 6 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(1677, 2, 274, 425)); // 7 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(1980, 0, 301, 420)); // 8 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(2321, 0, 329, 412)); // 9 frame
        pom_ludek.add_pom_animation_frame(sf::IntRect(2685, 0, 329, 412)); // 10 frame

        //RUNNING TEXTURE RECTANGLES
        pom_ludek.add_animation_frame(sf::IntRect(0,482,328,433)); // 1 frame of animation
        pom_ludek.add_animation_frame(sf::IntRect(330, 476, 323, 450)); // 2 frame
        pom_ludek.add_animation_frame(sf::IntRect(655, 472, 321, 446)); // 3 frame
        pom_ludek.add_animation_frame(sf::IntRect(983, 475, 353, 422)); // 4 frame
        pom_ludek.add_animation_frame(sf::IntRect(1340,482,354,427)); // 5 frame
        pom_ludek.add_animation_frame(sf::IntRect(1694, 482,328,427)); // 6 frame
        pom_ludek.add_animation_frame(sf::IntRect(2031, 476, 323, 448)); // 7 frame
        pom_ludek.add_animation_frame(sf::IntRect(2357, 472, 316, 431)); // 8 frame
        pom_ludek.add_animation_frame(sf::IntRect(2678, 474, 318, 405)); // 9 frame
        pom_ludek.add_animation_frame(sf::IntRect(2998, 482, 328, 422)); // 10 frame

        pom_ludek.setScale(0.2,0.2);
        pom_ludek.setTextureRect(sf::IntRect(0,482,328,433));//first frame

        ludek=pom_ludek;
    }

    void draw(){
        if(!started){
            okno->draw(start_text);
        }
        else{
            for(auto &el : platforms){
                el->draw();
            }
            okno->draw(ludek);
        }
    }

    void generate_platforms(){
        switch (this->difficulty) {
        case 0:platform_count=2;break;
        case 1:platform_count=rand()%2+2;break;
        case 2:platform_count=3;break;
        case 3:platform_count=rand()%2+3;break;
        }

        generate_equation_and_answers();

        for(int i=0;i<platform_count;i++){
            platforms.emplace_back(generate_platform(i));
        }

        int text_size = 50;
        sf::IntRect back_equation_rect(0,0,450,80);
        ScoreTable *pom_table = new ScoreTable(elements_textures,font, okno,back_equation_rect,
                                               sf::Vector2f(okno->getSize().x/2-back_equation_rect.width/2,15),sf::Vector2f(okno->getSize().x/2,15),str_equation,text_size);
        pom_table->settextonmiddle(-text_size);
        platforms.emplace_back(pom_table);
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
                a=rand()%10+1;b=rand()%10+1;
            }
            break;
        case 3:operation_type=operation(rand()%4);
            if(operation_type==DODAWANIE || operation_type==ODEJMOWANIE){
                a=rand()%100;b=rand()%100;
            }
            else if(operation_type==MNOZENIE){
                a=rand()%49+1;b=rand()%10+1;
            }
            else{
                do{
                a=rand()%99+1;b=rand()%9+1;
                }
                while(int(a)%int(b)!=0);
            }
            break;
        }

        std::stringstream stream;
        stream << std::fixed << std::setprecision(0) << a;

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

        stream << std::fixed << std::setprecision(0) << b << " = ";
        this->str_equation = stream.str();

        for(int i=0;i<platform_count;i++){//dodaje dobre rozwiązanie lub losuje złe niewylosowane wcześniej
            std::stringstream answer_stream;
            if(i==solution_place){
                answer_stream << std::fixed << std::setprecision(0) << c;
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

                answer_stream << std::fixed << std::setprecision(0) << c+addon;
                answers.emplace_back(answer_stream.str(),false);
            }
        }
    }

    ScoreTable* generate_platform(int current_count){//generuje platformę z równaniem losowo wygenerowanym; platformy w równej odległości
        sf::Vector2f plat_pos(float(okno->getSize().x)/this->platform_count*(current_count+1.0/2)-this->platform_texture_rect.width/2,400);
        ScoreTable *pom_platform = new PlatformWithEquation(elements_textures,font,okno,platform_texture_rect,plat_pos,plat_pos,
                                                            answers[current_count].first,character_size,answers[current_count].second);
        return pom_platform;

    }

    std::pair<int,int> summary_data(){
        std::pair<int,int> parka(good_points,how_many_tasks);
        return parka;
    }

};

#endif // MINDGAMEELEMENTS_H
