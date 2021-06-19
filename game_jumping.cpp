#include <jumping_game_elements.h>
#include <jumpingscene.h>
#include <iostream>

int GameApps::game_jumping()
{
    //PLATFORMER - JUMPER

    JumpingScene scene(1200,1000);
    JumpingGameElements jumping_game(30);
    scene.set_jumping_game(&jumping_game);

    scene.window_loop();

    return 0;
}
