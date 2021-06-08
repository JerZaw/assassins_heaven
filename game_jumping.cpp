#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <jumping_game_elements.h>
#include <Chronometer.hpp>
#include <summary.h>
#include <scoresavingelement.h>
#include <read_textures.h>

int game_jumping()
{
    srand(time(0));
    //PLATFORMER
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200,1000), "ASSASSIN'S HEAVEN",sf::Style::Close);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1200)/2,0));
    //::ShowWindow(window.getSystemHandle(),SW_MAXIMIZE);


    // create some shapes
    sf::Texture texture1;
    if (!texture1.loadFromFile("assets/notexture_background.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture1.setRepeated(true);
    sf::Sprite background;
    background.setTexture(texture1);
    background.setScale(1,1);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));


//    sf::Texture hero_texture;
//    if (!hero_texture.loadFromFile("assets/notexture.jpg")) {
//        std::cerr << "Could not load texture" << std::endl;
//        return 1;
//    }


    sf::Texture elements_texture;
    if (!elements_texture.loadFromFile("assets/notexture.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Font *points_font = new sf::Font;
    if (!points_font->loadFromFile("assets/arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        return 1;
    }

    Summary summary(4,points_font,&window);
    bool summary_generated = false;
    bool score_saving = false;

    ScoreSavingElement scoresaving(points_font,&window);
    scoresaving.create_buttons(elements_texture);

    sftools::Chronometer chron1;

    JumpingGameElements plansza(30,elements_texture,sf::IntRect(38,22,104,80),0,hero_texture,points_font, &window, &chron1);
    chron1.reset(true);
    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Event event;

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(background);

        if(plansza.Game_alive()){

            plansza.step(chron1.reset_if());
            // draw everything here...
            plansza.draw();
        }
        else if(!summary_generated){
            if(plansza.summary_data().first.second){
                summary.update(L"NEW HIGHSCORE!!!",
                               L"Congratulations! You got " + std::to_wstring(plansza.summary_data().first.first)
                               + L" points",
                               L"AND you have " +
                               std::to_wstring(plansza.summary_data().second) + L" coins",
                               L"Do you want to save your score?");
            }
            else{
                summary.update(L"YOU DIED",
                               L"Congratulations! You got " + std::to_wstring(plansza.summary_data().first.first)
                               + L" points",
                               L"AND " +
                               std::to_wstring(plansza.summary_data().second) + L" coins",
                               L"Do you want to save your score?");
            }
            summary.create_buttons(elements_texture);
            summary.update_main_game();
            summary_generated=true;
        }
        else if(!score_saving){
            summary.draw();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if(summary.YesOrNo(mouse_position)=="no"){
                    window.close();
                }
                else if(summary.YesOrNo(mouse_position)=="yes"){
                    score_saving=true;
                    scoresaving.SetScore(plansza.summary_data().first.first);
                }
            }
        }
        else{
            while (window.pollEvent(event)) {
                scoresaving.step(event);
            }
            scoresaving.draw();
        }

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
