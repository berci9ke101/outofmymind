#include <iostream>
#include "game.h"

int main()
{
    ///megkérdezzük a felhasználót, hogy mi a játékfájl neve
    std::cout << "What's the name of the gamefile that you would like to load?: ";
    std::string gamefile;
    std::cin >> gamefile;

    ///létrehozunk egy játékfájlt
    Game playgame();

    playgame().
    return 0;
}