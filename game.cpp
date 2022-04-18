#include "game.h"
#include <iostream>
#include "econio.h"
#include <string>

#ifdef _WIN32

#include <windows.h>

#endif

bool detect()
{
#ifdef _WIN32
    return true;
#endif
    return false;
}

///--------------------------///
///a játékért felelős osztály///
///--------------------------///
void Game::init()
{
    if (iswin)
    {
        ///ablak méretének beállítása
        std::string sys = "mode con:cols=" + std::to_string(width) + " lines=" + std::to_string(height);
        //system("mode con:cols=119 lines=25");

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
    }
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

void Game::writequest(const Quest &rhs)
{
    econio_clrscr();

    econio_gotoxy(0, 0);
    std::cout << rhs.getdesc();

    econio_gotoxy(14, 0);
    std::cout << "A: " << rhs.getoptA();

    econio_gotoxy(17, 0);
    std::cout << "B: " << rhs.getoptB();
}

Game::Game() : width(25), height(119), iswin(detect())
{}

Game::Game(int width, int height): width(width), height(height), iswin(detect())
{}

Game::Game(const Game &rhs): width(rhs.width), height(rhs.height), iswin(rhs.iswin)
{}

Game::~Game()
{}

///-------------------------------///
///a fájkezelésért felelős osztály///
///-------------------------------///
void Game::FileIO::read(const std::string &)
{
    ///NOT YET
}

void Game::FileIO::save()
{
    ///NOT YET
}
