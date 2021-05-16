#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <animatedsprite.h>

int game_jumping()
{
    //PLATFORMER
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200,800), "My window");

    // create some shapes
    sf::Texture texture1;
    if (!texture1.loadFromFile("notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture1.setRepeated(true);
    sf::Sprite grass;
    grass.setTexture(texture1);
    grass.setScale(1,1);
    grass.setTextureRect(sf::IntRect(0,0,window.getSize().x,300));


    sf::Texture texture;
    if (!texture.loadFromFile("notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    AnimatedSprite ludek(8);
    ludek.setTexture(texture);
    ludek.add_animation_frame(sf::IntRect(14,6,19,31)); // 1 frame of animation
    ludek.add_animation_frame(sf::IntRect(65, 6, 19, 31)); // 2 frame
    ludek.add_animation_frame(sf::IntRect(115, 6, 19, 31)); // 3 frame
    ludek.add_animation_frame(sf::IntRect(167, 6, 20, 30)); // 4 frame
    ludek.add_animation_frame(sf::IntRect(216,6,20,31)); // 5 frame
    ludek.add_animation_frame(sf::IntRect(266, 6, 20, 31)); // 6 frame
    ludek.add_animation_frame(sf::IntRect(317, 6, 20, 31)); // 7 frame
    ludek.add_animation_frame(sf::IntRect(366, 6, 20, 30)); // 8 frame
    ludek.setScale(1,1);

    sf::Texture texture2;
    if (!texture2.loadFromFile("notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture2.setRepeated(true);
    std::vector<sf::Sprite> mury;
    sf::Sprite mur1;
    mur1.setTexture(texture2);
    mur1.setTextureRect(sf::IntRect(38,22,104,80));
    mur1.setPosition(200,500);
    mur1.setScale(1,1);
    mury.emplace_back(mur1);

    mur1.setPosition(400,400);
    mury.emplace_back(mur1);

    mur1.setPosition(800,500);
    mury.emplace_back(mur1);

    ludek.setTextureRect(sf::IntRect(14,6,19,31));
    // run the program as long as the window is open
    sf::Clock clock1;
    while (window.isOpen()) {

        ludek.step(clock1);
        for(auto &el : mury){
            if(ludek.getGlobalBounds().intersects(el.getGlobalBounds())){
                ludek.SetSpeed(-200);
            }
        }
        sf::Event event;
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Right){
                    ludek.move(10,0);
                    if (ludek.getGlobalBounds().left+ludek.getGlobalBounds().width > window.getSize().x){
                        ludek.move(-(ludek.getGlobalBounds().left + ludek.getGlobalBounds().width - window.getSize().x),0);
                    }
                }
                else if(event.key.code == sf::Keyboard::Left){
                    ludek.move(-10,0);
                    if (ludek.getGlobalBounds().left < 0){
                        ludek.move(-ludek.getGlobalBounds().left,0);
                    }
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(grass);
        window.draw(ludek);
        for(auto &el : mury){
            window.draw(el);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
