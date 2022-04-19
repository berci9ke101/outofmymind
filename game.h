#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

#include <cstdio>
#include <string>
#include <vector>

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
    const std::vector<std::string> &read(const std::string &, const std::string &, QuestQueue &);

    ///betölti a paraméterként kapott szövegtömbből a küldetéstömbbe a küldetéseket
    void load(const std::vector<std::string> &sVector, QuestQueue &queue) const;

    ///elmenti a játékállást a paraméterül kapott szöveg néven
    void save(const std::string &, QuestQueue &) const;

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
    void init();

    ///a gombnyomás érzékelésére lett kitalálva
    int keypress();

    ///kiírja a paraméterként kapott küldetést
    void writequest(Quest *);

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    Game();

    ///konstruktor
    Game(std::string filename, int width = 25, int height = 119);

    ///másoló konstruktor
    Game(const Game &);

    ///destruktor
    ~Game();
};

#endif //NAGYHF_GAME_H
