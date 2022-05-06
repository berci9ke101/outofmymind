#include "memtrace.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

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

int game(char **argv)
{
    ///megkérdezzük a felhasználót, hogy mi a játékfájl neve
    std::cout << "What's the name of the gamefile that you would like to load?: ";
    std::string gamefile;
    std::cin >> gamefile;

    ///megkérdezzük a felhasználót, hogy mi a mentésfájl neve
    std::cout << "What's the name of the savefile that you would like to load?: ";
    std::string savefile;
    std::cin >> savefile;

    ///létrehozunk egy heterogén kollekciót a küldetéseknek
    QuestQueue qq;

    ///random "magzása"
    srand(time(0));

    ///létrehozunk egy játékfájlt
    Game playgame(gamefile, savefile);

    ///inicializáljuk a játékablakot
    playgame.init();

    ///beolvassuk a játékot
    try
    {
        ///pontosabban megpróbáljuk beolvasni
        playgame.getfile().load(playgame.getfile().read(qq), qq);
    } catch (file_failure &failure)
    {
        ///ha nem lehetett a fájlt megnyitni, akkor hibát írunk a felhasználónak
        std::cout << "\n\nCould not open load file!\n\nPress any button to exit!\n\n";

        ///bemeneti módra állítjuk
        econio_rawmode();
        econio_getch();

        ///és kilépünk -1 hibakóddal
        return -1;
    } catch (std::logic_error &error)
    {
        ///ha üres a fájl akkor hibát írunk a felhasználónak
        std::cout << "\n\nLoad file is empty or corrupted!\n\nPress any button to exit!\n\n";

        ///bemeneti módra állítjuk
        econio_rawmode();
        econio_getch();

        ///és kilépünk -2 hibakóddal és felszabadítjuk a küldetéseket
        return -2;
    } catch (std::exception &e)
    {
        ///ismeretlen hiba történt
        std::cout << "\n\nAn unknown error occured!\n\nPress any button to exit!\n\n";

        ///bemeneti módra állítjuk
        econio_rawmode();
        econio_getch();

        ///és kilépünk -3 hibakóddal
        return -3;
    }


    ///rendezzük a tárolót
    qq.sort();


    ///maga a játékloop, a -1 állapot a kilépési feltételünk
    size_t exit_state = -1;
    while (qq.getcurrent_state() != exit_state)
    {
        ///a jelenlegi küldetés szövegét kiírjuk
        playgame.writequest(qq[qq.getcurrent_state()]);

        ///miután megtörtént a gombnyomás, ha esetleg a küldetés már látogatott, autougrunk
        qq.autojmp();

        ///várakozunk gomnyomásra
        int keyboardinput = playgame.keypress();

        switch (keyboardinput)
        {
            case 'a':
                qq.chooseA();
                break;
            case 'b':
                qq.chooseB();
                break;
#ifndef CPORTA
            case KEY_ESCAPE:
#endif
                ///ez azért kell, hogy a CPORTA x billentyűvel tudjon menteni
#ifdef CPORTA
                case 'x':
#endif
                ///megpróbáljuk elmenteni az állást
                try
                {
                    savegame(argv, playgame, qq);
                } catch (std::ios_base::failure &failure)
                {
                    ///ha nem sikerül akkor hibát írunk a felhasználónak
                    econio_clrscr();
                    std::cout << "\n\nCouldn't save gamestate!\n\nPress any button to exit!\n\n";

                    ///bemeneti módra állítjuk
                    econio_rawmode();
                    econio_getch();

                    ///kilépünk -3 hibakóddal
                    return -3;
                }
                break;
        }
    }
    return 0;
}

void savegame(char **argv, Game &savename, QuestQueue &queue)
{
    ///"táblatörlés"
    econio_clrscr();

    ///megkérdezzük a felhasználót, hogy mi legyen a mentésfájl neve
    std::cout << "What's the name of the savefile that you would like to save to?: ";
    std::string savefile;
    std::cin >> savefile;

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
    savename.getfile().save(savefile, queue);
    queue.getcurrent_state() = -1;
}


///------------------------///
///Fájl hiba kivételosztály///
///------------------------///

file_failure::file_failure(const std::string &str) : std::ios_base::failure(str)
{}

