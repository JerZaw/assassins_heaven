#ifndef GAMEAPPS_H
#define GAMEAPPS_H

#include <assetsmanager.h>

class GameApps
{
private:
    int menu();
    int game_jumping();
    int highscores();
    int rules();
public:
    GameApps(){};

    void load_data(){
        AssetsManager assetsmanager;
    }

    void play(){
        menu_music.play();
        int x;
        do{
            x = menu();
            switch (x) {
            case 1: menu_music.stop();game_jumping();menu_music.play();break;
            case 2: highscores();break;
            case 3: rules();break;
            }
        }
        while(x!=0);
    }
};

#endif // GAMEAPPS_H
