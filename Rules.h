#ifndef RULES_H
#define RULES_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <read_textures.h>

class Rules
{
private:
    sf::RenderWindow *okno;
    sf::Font font1;
    sf::Sprite QuitButton;
    sf::Texture button_texture;
    std::vector<sf::Text> rules;
    sf::Clock clock;
    sf::Sprite background;
    bool mouse_released = false;
public:
    Rules(const sf::Font &font, sf::RenderWindow *arg_okno):
    okno(arg_okno),font1(font){

        background.setTexture(rules_back);
        background.setTextureRect(sf::IntRect(0,0,okno->getSize().x,okno->getSize().y));

        sf::Text text_1("",font1,70);
        text_1.setPosition(okno->getSize().x/2 - text_1.getGlobalBounds().width/2,30);
        text_1.setFillColor(sf::Color(0,0,0,250));
        rules.emplace_back(text_1);

        for(int i=1;i<11;i++){
            rules.emplace_back(sf::Text("",font1,30));
            rules[i].setFillColor(sf::Color::Black);
        }

        rules[1].setString(L"Game objective is to gain the highest");
        rules[2].setString(L"score possible by jumping on the platforms");
        rules[3].setString(L"left/right arrows move you accordingly");
        rules[4].setString(L"you can also earn money by collecting");
        rules[5].setString(L"coins appearing on the platforms");
        rules[6].setString(L"when assassin's symbol is collected minigame will start");
        rules[7].setString(L"1. mindgame: jump on the platform with the right answer");
        rules[8].setString(L"2. fightinggame: shoot all the targets");
        rules[9].setString(L"after the minigame ends you come back to the main game");
        rules[10].setString(L"use money to buy boosts at the start of each new game");

        rules[1].setPosition(okno->getSize().x/2 - rules[1].getGlobalBounds().width/2,okno->getSize().y/5 + 50);
        for(unsigned long long i=2;i<rules.size();i++){
            rules[i].setPosition(okno->getSize().x/2 - rules[i].getGlobalBounds().width/2,rules[i-1].getPosition().y + 40);
        }
        clock.restart();

        create_buttons(menu_button_textures);
    }

    void step(){
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            mouse_released = true;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_released){
            sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
            if(QuitButton.getGlobalBounds().contains(mouse_position)){
                click.play();
                okno->close();
            }
        }

        sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
        if(QuitButton.getGlobalBounds().contains(mouse_position)){
            QuitButton.setTextureRect(sf::IntRect(489,549,402,174));
        }
        else{
            QuitButton.setTextureRect(sf::IntRect(0,549,402,174));
        }
    }

    void draw(){
        okno->draw(background);
        for(auto &el : rules){
            okno->draw(el);
        }
        okno->draw(QuitButton);
    }

    void create_buttons(const sf::Texture &texture){
        this->button_texture = texture;
        QuitButton.setTexture(button_texture);
        QuitButton.setTextureRect(sf::IntRect(0,549,402,174));
        QuitButton.setScale(0.9,0.9);
        QuitButton.setPosition(okno->getSize().x/2 - QuitButton.getGlobalBounds().width/2, okno->getSize().y/2 + 230);

    }
};

#endif // RULES_H
