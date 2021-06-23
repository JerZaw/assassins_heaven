#ifndef SCORESAVINGELEMENT_H
#define SCORESAVINGELEMENT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <read_textures.h>

class ScoreSavingElement
{
private:
    std::vector<std::pair<std::string,int>> highscores;
    sf::RenderWindow *okno;
    sf::RectangleShape background_rect;
    std::vector<sf::Drawable*> drawables;
    sf::Text text_1,text_2,text_3,text_4;
    sf::Font font1;
    sf::Sprite SubmitButton,QuitButton;
    sf::Texture button_texture;
    sf::RectangleShape typing_rect;
    sf::Text name_text;
    bool name_field_activated = false;
    int score;
public:
    ScoreSavingElement(const sf::Font font, sf::RenderWindow *arg_okno):
    okno(arg_okno),font1(font){

        background_rect.setSize(sf::Vector2f(1300,600));
        background_rect.setFillColor(sf::Color(200,200,200,128));
        background_rect.setPosition(okno->getSize().x/2 - background_rect.getGlobalBounds().width/2,okno->getSize().y/2 - background_rect.getGlobalBounds().height/2);
        drawables.emplace_back(&background_rect);

        text_1.setCharacterSize(70);
        text_1.setString("Score Saving");
        text_1.setFont(font1);
        text_1.setPosition(okno->getSize().x/2 - text_1.getGlobalBounds().width/2,okno->getSize().y/4 -50);
        text_1.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_1);

        text_2.setCharacterSize(50);
        text_2.setString("Type your name below and click SUBMIT");
        text_2.setFont(font1);
        text_2.setPosition(okno->getSize().x/2 - text_2.getGlobalBounds().width/2,okno->getSize().y/3 -30);
        text_2.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_2);

        text_3.setCharacterSize(40);
        text_3.setString("WARNING there can only be one score under one nickname");
        text_3.setFont(font1);
        text_3.setPosition(okno->getSize().x/2 - text_3.getGlobalBounds().width/2,okno->getSize().y/3 + 70);
        text_3.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_3);

        text_4.setCharacterSize(25);
        text_4.setString("If you don't want to save your score click QUIT");
        text_4.setFont(font1);
        text_4.setPosition(okno->getSize().x/2 - text_4.getGlobalBounds().width/2,okno->getSize().y/3 + 140);
        text_4.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_4);

        typing_rect.setSize(sf::Vector2f(500,50));
        typing_rect.setFillColor(sf::Color::White);
        typing_rect.setPosition(okno->getSize().x/2 - typing_rect.getGlobalBounds().width/2,okno->getSize().y/2 + 50);
        drawables.emplace_back(&typing_rect);

        name_text.setCharacterSize(30);
        name_text.setString("type your name here");
        name_text.setFont(font1);
        name_text.setPosition(typing_rect.getGlobalBounds().left + 10,
                              typing_rect.getGlobalBounds().top + typing_rect.getGlobalBounds().height/2 - name_text.getGlobalBounds().height);
        name_text.setFillColor(sf::Color(128,128,128,250));
        drawables.emplace_back(&name_text);

        std::string str_pom;
        std::ifstream odczyt("assets/highscores.txt");
        while(!odczyt.eof()){
            odczyt >> str_pom;
            highscores.emplace_back(str_pom.substr(0,str_pom.find('-')),
                                    std::stoi(str_pom.substr(str_pom.find('-')+1,str_pom.size()-1)));
        }
        odczyt.close();

        this->create_buttons(menu_button_textures);
    }

    void step(const sf::Event &event){

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
            if(SubmitButton.getGlobalBounds().contains(mouse_position) && name_field_activated){
                click.play();
                if(name_text.getString()!=""){
                    std::pair<std::string, int> parka(name_text.getString(),score);
                    this->AddScore(parka);
                    okno->close();
                }
                else{
                    name_text.setString("TYPE YOUR NAME HERE");
                    name_text.setFillColor(sf::Color::Red);
                    name_field_activated = false;
                }
            }
            else if(QuitButton.getGlobalBounds().contains(mouse_position)){
                click.play();
                okno->close();
            }
            else if(typing_rect.getGlobalBounds().contains(mouse_position)){
                activate_name_field();
            }
        }

        if(event.type == sf::Event::TextEntered && name_field_activated){
            if(event.text.unicode == 8){
                name_text.setString(name_text.getString().substring(0,name_text.getString().getSize()-1));
            }
            else if(name_text.getString().getSize()<10 && event.text.unicode != 32){
                name_text.setString(name_text.getString() + event.text.unicode);
            }
        }

        sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
        if(SubmitButton.getGlobalBounds().contains(mouse_position)){
            SubmitButton.setTextureRect(sf::IntRect(489,732,402,174));
        }else{
            SubmitButton.setTextureRect(sf::IntRect(0,732,402,174));
            if(QuitButton.getGlobalBounds().contains(mouse_position)){
                QuitButton.setTextureRect(sf::IntRect(489,549,402,174));
            }
            else{
                QuitButton.setTextureRect(sf::IntRect(0,549,402,174));
            }
        }
    }

    void SetScore(const int &arg_score){
        this->score = arg_score;
    }

    void activate_name_field(){
        name_text.setFillColor(sf::Color(0,0,0,250));
        name_text.setString("");
        name_field_activated = true;
    }

    void draw(){
        for(auto &el : drawables){
            okno->draw(*el);
        }
    }


    void create_buttons(const sf::Texture &texture){
        this->button_texture = texture;
        SubmitButton.setTexture(button_texture);
        SubmitButton.setTextureRect(sf::IntRect(0,732,402,174));
        SubmitButton.setPosition(okno->getSize().x/4+50 - SubmitButton.getGlobalBounds().width/2, okno->getSize().y/2 + 200);
        drawables.emplace_back(&SubmitButton);
        QuitButton.setTexture(button_texture);
        QuitButton.setTextureRect(sf::IntRect(0,549,402,174));
        QuitButton.setPosition(okno->getSize().x/4*3-50 - QuitButton.getGlobalBounds().width/2, okno->getSize().y/2 + 200);
        drawables.emplace_back(&QuitButton);
    }

    void AddScore(const std::pair<std::string,int> &parka){
        auto it = std::find_if(highscores.begin(),highscores.end(),
                               [&parka](const std::pair<std::string,int> &el_pair){return parka.first == el_pair.first;});
        if(it==highscores.end()){
            highscores.emplace_back(parka);
        }
        else{
            it->second=score;
        }
    }

    ~ScoreSavingElement(){

//        for(auto &el: drawables){
//            delete el;
//        }

        std::sort(highscores.begin(),highscores.end(),
                  [](const std::pair<std::string,int> &el_pair1,const std::pair<std::string,int> &el_pair2)
        {return el_pair1.second > el_pair2.second;});

        std::ofstream zapis("assets/highscores.txt",std::ios::trunc);
        for(unsigned long long i=0;i<highscores.size();i++){
            zapis << highscores[i].first <<'-'<<highscores[i].second;
            if(i<highscores.size()-1){
                zapis<<std::endl;
            }
        }
        zapis.close();
    }
};

#endif // SCORESAVINGELEMENT_H
