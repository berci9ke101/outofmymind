#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

#include <cstdio>
#include <string>
#include "vector.hpp"

#include "quest.h"
#include "questqueue.h"

///-------------------------------///
///a fájkezelésért felelős osztály///
///-------------------------------///
class FileIO
{
    std::string filename;
public:
    ///beolvassa a paraméterként kapott játékfájlt, illetve mentésfájlt
    static const notstd::vector<std::string> &read(const std::string &, const std::string &, QuestQueue &);

    ///betölti a paraméterként kapott szövegtömbből a küldetéstömbbe a küldetéseket
    static void load(const notstd::vector<std::string> &sVector, QuestQueue &queue);

    ///elmenti a játékállást a paraméterül kapott szöveg néven
    static void save(const std::string &, QuestQueue &);

    //------------------------>
    ///paraméter nékül hívható konstruktor
    FileIO();

    ///konstruktor
    FileIO(const std::string &);

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
public:
    ///fájlkezelésért felelős objektum
    FileIO file;

    ///inicializálja a játékablakot
    void init() const;

    ///a gombnyomás érzékelésére lett kitalálva
    static int keypress();

    ///kiírja a paraméterként kapott küldetést
    static void writequest(Quest *);

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    Game();

    ///konstruktor
    Game(const std::string &filename, int width = 25, int height = 119);

    ///másoló konstruktor
    Game(const Game &);

    ///destruktor
    ~Game();
};

///játék elmentése
void savegame(int argc, char **argv, Game& game, QuestQueue& queue);

#endif //NAGYHF_GAME_H
