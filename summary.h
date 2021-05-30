#ifndef SUMMARY_H
#define SUMMARY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Summary
{
private:
    sf::RenderWindow *okno;
    sf::RectangleShape background_rect;
    std::vector<sf::Drawable*> drawables;
    sf::Text text_1,text_2,text_3,text_4;
    sf::Font font1;
public:
    Summary(){};
    Summary(const int &text_count, const sf::Font *font, sf::RenderWindow *arg_okno){

        this->okno = arg_okno;
        this->font1 = *font;

        background_rect.setSize(sf::Vector2f(1300,600));
        background_rect.setFillColor(sf::Color(200,200,200,128));
        background_rect.setPosition(okno->getSize().x/2 - background_rect.getGlobalBounds().width/2,okno->getSize().y/2 - background_rect.getGlobalBounds().height/2);

        drawables.emplace_back(&background_rect);

        for(int i=0;i<text_count;i++){
            sf::Text text;
            drawables.emplace_back(&text);
        }
    };

    void update( const std::wstring &main_title, const std::wstring &points_text, const std::wstring &lower_title){
        text_1.setCharacterSize(80);
        text_1.setString(main_title);
        text_1.setFont(font1);
        text_1.setPosition(okno->getSize().x/2 - text_1.getGlobalBounds().width/2,okno->getSize().y/6);
        text_1.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_1);

        text_2.setCharacterSize(60);
        text_2.setString(points_text);
        text_2.setFont(font1);
        text_2.setPosition(okno->getSize().x/2 - text_2.getGlobalBounds().width/2,okno->getSize().y/2-60);
        text_2.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_2);

        text_3.setCharacterSize(40);
        text_3.setString(lower_title);
        text_3.setFont(font1);
        text_3.setPosition(okno->getSize().x/2 - text_3.getGlobalBounds().width/2,okno->getSize().y/2+130);
        text_3.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_3);
    };

    void update(const std::wstring &main_title, const std::wstring &points_text, const std::wstring &points_addon_text, const std::wstring &lower_title){
        text_1.setCharacterSize(80);
        text_1.setString(main_title);
        text_1.setFont(font1);
        text_1.setPosition(okno->getSize().x/2 - text_1.getGlobalBounds().width/2,okno->getSize().y/6);
        text_1.setFillColor(sf::Color(0,0,0,250));
        drawables[1] = &text_1;

        text_2.setCharacterSize(60);
        text_2.setString(points_text);
        text_2.setFont(font1);
        text_2.setPosition(okno->getSize().x/2 - text_2.getGlobalBounds().width/2,okno->getSize().y/2-60);
        text_2.setFillColor(sf::Color(0,0,0,250));
        drawables[2] = &text_2;

        text_3.setCharacterSize(50);
        text_3.setString(points_addon_text);
        text_3.setFont(font1);
        text_3.setPosition(okno->getSize().x/2 - text_3.getGlobalBounds().width/2,okno->getSize().y/2+70);
        text_3.setFillColor(sf::Color(0,0,0,250));
        drawables[3] = &text_3;

        text_4.setCharacterSize(40);
        text_4.setString(lower_title);
        text_4.setFont(font1);
        text_4.setPosition(okno->getSize().x/2 - text_4.getGlobalBounds().width/2,okno->getSize().y/2+160);
        text_4.setFillColor(sf::Color(0,0,0,250));
        drawables[4] = &text_4;
    };

    void draw(){
        for(auto &el : drawables){
            okno->draw(*el);
        }
    }

    bool closing(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){//sprawdzam ruchy poza eventem z powodu opóźnień wejścia
            return true;
        }
        return false;
    }

};

#endif // SUMMARY_H
