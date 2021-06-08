#ifndef RULES_H
#define RULES_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Rules
{
private:
    sf::RenderWindow *okno;
    sf::Font font1;
    sf::Sprite QuitButton;
    sf::Texture button_texture;
    std::vector<sf::Text> rules;
public:
    Rules(const sf::Font *font, sf::RenderWindow *arg_okno){
        this->okno = arg_okno;
        this->font1 = *font;

        sf::Text text_1("Rules",font1,70);
        text_1.setPosition(okno->getSize().x/2 - text_1.getGlobalBounds().width/2,30);
        text_1.setFillColor(sf::Color(0,0,0,250));
        rules.emplace_back(text_1);

        for(int i=1;i<11;i++){
            rules.emplace_back(sf::Text("",font1,30));
            rules[i].setFillColor(sf::Color::Black);
        }

        rules[1].setString(L"Gra polega na zdobyciu jak największej");
        rules[2].setString(L"ilości punktów poprzed wspięcie się jak najwyżej");
        rules[3].setString(L"w głównej grze sterowanie strzałki lewo-prawo");
        rules[4].setString(L"możesz też zdobyć pieniądze zbierając");
        rules[5].setString(L"monety pojawiające się na platformach");
        rules[6].setString(L"zbierając symbol assassina aktywuje się minigra");
        rules[7].setString(L"1. mindgame: wskocz na platformę z dobrą odpowiedzią");
        rules[8].setString(L"2. fightinggame: zestrzel wszystkie cele");
        rules[9].setString(L"po skończeniu minigier wracasz do gry");
        rules[10].setString(L"za pieniądze możesz kupić boosty na starcie");

        rules[1].setPosition(okno->getSize().x/2 - rules[1].getGlobalBounds().width/2,okno->getSize().y/6);
        for(unsigned long long i=2;i<rules.size();i++){
            rules[i].setPosition(okno->getSize().x/2 - rules[i].getGlobalBounds().width/2,rules[i-1].getPosition().y + 40);
        }
    }

    void step(){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
            if(QuitButton.getGlobalBounds().contains(mouse_position)){
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
