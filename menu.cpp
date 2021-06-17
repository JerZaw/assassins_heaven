#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <read_textures.h>

int menu()
{
    bool mouse_released = false;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800,800), "Menu");

    // create some shapes
    sf::Texture tlo_texture;
    if (!tlo_texture.loadFromFile("assets/menu/back.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return -1;
    }
    sf::Sprite tlo;
    tlo.setTexture(menu_back_texture);

    std::vector<sf::Sprite> options;

    sf::Texture option_texture;
    if (!option_texture.loadFromFile("assets/menu/option.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return -1;
    }

    sf::Sprite option;
    option.setTexture(menu_button_textures);
    option.setTextureRect(sf::IntRect(0,0,402,174));
    option.setScale(0.9,0.9);
    option.setPosition(window.getSize().x/2 - option.getGlobalBounds().width/2,250);
    options.emplace_back(option);

    option.setTextureRect(sf::IntRect(0,183,402,174));
    option.setPosition(window.getSize().x/2 - option.getGlobalBounds().width/2,250 + 174 + 10);
    options.emplace_back(option);

    option.setTextureRect(sf::IntRect(0,366,402,174));
    option.setPosition(window.getSize().x/2 - option.getGlobalBounds().width/2,option.getPosition().y+ 174 + 10);
    options.emplace_back(option);

    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Event event;

        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here...
        window.draw(tlo);
        for(auto &el : options){
            window.draw(el);
        }
        // end the current frame
        window.display();

        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if(options[0].getGlobalBounds().contains(mouse_position)){
            options[0].setTextureRect(sf::IntRect(489,0,402,174));
        }else{
            options[0].setTextureRect(sf::IntRect(0,0,402,174));
            if(options[1].getGlobalBounds().contains(mouse_position)){
                options[1].setTextureRect(sf::IntRect(489,183,402,174));
            }
            else{
                options[1].setTextureRect(sf::IntRect(0,183,402,174));
                if(options[2].getGlobalBounds().contains(mouse_position)){
                    options[2].setTextureRect(sf::IntRect(489,366,402,174));
                }
                else{
                    options[2].setTextureRect(sf::IntRect(0,366,402,174));
                }
            }
        }

        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
                return 0;
            }
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                mouse_released = true;
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_released){
                mouse_released = false;
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if(options[0].getGlobalBounds().contains(mouse_position)){
                    click.play();
                    return 1;
                }
                else if(options[1].getGlobalBounds().contains(mouse_position)){
                    click.play();
                    return 2;
                }
                else if(options[2].getGlobalBounds().contains(mouse_position)){
                    click.play();
                    return 3;
                }
            }
        }
    }
    return 0;
}
