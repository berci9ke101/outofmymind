#include "game.h"
#include "econio.h"

#ifdef _WIN32

#include <windows.h>

#endif

void Game::init()
{
#ifdef _WIN32
    ///ablak méretének beállítása
    system("mode con:cols=119 lines=25");

    ///ablak átnevezése
    UINT original_cp = GetConsoleCP();
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleTitle("Out Of My Mind");
    SetConsoleCP(original_cp);

    ///kurzor eltűntetése
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(outhandle, &cursor);
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(outhandle, &cursor);

#endif
    econio_rawmode();
}

int Game::keypress()
{
    int key = -1;
    if (econio_kbhit())
    {
        key = econio_getch();
    }
    return key;
}

void Game::writequest(const Quest &)
{
///NEM AKAROM MEGCSINÁLNI
}
