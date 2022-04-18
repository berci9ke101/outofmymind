#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

#include <cstdio>
#include <string>
#include <vector>

#include "quest.h"
#include "questqueue.h"

///--------------------------///
///a játékért felelős osztály///
///--------------------------///
class Game
{
    unsigned const int width;
    unsigned const int height;
    const bool iswin;
public:
    ///inicializálja a játékablakot
    void init();

    ///a gombnyomás érzékelésére lett kitalálva
    int keypress();

    ///kiírja a paraméterként kapott küldetést
    void writequest(const Quest &);

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    Game();

    ///konstruktor
    Game(int width, int height);

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
        const std::vector<std::string> &read(const std::string &) const;

        ///betölti a paraméterként kapott játékfájlt
        load(const std::vector<std::string> &sVector, const QuestQueue &queue) const;

        ///elmenti a játékállást
        void save() const;

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
