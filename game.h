#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

#include "memtrace.h"

#include <cstdio>
#include <string>
#include "vector.hpp"

#include "quest.h"
#include "questqueue.h"

/**
 * Fájl hiba kivételosztály
 */
class file_failure : public std::ios_base::failure
{
public:
    /**
     * Konstruktor
     * @param str - a hiba szövege
     */
    file_failure(const std::string &str);


    /**
     * Másolókonstruktor
     * @param rhs - jobbérték
     */
    file_failure(const file_failure &rhs);


    /**
     * Destruktor
     */
    ~file_failure();
};


/**
 * Fájlkezelésért felelős osztály
 */
class FileIO
{
    std::string gamefile;            ///A játékfájl neve
    std::string savefile;            ///A betöltendő mentésfájl neve
public:
    /**
     * Beolvassa a paraméterként kapott játékfájlt, illetve mentésfájlt
     * @param queue - Quest* tárolására alkalmas heterogén kollekció
     * @return - mutató a beolvasott fájl soraira egy 2D-s dinamikus tömbben
     * */
    const notstd::vector<std::string> read(QuestQueue &queue);


    /**
     * Betölti a paraméterként kapott szövegtömbből a küldetéstömbbe a küldetéseket
     * @param sVector - mutató a beolvasott fájl soraira egy 2D-s dinamikus tömbben
     * @param queue - Quest* tárolására alkalmas heterogén kollekció
     * */
    void load(const notstd::vector<std::string> sVector, QuestQueue &queue);


    /**
     * Elmenti a játékállást a paraméterül kapott szöveg néven
     * @param savegame - a mentendő fájl neve
     * @param queue - Quest* tárolására alkalmas heterogén kollekció
     * */
    void save(const std::string &savegame, QuestQueue &queue);


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    FileIO();


    /**
     * Konstruktor
     * @param gamefile - a játékfájl neve
     * @param savefile - a betöltendő mentésfájl neve
     * */
    FileIO(std::string gamefile, std::string savefile);


    /**
     * Másolóonstruktor
     * @param rhs - jobbérték
     * */
    FileIO(const FileIO &rhs);


    /**
     * Destruktor
     * */
    ~FileIO();
};

/**
 * Játékért felelős osztály
 */
class Game
{
    unsigned const int width;       ///A konzolablak szélessége
    unsigned const int height;      ///A konzolablak magassága
    const bool iswin;               ///Ha az operációs rendszer Windows, alapértelmezetten igaz értéket vesz fel
    FileIO file;                    ///Fájlkezelésért felelős objektum
public:
    /**
     * Inicializálja a játékablakot
     * */
    void init() const;


    /**
     * Érzékeli, ha megnyomtak egy gombot a billentyűzeten
     * @return - a lenyomott karakter kódja
     * */
    static int keypress();


    /**
     * Kiírja a paraméterként kapott küldetést a konzolra
     * */
    static void writequest(Quest *);


    /**
     * Visszaad a fájkezelésért felelős objektumra egy referanciát
     *  @return - referencia a fájlkezelésért felelős objektumra
     * */
    FileIO &getfile();


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    Game();


    /**
     * Konstruktor
     * @param gamefile - a játékfájl neve
     * @param savefile - a betöltendő mentésfájl neve
     * @param width - a konzolablak szélessége, alapértelmezetten 119
     * @param height - a konzolablak magassága, alapértelmezetten 25
     * */
    Game(const std::string &gamefile, const std::string &savefile, int width = 119, int height = 25);


    /**
     * Másolóonstruktor
     * @param rhs - jobbérték
     * */
    Game(const Game &);


    /**
     * Destruktor
     * */
    ~Game();
};

/**
 * Játékmentés
 * @param argv - az argumentum vektor
 * @param savename - milyen néven mentse el a játékállást
 * @param queue - Quest* tárolására alkalmas heterogén kollekció
 * */
void savegame(char **argv, Game &savename, QuestQueue &queue);


/**
 * Érzékeli, hogy az operációs rendszer Windows típusú-e
 * */
bool detect();


/**
 * Maga a játék
 * @param argv az argumentumvektor
 * @return - a kilépési kód
 */
int game(char **argv);

#endif //NAGYHF_GAME_H
