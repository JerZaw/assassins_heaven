#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <animatedsprite.h>
#include <platform.h>
#include <movingplatform.h>
#include <timedplatform.h>
#include <timedmovingplatform.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <game_elements.h>
#include <Chronometer.hpp>



int game_jumping()
{
    srand(time(0));
    //PLATFORMER
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200,1000), "My window",sf::Style::Close);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1200)/2,0));
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


    sf::Texture platform_texture;
    if (!platform_texture.loadFromFile("notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    GameElements plansza(30,platform_texture,sf::IntRect(38,22,104,80),2,hero_texture);


    // run the program as long as the window is open
    sftools::Chronometer chron1;
    while (window.isOpen()) {
        while(plansza.Game_alive()){

            plansza.step(chron1.reset(true),window);


            // clear the window with black color
            window.clear(sf::Color::Black);

            // draw everything here...
            window.draw(background);
            window.draw(plansza.GetLudek());
            for(auto &el : plansza.GetPlatformsVec()){
                window.draw(*el);
            }

            // end the current frame
            window.display();
        }
        chron1.pause();

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
