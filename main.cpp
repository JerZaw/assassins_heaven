#include <iostream>

int menu();
int game_jumping();
int highscores();
int rules();

int main()
{
    int x;
    do{
    x = menu();
    switch (x) {
    case 1: game_jumping();break;
    case 2: highscores();break;
    case 3: rules();break;
    }
}
    while(x!=0);
    return 0;
}