file_failure::file_failure(const file_failure &rhs) : std::ios_base::failure(rhs.what())
{}

file_failure::~file_failure()
{}


///--------------------------///
///a játékért felelős osztály///
///--------------------------///
void Game::init() const
{
    ///Ha az operációs rendszer Windows, akkor annak megfelelően inicializáljuk a konzolt
    if (iswin)
    {
#ifdef WIN32
        ///A VT100 konzol engedélyezése
        ///forrás: http://salvi.chaosnet.org/texts/vt100.html
        // Enable VT100 escape control characters on Windows
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode;
        GetConsoleMode(hOutput, &dwMode);
        dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOutput, dwMode);
        ///forrás: http://salvi.chaosnet.org/texts/vt100.html


        ///kurzor eltűntetése
        HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursor;
        GetConsoleCursorInfo(outhandle, &cursor);
        cursor.bVisible = FALSE;
        SetConsoleCursorInfo(outhandle, &cursor);


        ///ablak kódolásának megváltoztatása és átnevezése
        UINT original_cp = GetConsoleCP();
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        SetConsoleTitle("Out Of My Mind");
        SetConsoleCP(original_cp);
#endif
    }
    ///inicializáljuk az ablak méretét
    ///ablak méretének beállítása VT100 escape karakter szekvenciákkal
#ifndef CPORTA
    std::cout << "\x1b[8;" << height << ';' << width << 't';
#endif

    ///billentyű lenyomás érzékelése miatt kel
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
    std::cout << rhs->getdesc();

    ///ha nem látogatott a küldetés csak akkor írjuk ki a szöveget
    if (rhs->gettype() != Visited)
    {
        econio_gotoxy(0, 14);
        std::cout << "A: " << rhs->getoptA();

        econio_gotoxy(0, 17);
        std::cout << "B: " << rhs->getoptB();

        econio_gotoxy(43, 22);
        std::cout << "A button       -  select option A";
        econio_gotoxy(43, 23);
        std::cout << "B button       -  select option B";
    }

    ///"help menu"
    econio_gotoxy(43, 24);
    std::cout << "ESCAPE button  -    save and exit";
}

Game::Game() : width(25), height(119), iswin(detect()), file()
{}

Game::Game(const std::string &gamefile, const std::string &savefile, int width, int height) : width(width),
                                                                                              height(height),
                                                                                              iswin(detect()),
                                                                                              file(gamefile, savefile)
{}

Game::Game(const Game &rhs) : width(rhs.width), height(rhs.height), iswin(rhs.iswin), file(rhs.file)
{}

Game::~Game()
{}

FileIO &Game::getfile()
{
    return file;
}


///-------------------------------///
///a fájkezelésért felelős osztály///
///-------------------------------///
const notstd::vector<std::string> FileIO::read(QuestQueue &queue)
{
    ///fájl megnyitása
    std::ifstream GAME;
    GAME.open(gamefile, std::ios::in);

    ///ha nem lehet megnyitni a fájlt...
    if (not(GAME.is_open()))
    {
        ///kivételt dobunk
        GAME.close();
        throw file_failure("Could not open file!");
    }

    ///beolvasás, ha nincs hiba
    std::string line;
    notstd::vector<std::string> sVector;
    while (getline(GAME, line))
    {
        ///ha nem volt üres a sor, akkor belerakjuk a stringbe
        if (line != std::string(""))
        {
            sVector.push_back(line);
        }
    }

    ///ha üres a fájl...
    if (sVector.empty())
    {
        ///kivételt dobunk
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
    return sVector;
}

void FileIO::load(const notstd::vector<std::string> sVector, QuestQueue &queue)
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
        throw file_failure("Could not open file!");
    }

    ///kiírás, ha nincs hiba
    SAVE << queue.getcurrent_state() << "\n";

    ///a fájl bezárása
    SAVE.close();
}

FileIO::FileIO() : gamefile("N/A"), savefile("N/A")
{}

FileIO::FileIO(std::string gamefile, std::string savefile) : gamefile(std::move(gamefile)),
                                                             savefile(std::move(savefile))
{}

FileIO::FileIO(const FileIO &rhs) : gamefile(rhs.gamefile), savefile(rhs.savefile)
{}

FileIO::~FileIO()
{}
