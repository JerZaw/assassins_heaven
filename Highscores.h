#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

class Highscores
{
private:
    std::string pom_highscore;
    sf::RenderWindow *okno;
    std::vector<sf::Drawable*> drawables;
    sf::Text text_1,text_2;
    sf::Font font1;
    sf::Sprite QuitButton;
    sf::Texture button_texture;
    std::vector<sf::Text> scores;
public:
    Highscores(const sf::Font *font, sf::RenderWindow *arg_okno){

        this->okno = arg_okno;
        this->font1 = *font;

        text_1.setCharacterSize(70);
        text_1.setString("Highscores");
        text_1.setFont(font1);
        text_1.setPosition(okno->getSize().x/2 - text_1.getGlobalBounds().width/2,30);
        text_1.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_1);

        text_2.setCharacterSize(50);
        text_2.setString("Top 10");
        text_2.setFont(font1);
        text_2.setPosition(okno->getSize().x/2 - text_2.getGlobalBounds().width/2,125);
        text_2.setFillColor(sf::Color(0,0,0,250));
        drawables.emplace_back(&text_2);

        for(int i=0;i<10;i++){
            scores.emplace_back(sf::Text(std::to_string(i+1)+". ",font1,30));
            scores[i].setFillColor(sf::Color::Black);
        }

        std::string str_pom;
        std::ifstream odczyt("assets/highscores.txt");
        int counter = 0;
        while(!odczyt.eof()){
            odczyt >> str_pom;
            pom_highscore = str_pom.substr(0,str_pom.find('-')) + '\t' + str_pom.substr(str_pom.find('-')+1,str_pom.size()-1);
            scores[counter].setString(scores[counter].getString() + pom_highscore);
            counter++;
        }

        scores[0].setPosition(okno->getSize().x/3,okno->getSize().y/4);
        for(unsigned long long i=1;i<scores.size();i++){
            scores[i].setPosition(okno->getSize().x/3,scores[i-1].getPosition().y + 40);
        }
        odczyt.close();
    }

    void step(){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2f mouse_position = okno->mapPixelToCoords(sf::Mouse::getPosition(*okno));
            if(QuitButton.getGlobalBounds().contains(mouse_position)){
                okno->close();
            }
        }
    }

    void draw(){
        for(auto &el : drawables){
            okno->draw(*el);
        }
        for(auto &el : scores){
            okno->draw(el);
        }
    }

    void create_buttons(const sf::Texture &texture){
        this->button_texture = texture;
        QuitButton.setTexture(button_texture);
        QuitButton.setTextureRect(sf::IntRect(1439,206,270,129));
        QuitButton.setScale(1,0.7);
        QuitButton.setPosition(okno->getSize().x/2 - QuitButton.getGlobalBounds().width/2, okno->getSize().y/2 + 230);
        drawables.emplace_back(&QuitButton);
    }
};

#endif // HIGHSCORES_H
