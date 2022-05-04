#ifndef NAGYHF_QUEST_H
#define NAGYHF_QUEST_H

#include "memtrace.h"

#include <cstdio>
#include <string>
#include "vector.hpp"


/**
 * A lehetséges küldetéstípusok enumerációja
 * */
enum questtype
{
    Simple, Visitable, Visited, Random
};


/**
 * Az absztrakt küldetés ősosztály
 * */
class Quest
{
protected:
    /**
     * Átállítja  a küldetés típusát
     * @param qtype - lehetséges küldetéstípus
     * */
    void settype(questtype qtype);

private:
    questtype type;                 ///A küldetés típusa
    size_t ID;                      ///A küldetés azonosítója (ID-je)
    std::string desc;               ///A küldetés leírása
    std::string optA;               ///Az 'A' válaszlehetőség szövege
    size_t jmpA;                    ///Az 'A' válaszlehetőség választása esetén, melyik küldetésre ugorjon
    std::string optB;               ///A 'B' válaszlehetőség szövege
    size_t jmpB;                    ///A 'B' válaszlehetőség választása esetén, melyik küldetésre ugorjon
    size_t jmpauto;                 ///Automatikus ugrás esetén, melyik küldetésre ugorjon
public:
    /**
     * Visszaadja a küldetés azonosítóját (ID-jét)
     * @return - Az adott küldetés azonosítója
     * */
    const size_t getID() const;


    /**
     * Visszaadja, hogy a küldetés melyik másik küldetésre ugrik A válaszlehetőség választása esetén, az érték változtatható is
     * @return - Referencia az 'A' ugrásra
     * */
    size_t &getjmpA();


    /**
     * Visszaadja, hogy a küldetés melyik másik küldetésre ugrik B válaszlehetőség választása esetén, az érték változtatható is
     * @return - Referencia a 'B' ugrásra
     * */
    size_t &getjmpB();


    /**
     * Visszaadja, hogy a küldetés melyik másik küldetésre ugrik automatikus ugrás esetén, az érték változtatható is
     * @return - Referencia az automatikus ugrásra
     * */
    size_t &getautojmp();


    /**
     * Visszaadja az 'A' válaszlehetőség szövegét
     * @return - konstans referencia az 'A' válaszlehetőség szövegére
     * */
    const std::string &getoptA() const;


    /**
     * Visszaadja a 'B' válaszlehetőség szövegét
     * @return - konstans referencia a 'B' válaszlehetőség szövegére
     * */
    const std::string &getoptB() const;


    /**
     * Visszaadja a küldetés leírását (azért nem referencia, mert Random küldetéstípusnál dolgozni kell a szöveggel)
     * @return - a küldetés leírása
     * */
    virtual const std::string getdesc() const;


    /**
     * Visszaadja a küldetés típusát
     * @return - a kuldetés típusa
     * */
    const questtype gettype() const;


    /**
     * Megváltoztatja a küldetés típusát 'Visitable'-ről 'Visited'-re, ha a küldetésobjektum 'VisitedQuest'
     * */
    virtual void change();


    /**
     * Létrehoz egy dinamikus másolatot a példányból, egy tisztán virtuális tagfüggvény
     * @return - mutató a dinamikusan másolt objektumra
     * */
    virtual Quest *clone() const = 0;


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    Quest();


    /**
     * Konstruktor
     * @param type - a küldetés típusa
     * @param ID - a küldetés azonosítója
     * @param desc - a küldetés leírása
     * @param optA - az 'A' válaszlehetőség szövege
     * @param jmpA - az 'A' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param optB - a 'B' válaszlehetőség szövege
     * @param jmpB - a 'B' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param jmpauto - automatikus ugrás esetén, melyik küldetésre ugorjon
     * */
    Quest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB,
          size_t jmpauto);


    /**
     * Másolókonstruktor
     * @param rhs - jobbérték
     * */
    Quest(const Quest &rhs);


    /**
     * Destruktor
     * */
    virtual ~Quest();
};

