#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ScoreTable
{
private:
    sf::Sprite background_table;
    sf::Texture texture;
    const sf::Font *font1;
    sf::Text points_text;
public:
    ScoreTable(){};
    ScoreTable(const sf::Texture &arg_texture, const sf::Font *arg_font){
            background_table.setTexture(arg_texture);
            background_table.setTextureRect(sf::IntRect(0,0,200,60));
            background_table.setPosition(600-background_table.getGlobalBounds().width/2,10);

            font1 = arg_font;
            points_text.setFont(*font1);
            points_text.setCharacterSize(30);
            points_text.setStyle(sf::Text::Regular);
            points_text.setString("0");
            points_text.setFillColor(sf::Color::Black);
            points_text.setPosition(600,15);
    }

    sf::Sprite GetBackground(){
        return background_table;
    }
    sf::Text GetText(){
        return points_text;
    }

    void update(int points){
        points_text.setString(std::to_string(points));
    }


};

#endif // SCORETABLE_H
