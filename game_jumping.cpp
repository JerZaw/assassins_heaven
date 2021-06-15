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

    Summary summary(4,&font_comica_bold,&window);
    bool summary_generated = false;
    bool score_saving = false;

    ScoreSavingElement scoresaving(&font_comica_bold,&window);
    scoresaving.create_buttons(menu_button_textures);

    sftools::Chronometer chron1;

    JumpingGameElements plansza(30,0, &window, &chron1);
    chron1.reset(true);
    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Event event;

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
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
            summary.create_buttons(menu_button_textures);
            summary.update_main_game();
            summary_generated=true;
        }
        else if(!score_saving){
            summary.draw();
            sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            std::string pom_chosenbutton = summary.YesOrNo(mouse_position);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(pom_chosenbutton=="no"){
                    window.close();
                }
                else if(pom_chosenbutton=="yes"){
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
