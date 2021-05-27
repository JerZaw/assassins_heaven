#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ScoreTable
{
private:
    sf::Sprite background_table;
    const sf::Font *font1;
    sf::Text points_text;
    sf::RenderWindow *okno;
public:
    ScoreTable(){};
    ScoreTable(const sf::Texture &arg_texture, const sf::Font *arg_font, sf::RenderWindow *arg_okno,
               const sf::IntRect &arg_rect, const sf::Vector2f &arg_back_position,
               const sf::Vector2f &arg_text_position, const std::string &start_string = "0", const int &character_size=30){
            background_table.setTexture(arg_texture);
            background_table.setTextureRect(arg_rect);
            background_table.setPosition(arg_back_position);

            this->okno = arg_okno;

            font1 = arg_font;
            points_text.setFont(*font1);
            points_text.setCharacterSize(character_size);
            points_text.setStyle(sf::Text::Regular);
            points_text.setString(start_string);
            points_text.setFillColor(sf::Color::Black);
            points_text.setPosition(arg_text_position);
    }

    void settextonmiddle(int space_between){
        points_text.setPosition(background_table.getGlobalBounds().left - points_text.getGlobalBounds().width/2,
                                background_table.getGlobalBounds().top - space_between);
    }

    void draw(){
        okno->draw(background_table);
        okno->draw(points_text);
    }

    void update(int points){
        points_text.setString(std::to_string(points));
    }


};

#endif // SCORETABLE_H
