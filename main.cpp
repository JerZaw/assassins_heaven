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
sf::Font font_comica, font_comica_bold;

int main()
{
    menu_back_texture.loadFromFile("assets/menu/menu_back.png");
    menu_button_textures.loadFromFile("assets/menu/options.png");
    hero_texture.loadFromFile("assets/character.png");
    elements_textures.loadFromFile("assets/menu/menu_back.png");
    font_comica.loadFromFile("assets/Comica_BD.ttf");
    font_comica_bold.loadFromFile("assets/Comica_BD_Bold.ttf");
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
