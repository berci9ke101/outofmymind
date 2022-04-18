#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "econio.h"
#include "game.h"

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

Game::Game(int width, int height) : width(width), height(height), iswin(detect())
{}

Game::Game(const Game &rhs) : width(rhs.width), height(rhs.height), iswin(rhs.iswin)
{}

Game::~Game()
{}

///-------------------------------///
///a fájkezelésért felelős osztály///
///-------------------------------///
const std::vector<std::string> &
Game::FileIO::read(const std::string &gamefile, const std::string &savefile, QuestQueue &queue)
{
//    ///megkérdezzük a felhasználót, hogy mi a játékfájl neve
//    std::cout << "What's the name of the gamefile that you would like to load?: ";
//    std::string gamefile;
//    std::cin >> gamefile;
//
//
    ///fájl megnyitása
    std::ifstream GAME;
    GAME.open(gamefile, std::ios::in);

    ///ha nem lehet megnyitni a fájlt...
    if (not(GAME.is_open()))
    {
        ///kivételt dobunk
        GAME.close();
        throw std::ios_base::failure("Could not open file!");
    }

    ///beolvasás, ha nincs hiba
    std::string line;
    std::vector<std::string> *sVector = new std::vector<std::string>;
    while (getline(GAME, line))
    {
        sVector->push_back(line);
    }

    ///ha üres a fájl...
    if (sVector->empty())
    {
        ///kivételt dobunk
        delete sVector;
        GAME.close();
        throw std::logic_error("Empty file!");
    }

    ///a fájl bezárása
    GAME.close();

    ///mentés betöltése
    std::ifstream LOAD;
    LOAD.open(savefile, std::ios::in);

    ///ha nem lehet megnyitni a fájlt...
    if (not(LOAD.is_open()))
    {
        ///kivételt dobunk
        LOAD.close();
        throw std::ios_base::failure("Could not open file!");
    }

    ///beolvasás, ha nincs hiba
    getline(LOAD, line);
    std::stringstream(line) >> queue.getcurrent_state();

    ///a fájl bezárása
    LOAD.close();

    ///tömb visszaadása
    return *sVector;
}

void Game::FileIO::load(const std::vector<std::string> &sVector, QuestQueue &queue) const
{
    ///temporális változók
    questtype TMP_type;
    size_t TMP_ID;
    std::string TMP_desc;
    std::string TMP_optA;
    size_t TMP_jmpA;
    std::string TMP_optB;
    size_t TMP_jmpB;

    ///a visitable quest tempoláris változói
    size_t TMP_jmpauto;
    std::string TMP_alternatedesc;

    ///ha üres a fájl...
    if (sVector.empty())
    {
        ///kivételt dobunk
        throw std::logic_error("Empty file!");
    }

    ///beolvasáso ciklus
    for (size_t i = 0; i < sVector.size(); i++)
    {
        std::string TEMP = sVector[i];

        std::vector<std::string> variable_arr;
        std::istringstream strings(sVector[i]);
        std::string s;

        while (getline(strings, s, ';'))
        {
            variable_arr.push_back(s);
        }

        ///ID konvertálása
        std::stringstream(variable_arr[0]) >> TMP_ID;

        ///küldetés típusának kitalálása
        std::string type = variable_arr[1];
        ///Simple vagy Random quest esetén
        if (type == std::string("S") or type == std::string("R"))
        {
            ///küldetésleírás konvertálása
            TMP_desc = variable_arr[2];

            ///A opció szövegének konvertálása
            TMP_optA = variable_arr[3];

            ///A opcióra való ugrás konvertálása
            std::stringstream(variable_arr[4]) >> TMP_jmpA;

            ///B opció szövegének konvertálása
            TMP_optA = variable_arr[5];

            ///B opcióra való ugrás konvertálása
            std::stringstream(variable_arr[4]) >> TMP_jmpB;

            ///küldetéstípus tesztelése
            if (type == std::string("S"))
            {
                ///küldetéstípus konvertálása
                TMP_type = Simple;
                queue.add(new SimpleQuest(TMP_type, TMP_ID, TMP_desc, TMP_optA, TMP_jmpA, TMP_optB, TMP_jmpB));
            }
            else if (type == std::string("R"))
            {
                ///küldetéstípus konvertálása
                TMP_type = Random;
                queue.add(new RandomQuest(TMP_type, TMP_ID, TMP_desc, TMP_optA, TMP_jmpA, TMP_optB, TMP_jmpB));
            }
        }

            ///Visited vagy Visitable
        else if (type == std::string("V") or type == std::string("v"))
        {
            ///küldetésleírás konvertálása
            TMP_desc = variable_arr[2];

            ///a másodlagos leírás konvertálása
            TMP_alternatedesc = variable_arr[3];

            ///az automatikus ugrás konvertálása
            std::stringstream(variable_arr[4]) >> TMP_jmpauto;

            ///A opció szövegének konvertálása
            TMP_optA = variable_arr[5];

            ///A opcióra való ugrás konvertálása
            std::stringstream(variable_arr[6]) >> TMP_jmpA;

            ///B opció szövegének konvertálása
            TMP_optA = variable_arr[7];

            ///B opcióra való ugrás konvertálása
            std::stringstream(variable_arr[8]) >> TMP_jmpB;

            ///küldetéstípus tesztelése
            if (type == std::string("v"))
            {
                ///küldetéstípus konvertálása
                TMP_type = Visitable;
            }
            else if (type == std::string("V"))
            {
                ///küldetéstípus konvertálása
                TMP_type = Visited;
            }
            queue.add(new VisitedQuest(TMP_type, TMP_ID, TMP_desc, TMP_optA, TMP_jmpA, TMP_optB, TMP_jmpB, TMP_jmpauto,
                                       TMP_alternatedesc));
        }
        else
        {
            ///egyik sem, baj van...
            throw std::logic_error("No such questtype!");
        }
    }
}

void Game::FileIO::save(const std::string &savegame, QuestQueue &queue) const
{
    ///mentés kiírása
    std::ofstream SAVE;
    std::string line;
    SAVE.open(savegame, std::ios::out);

    ///ha nem lehet megnyitni a fájlt...
    if (not(SAVE.is_open()))
    {
        ///kivételt dobunk
        SAVE.close();
        throw std::ios_base::failure("Could not open file!");
    }

    ///kiírás, ha nincs hiba
    SAVE << queue.getcurrent_state() << "\n";

    ///a fájl bezárása
    SAVE.close();
}
