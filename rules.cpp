#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Rules.h>
#include <read_textures.h>

int rules()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800,800), "RULES",sf::Style::None);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-800)/2,window.getPosition().y));

    // create some shapes
    sf::Texture texture1;
    if (!texture1.loadFromFile("assets/notexture_background.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture1.setRepeated(true);
    sf::Sprite background;
    background.setTexture(rules_back);
    background.setScale(1,1);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));

    sf::Texture elements_texture;
    if (!elements_texture.loadFromFile("assets/notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Font *points_font = new sf::Font;
    if (!points_font->loadFromFile("assets/Comica_BD_Bold.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        return 1;
    }

    Rules rules(&font_comica_bold,&window);
    rules.create_buttons(menu_button_textures);

    // run the program as long as the window is open
    while (window.isOpen()) {

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(background);
        rules.draw();

        rules.step();

        // end the current frame
        window.display();
    }

    return 0;
}


