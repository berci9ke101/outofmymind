#ifndef NAGYHF_QUEST_H
#define NAGYHF_QUEST_H

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
     * @return - a kuldetés leírása
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
     * Létrehoz egy dinamikus másolatot a példányból ('Quest' osztály leszármazottjainál működik)
     * @return - mutató a dinamikusan másolt objektumra
     * */
    virtual Quest *clone() const = 0;


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    Quest();

    ///konstruktor
    Quest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB,
          size_t jmpauto);

    ///másoló konstruktor
    Quest(const Quest &);

    ///destruktor
    virtual ~Quest();
};

///----------------------------///
///az egyszerű küldetés osztály///
///----------------------------///
class SimpleQuest : public Quest
{
public:
    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    SimpleQuest();

    ///konstruktor
    SimpleQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                size_t jmpB, size_t jmpauto = -1);

    ///másoló konstruktor
    SimpleQuest(const SimpleQuest &);

    ///destruktor
    ~SimpleQuest();
};

///------------------------------///
///a látogatható küldetés osztály///
///----------------- ------------///
class VisitedQuest : public Quest
{
    std::string alternatedesc;
public:
    ///visszaadja a küldetés leírását
    const std::string getdesc() const;

    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

    ///megváltoztatja a küldetés típusát "Visitable"-ről "Visited"-re
    void change();

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    VisitedQuest();

    ///konstruktor
    VisitedQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                 size_t jmpB, size_t jmpauto, std::string alternatedesc);

    ///másoló konstruktor
    VisitedQuest(const VisitedQuest &);

    ///destruktor
    ~VisitedQuest();
};

///--------------------------------///
///a véletlenszerű küldetés osztály///
///--------------------------------///
class RandomQuest : public Quest
{
public:
    ///visszaadja a küldetés leírását, FONTOS: a használónak kell felszabdítani a dinamikusan foglalt részt
    const std::string getdesc() const;

    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    RandomQuest();

    ///konstruktor
    RandomQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                size_t jmpB, size_t jmpauto = -1);

    ///másoló konstruktor
    RandomQuest(const RandomQuest &);

    ///destruktor
    ~RandomQuest();
};

#endif //NAGYHF_QUEST_H
