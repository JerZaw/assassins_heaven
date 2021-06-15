#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <Chronometer.hpp>
#include <mind_game_elements.h>
#include <taskelement.h>
#include <summary.h>
#include <read_textures.h>


int TaskElement::mind_game(const int &difficulty)
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1500,800), "MIND_GAME",sf::Style::Close);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-1500)/2,window.getPosition().y-100));

    //::ShowWindow(window.getSystemHandle(),SW_MAXIMIZE);

    // create some shapes
    sf::Sprite background;
    background.setTexture(mind_game_back_texture);
    background.setScale(1,1);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));

    sftools::Chronometer chron1;
    chron1.reset(true);

    MindGameElements mind_plansza(difficulty,sf::IntRect(38,22,104,80),
                                  &window, &chron1);
    Summary summary(4,&font_comica_bold,&window);
    bool summary_generated = false;

    // run the program as long as the window is open
    while (window.isOpen()) {

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(background);

        if(!mind_plansza.tasks_finished()){
            mind_plansza.step(chron1.reset(true));

            // draw everything here...
            mind_plansza.draw();
        }
        else if(!summary_generated){
            summary.update(L"MIND_GAME",
                            L"Gratulacje, zdobyłeś " + std::to_wstring(mind_plansza.summary_data().first)
                            + L'/' + std::to_wstring(mind_plansza.summary_data().second)+L" punktów",
                           L"za wykonanie zadań otrzymujesz " +
                           std::to_wstring(5*(current_difficulty+1)*mind_plansza.summary_data().first) + L" monet",
                            L"naciśnij klawisz ENTER, aby wyjść z minigry");
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
                window.close();
        }

        // end the current frame
        window.display();
    }

    return 0;
}
