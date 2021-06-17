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

    sf::Sprite background;
    background.setTexture(rules_back);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));

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


