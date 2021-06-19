#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Highscores.h>
#include <read_textures.h>
#include <gameapps.h>

int GameApps::highscores()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800,800), "HIGHSCORES",sf::Style::None);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-window.getSize().x)/2,window.getPosition().y));

    Highscores highscores(font_comica_bold,&window);

    // run the program as long as the window is open
    while (window.isOpen()) {

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        highscores.draw();

        highscores.step();

        // end the current frame
        window.display();
    }

    return 0;
}

