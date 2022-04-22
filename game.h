#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

#include <cstdio>
#include <string>
#include "vector.hpp"

#include "quest.h"
#include "questqueue.h"

/**
 * Fájlkezelésért felelős osztály
 */
class FileIO
{
    std::string gamefile;            ///A játékfájl neve
    std::string savefile;            ///A betöltendő mentésfájl neve
public:
    ///beolvassa a paraméterként kapott játékfájlt, illetve mentésfájlt
    const notstd::vector<std::string> &read(QuestQueue &queue);

    ///betölti a paraméterként kapott szövegtömbből a küldetéstömbbe a küldetéseket
    void load(const notstd::vector<std::string> &sVector, QuestQueue &queue);

    ///elmenti a játékállást a paraméterül kapott szöveg néven
    void save(const std::string &savegame, QuestQueue &queue);

    //------------------------>
    ///paraméter nékül hívható konstruktor
    FileIO();

    ///konstruktor
    FileIO(std::string gamefile, std::string savefile);

    ///másoló konstruktor
    FileIO(const FileIO &);

    ///destruktor
    ~FileIO();
};


///--------------------------///
///a játékért felelős osztály///
///--------------------------///
class Game
{
    unsigned const int width;
    unsigned const int height;
    const bool iswin;
    ///fájlkezelésért felelős objektum
    FileIO file;
public:
    ///inicializálja a játékablakot
    void init() const;

    ///a gombnyomás érzékelésére lett kitalálva
    static int keypress();

    ///kiírja a paraméterként kapott küldetést
    static void writequest(Quest *);

    ///visszaadja a fájkezelésért felelős objektumot
    FileIO getfile();

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    Game();

    ///konstruktor
    Game(const std::string &gamefile, const std::string &savefile, int width = 119, int height = 25);

    ///másoló konstruktor
    Game(const Game &);

    ///destruktor
    ~Game();
};

///játék elmentése
void savegame(int argc, char **argv, Game &game, QuestQueue &queue);

#endif //NAGYHF_GAME_H
