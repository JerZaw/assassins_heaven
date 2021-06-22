#include <gameapps.h>

int main()
{
    GameApps gameapps;
    try{
        gameapps.load_data();
    }
    catch (const std::exception &e) {
        std::cerr<<"ERROR: "<<e.what()<<std::endl;
        return 0;
    }

    gameapps.play();
    return 0;
}
