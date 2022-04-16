#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

#include <cstdio>
#include <string>
#include "quest.h"

///--------------------------///
///a játékért felelős osztály///
///--------------------------///
class Game
{
    unsigned const int height;
    unsigned const int width;
    const bool iswin;
public:
    ///inicializálja a játékablakot
    void init();

    ///a gombnyomás érzékelésére lett kitalálva
    int keypress();

    ///kiírja a paraméterként kapott küldetést
    void writequest(const Quest &);

    //------------------------>
    ///konstruktor
    Game();

    ///másoló konstruktor
    Game(const Game &);

    ///destruktor
    ~Game();

    ///-------------------------------///
    ///a fájkezelésért felelős osztály///
    ///-------------------------------///
    class FileIO
    {
        std::string filename;
    public:
        ///beolvassa a paraméterként kapott játékfájlt
        void read(const std::string &);

        ///elmenti a játékállást
        void save();

        ///betölti a paraméterként kapott játékfájlt
        void load(const std::string &);

        //------------------------>
        ///konstruktor
        FileIO();

        ///másoló konstruktor
        FileIO(const FileIO &);

        ///destruktor
        ~FileIO();
    };
};

#endif //NAGYHF_GAME_H
