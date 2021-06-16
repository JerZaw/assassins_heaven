#ifndef PLATFORMWITHEQUATION_H
#define PLATFORMWITHEQUATION_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <scoretable.h>

class PlatformWithEquation : public ScoreTable
{
private:
    bool good_solution;
    sf::Color clicked_color;
public:
    PlatformWithEquation(){};
    PlatformWithEquation(const sf::Texture &arg_texture, const sf::Font *arg_font, sf::RenderWindow *arg_okno,
                         const sf::IntRect &arg_rect, const sf::Vector2f &arg_back_position,
                         const sf::Vector2f &arg_text_position, const std::string &start_string = "0",
                         const int &character_size=30, const bool &if_solution = false):
        ScoreTable(arg_texture,arg_font,arg_okno,arg_rect,arg_back_position,arg_text_position,start_string,character_size){
        this->good_solution = if_solution;
        if(good_solution){
            clicked_color = sf::Color::Green;
        }
        else{
            clicked_color = sf::Color::Red;
        }
        this->scalebackground(0.35);
        this->settextonmiddle(13);
    };

    bool picked(){
        this->GetBackground()->setColor(clicked_color);
        return good_solution;
    }

};

#endif // PLATFORMWITHEQUATION_H
