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
void Game::init() const
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
    int key = econio_getch();
    return key;
}

void Game::writequest(Quest *rhs)
{
    econio_clrscr();

    econio_gotoxy(0, 0);
    std::cout << *(rhs->getdesc());

    ///felszbadítjuk a dinamikusan foglalt leírást
    delete rhs->getdesc();

    ///ha nem látogatott a küldetés csak akkor írjuk ki a szöveget
    if (rhs->gettype() != Visited)
    {
        econio_gotoxy(0, 14);
        std::cout << "A: " << rhs->getoptA();

        econio_gotoxy(0, 17);
        std::cout << "B: " << rhs->getoptB();
    }

    ///"help menu"
    econio_gotoxy(0, 22);
    std::cout << "A billentyű      - kiválasztja az 'A' opciót";
    econio_gotoxy(0, 23);
    std::cout << "B billentyű      - kiválasztja az 'B' opciót";
    econio_gotoxy(0, 24);
    std::cout << "ESCAPE billentyű - mentés és kilépés";
}

Game::Game() : width(25), height(119), iswin(detect())
{}

Game::Game(const std::string &filename, int width, int height) : width(width), height(height), iswin(detect()),
                                                                 file(filename)
{}

Game::Game(const Game &rhs) : width(rhs.width), height(rhs.height), iswin(rhs.iswin)
{}

Game::~Game()
{}

///-------------------------------///
///a fájkezelésért felelős osztály///
///-------------------------------///
const notstd::vector<std::string> &
FileIO::read(const std::string &gamefile, const std::string &savefile, QuestQueue &queue)
{
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
    notstd::vector<std::string> *sVector = new notstd::vector<std::string>;
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

    ///ha nem lehetne megnyitni a fájlt, akkor az alapértelmezett 0 állásból indul a játék
    queue.getcurrent_state() = 0;

    ///ha meg lehet nyitni a fájlt...
    if (LOAD.is_open())
    {
        ///betöltjük a játékállást
        getline(LOAD, line);
        std::stringstream(line) >> queue.getcurrent_state();
    }

    ///a fájl bezárása
    LOAD.close();

    ///tömb visszaadása
    return *sVector;
}

void FileIO::load(const notstd::vector<std::string> &sVector, QuestQueue &queue)
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
        ///szétszedjük a szöveget a ';' karakterek mentén és belerakjuk egy dinamikus tömbbe
        notstd::vector<std::string> variable_arr;
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
            TMP_optB = variable_arr[5];

            ///B opcióra való ugrás konvertálása
            std::stringstream(variable_arr[6]) >> TMP_jmpB;

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

            ///Visitable
        else if (type == std::string("V"))
        {
            ///küldetéstípus konvertálása
            TMP_type = Visitable;

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
            TMP_optB = variable_arr[7];

            ///B opcióra való ugrás konvertálása
            std::stringstream(variable_arr[8]) >> TMP_jmpB;

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

void FileIO::save(const std::string &savegame, QuestQueue &queue)
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

FileIO::FileIO() : filename("N/A")
{}

FileIO::FileIO(const std::string &filename) : filename(filename)
{}

FileIO::FileIO(const FileIO &rhs) : filename(rhs.filename)
{}

FileIO::~FileIO()
{}

void savegame(int argc, char **argv, Game &game, QuestQueue &queue)
{
    ///"táblatörlés"
    econio_clrscr();

    ///megkérdezzük a felhasználót, hogy mi legyen a mentésfájl neve
    std::cout << "What's the name of the savefile that you would like to save to?: ";
    std::string savefile;
    std::cin >> savefile;;

    ///forrás: http://www.cplusplus.com/forum/beginner/10862/#msg50953
    std::string directory = argv[0];//program full path + name of binary file
    directory.erase(directory.find_last_of('\\') + 1);//remove name of binary file
    ///forrás: http://www.cplusplus.com/forum/beginner/10862/#msg50953

    ///fájlnév hozzáfűzése az elérési úthoz
    directory += savefile;

    ///üres fájl létrehozása
    std::ofstream a(directory);
    a.close();

    ///a mentés meghívása és a kilépés állapotba állás
    game.file.save(savefile, queue);
    queue.getcurrent_state() = -1;
}
