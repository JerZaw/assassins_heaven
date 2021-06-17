#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <Chronometer.hpp>
#include <fighting_game_elements.h>
#include <taskelement.h>
#include <summary.h>
#include <read_textures.h>

int TaskElement::fighting_game(const int &difficulty)
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1500,800), "FIGHTING_GAME",sf::Style::Close);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1500)/2,window.getPosition().y-100));

    //::ShowWindow(window.getSystemHandle(),SW_MAXIMIZE);

    // create some shapes
    sf::Sprite background;
    background.setTexture(fighting_game_back_texture);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));

    sftools::Chronometer chron1;
    chron1.reset(true);

    fighting_game_elements fight_plansza(difficulty,sf::IntRect(38,22,104,80),
                                  &window,&chron1);
    Summary summary(4, &font_comica_bold, &window);
    bool summary_generated = false;

    // run the program as long as the window is open
    while (window.isOpen()) {

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(background);

        if(!fight_plansza.tasks_finished()){
            fight_plansza.step(chron1.reset(true));

            // draw everything here...
            fight_plansza.draw();
        }
        else if(!summary_generated){
            summary.update(L"FIGHTING_GAME",
                            L"Congratulations, you got " + std::to_wstring(fight_plansza.summary_data().first)
                            + L'/' + std::to_wstring(fight_plansza.summary_data().second)+L" points",
                           L"For completing the tasks you gain " +
                           std::to_wstring((current_difficulty+1)*fight_plansza.summary_data().first) + L" coins",
                            L"press ENTER, to leave the minigame");
            summary_generated=true;
            //minigame_end_horns.play();
        }
        else{
            summary.draw();

            if(summary.closing()){
                window.close();
                return (current_difficulty+1)*fight_plansza.summary_data().first;
            }
        }

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
