#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <Chronometer.hpp>
#include <mind_game_elements.h>
#include <taskelement.h>



int TaskElement::mind_game(const int &difficulty)
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1500,800), "My window",sf::Style::Close);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1500)/2,0));

    //::ShowWindow(window.getSystemHandle(),SW_MAXIMIZE);

    // create some shapes
    sf::Texture texture1;
    if (!texture1.loadFromFile("notexture_background.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture1.setRepeated(true);
    sf::Sprite background;
    background.setTexture(texture1);
    background.setScale(1,1);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));


    sf::Texture hero_texture;
    if (!hero_texture.loadFromFile("notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }


    sf::Texture elements_texture;
    if (!elements_texture.loadFromFile("notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Font *points_font = new sf::Font;
    if (!points_font->loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        return 1;
    }

    sftools::Chronometer chron1;
    chron1.reset(true);

    MindGameElements mind_plansza(difficulty,elements_texture, sf::IntRect(38,22,104,80),
                                  hero_texture, points_font, &window,
                                  &chron1);

    // run the program as long as the window is open
    while (window.isOpen()) {
        while(!mind_plansza.tasks_finished()){
            mind_plansza.step(chron1.reset(true));

            // clear the window with black color
            window.clear(sf::Color::Black);

            // draw everything here...
            window.draw(background);
            mind_plansza.draw();

            // end the current frame
            window.display();
        }
        //chron1.pause();

        sf::Event event;
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
