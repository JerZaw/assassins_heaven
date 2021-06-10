#include <iostream>
#include <read_textures.h>


int menu();
int game_jumping();
int highscores();
int rules();


sf::Texture menu_back_texture;
sf::Texture hero_texture;
sf::Texture elements_textures;
sf::Texture menu_button_textures;
sf::Texture rules_back;
sf::Texture highscores_back;
sf::Texture assassin_logo_texture;
sf::Texture jumping_back_textures;
sf::Font font_comica, font_comica_bold;

int main()
{
    try{
    if(!menu_back_texture.loadFromFile("assets/menu/menu_back.png")){
        throw std::runtime_error("texture menu_back.png not found!");
    }
    if(!menu_button_textures.loadFromFile("assets/menu/options.png")){
        throw std::runtime_error("texture options.png not found!");
    }
    if(!hero_texture.loadFromFile("assets/character.png")){
        throw std::runtime_error("texture character.png not found!");
    }
    if(!elements_textures.loadFromFile("assets/spritesheet_jumper.png")){
        throw std::runtime_error("texture spritesheet_jumper.png not found!");
    }
    if(!rules_back.loadFromFile("assets/rules_back.png")){
        throw std::runtime_error("texture rules_back.png not found!");
    }
    if(!highscores_back.loadFromFile("assets/highscores_back.png")){
        throw std::runtime_error("texture highscores_back.png not found!");
    }
    if(!assassin_logo_texture.loadFromFile("assets/assassin_logo.png")){
        throw std::runtime_error("texture assassin_logo.png not found!");
    }
    if(!jumping_back_textures.loadFromFile("assets/background_1.png")){
        throw std::runtime_error("texture jumping_back_textures.png not found!");
    }
    if(!font_comica.loadFromFile("assets/Comica_BD.ttf")){
        throw std::runtime_error("font Comica_BD.ttf not found!");
    }
    if(!font_comica_bold.loadFromFile("assets/Comica_BD_Bold.ttf")){
        throw std::runtime_error("font Comica_BD_Bold.ttf not found!");
    }
    }
    catch (const std::exception &e) {
        std::cerr<<"ERROR: "<<e.what()<<std::endl;
        sf::sleep(sf::seconds(5));
        return 0;
    }
    int x;
    do{
        x = menu();
        switch (x) {
        case 1: game_jumping();break;
        case 2: highscores();break;
        case 3: rules();break;
        }
    }
    while(x!=0);
    return 0;
}
