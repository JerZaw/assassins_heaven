#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Highscores.h>
#include <read_textures.h>

int highscores()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800,800), "HIGHSCORES",sf::Style::None);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-800)/2,window.getPosition().y));

    Highscores highscores(font_comica_bold,&window);
    highscores.create_buttons(menu_button_textures);

    // run the program as long as the window is open
    while (window.isOpen()) {

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        highscores.draw();

        highscores.step();

        sf::Event event;
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // end the current frame
        window.display();
    }

    return 0;
}