/**
 * Az egyszerű küldetés osztálya
 * */
class SimpleQuest : public Quest
{
public:
    /**
     * Létrehoz egy dinamikus másolatot a példányból
     * @return - mutató a dinamikusan másolt objektumra
     * */
    Quest *clone() const;


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    SimpleQuest();


    /**
     * Konstruktor
     * @param type - a küldetés típusa
     * @param ID - a küldetés azonosítója
     * @param desc - a küldetés leírása
     * @param optA - az 'A' válaszlehetőség szövege
     * @param jmpA - az 'A' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param optB - a 'B' válaszlehetőség szövege
     * @param jmpB  - a 'B' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param jmpauto - automatikus ugrás esetén, melyik küldetésre ugorjon, ALAPÉRTELMEZETT ÉRTÉK: -1
     * */
    SimpleQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                size_t jmpB, size_t jmpauto = -1);


    /**
     * Másolókonstruktor
     * @param rhs - jobbérték
     * */
    SimpleQuest(const SimpleQuest &rhs);


    /**
     * Destruktor
     * */
    ~SimpleQuest();
};

/**
 * A látogatott küldetés osztálya
 * */
class VisitedQuest : public Quest
{
    std::string alternatedesc;              ///A küldetés leírása, ha már látogatva volt
public:
    /**
     * Visszaadja a küldetés leírását
     * @return - a kuldetés leírása
     * */
    const std::string getdesc() const;


    /**
     * Létrehoz egy dinamikus másolatot a példányból
     * @return - mutató a dinamikusan másolt objektumra
     * */
    Quest *clone() const;


    /**
     * Megváltoztatja a küldetés típusát 'Visitable'-ről 'Visited'-re
     * */
    void change();


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    VisitedQuest();


    /**
     * Konstruktor
     * @param type - a küldetés típusa
     * @param ID - a küldetés azonosítója
     * @param desc - a küldetés leírása
     * @param optA - az 'A' válaszlehetőség szövege
     * @param jmpA - az 'A' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param optB - a 'B' válaszlehetőség szövege
     * @param jmpB  - a 'B' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param jmpauto - automatikus ugrás esetén, melyik küldetésre ugorjon
     * @param alternatedesc - a küldetés leírása, ha már látogatva volt
     * */
    VisitedQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                 size_t jmpB, size_t jmpauto, std::string alternatedesc);


    /**
     * Másolókonstruktor
     * @param rhs - jobbérték
     * */
    VisitedQuest(const VisitedQuest &rhs);


    /**
     * Destruktor
     * */
    ~VisitedQuest();
};

/**
 * A véletlen leírású küldetés osztálya
 * */
class RandomQuest : public Quest
{
public:
    /**
     * Visszaadja a küldetés leírását
     * @return - a kuldetés leírása
     * */
    const std::string getdesc() const;


    /**
     * Létrehoz egy dinamikus másolatot a példányból
     * @return - mutató a dinamikusan másolt objektumra
     * */
    Quest *clone() const;


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    RandomQuest();


    /**
     * Konstruktor
     * @param type - a küldetés típusa
     * @param ID - a küldetés azonosítója
     * @param desc - a küldetés leírása
     * @param optA - az 'A' válaszlehetőség szövege
     * @param jmpA - az 'A' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param optB - a 'B' válaszlehetőség szövege
     * @param jmpB  - a 'B' válaszlehetőség választása esetén, melyik küldetésre ugorjon
     * @param jmpauto - automatikus ugrás esetén, melyik küldetésre ugorjon, ALAPÉRTELMEZETT ÉRTÉK: -1
     * */
    RandomQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                size_t jmpB, size_t jmpauto = -1);


    /**
     * Másolókonstruktor
     * @param rhs - jobbérték
     * */
    RandomQuest(const RandomQuest &);


    /**
     * Destruktor
     * */
    ~RandomQuest();
};

#endif //NAGYHF_QUEST_H
