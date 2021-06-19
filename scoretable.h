#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <read_textures.h>

class ScoreTable
{
private:
    sf::Sprite background_table;
    const sf::Font font1;
    sf::Text points_text;
    sf::RenderWindow *okno;
    const sf::Texture texture;
public:
    ScoreTable(){};
    ScoreTable(sf::RenderWindow *arg_okno, const sf::Texture &arg_texture,
               const sf::IntRect &arg_rect, const sf::Vector2f &arg_back_position,
               const sf::Vector2f &arg_text_position, const std::string &start_string = "0", const int &character_size=30):
    font1(font_comica_bold),okno(arg_okno),texture(arg_texture){
            background_table.setTexture(texture);
            background_table.setTextureRect(arg_rect);
            background_table.setPosition(arg_back_position);

            points_text.setFont(font1);
            points_text.setCharacterSize(character_size);
            points_text.setStyle(sf::Text::Regular);
            points_text.setString(start_string);
            points_text.setFillColor(sf::Color::Black);
            points_text.setPosition(arg_text_position);
    }

    float GetTextHeight(){
        return points_text.getGlobalBounds().height;
    }

    void scalebackground(const float &scale){
        background_table.scale(scale,scale);
    }

    void settextonmiddle(int space_between){
        points_text.setPosition(background_table.getGlobalBounds().left +
                                background_table.getGlobalBounds().width/2 - points_text.getGlobalBounds().width/2,
                                background_table.getGlobalBounds().top - space_between - points_text.getGlobalBounds().height);
    }

    virtual bool picked(){};

    void draw(){
        okno->draw(background_table);
        okno->draw(points_text);
    }

    void update(const int &points){
        points_text.setString(std::to_string(points));
    }

    void update(const std::string &text){
        points_text.setString(text);
    }

    sf::Sprite* GetBackground(){
        return &background_table;
    }


};

#endif // SCORETABLE_H
