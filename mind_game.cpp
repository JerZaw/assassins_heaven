#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <Chronometer.hpp>
#include <mind_game_elements.h>
#include <taskelement.h>
#include <summary.h>
#include <read_textures.h>


int TaskElement::mind_game(const int &difficulty,const sf::IntRect &current_long_platform_texture_rect)
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1500,800), "MIND_GAME",sf::Style::Close);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1500)/2,window.getPosition().y-100));

    // create some shapes

    sftools::Chronometer chron1;
    chron1.reset(true);

    MindGameElements mind_plansza(difficulty,current_long_platform_texture_rect,
                                  &window, &chron1);
    Summary summary(4,font_comica_bold,&window);
    bool summary_generated = false;

    // run the program as long as the window is open
    while (window.isOpen()) {

        // clear the window with black color
        window.clear(sf::Color::Black);

        if(!mind_plansza.tasks_finished()){
            mind_plansza.step(chron1.reset(true));

            // draw everything here...
            mind_plansza.draw();
        }
        else if(!summary_generated){
            summary.update(L"MIND_GAME",
                           L"Congratulations, you got " + std::to_wstring(mind_plansza.summary_data().first)
                           + L'/' + std::to_wstring(mind_plansza.summary_data().second)+L" points",
                           L"For completing the tasks you gain " +
                           std::to_wstring(5*(current_difficulty+1)*mind_plansza.summary_data().first) + L" coins",
                           L"press ENTER, to leave the minigame");
            summary_generated=true;
        }
        else{
            summary.draw();

            if(summary.closing()){
                window.close();
                return 5*(current_difficulty+1)*mind_plansza.summary_data().first;
            }
        }

        sf::Event event;
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // end the current frame
        window.display();
    }

    return 0;
}
