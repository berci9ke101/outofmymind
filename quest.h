#ifndef NAGYHF_QUEST_H
#define NAGYHF_QUEST_H

#include <cstdio>
#include <string>
#include "vector.hpp"

///a küldetéstípusok felsorolása
enum questtype
{
    Simple, Visitable, Visited, Random
};

///-------------------------------///
///az absztrakt küldetés ősosztály///
///-------------------------------///
class Quest
{
protected:
    ///a küldetés típusát állítja át
    void settype(questtype type);

private:
    questtype type;
    size_t ID;
    std::string desc;
    std::string optA;
    size_t jmpA;
    std::string optB;
    size_t jmpB;
    size_t jmpauto;
public:
    ///visszaadja a küldetésst ID-jét
    const size_t getID() const;

    ///visszaadja, hogy a küldetés melyik másik küldetésre ugrik A válaszlehetőség választása esetén
    const size_t getjmpA() const;

    ///visszaadja, hogy a küldetés melyik másik küldetésre ugrik B válaszlehetőség választása esetén
    const size_t getjmpB() const;

    ///visszaadja az automatikus ugrás értékét
    const size_t getautojmp() const;

    ///visszaadja A válaszlehetőség szövegét
    const std::string &getoptA() const;

    ///visszaadja B válaszlehetőség szövegét
    const std::string &getoptB() const;

    ///visszaadja a küldetés leírását
    virtual std::string *getdesc() const;

    ///visszaadja a küüldetés típusát
    const questtype gettype() const;

    ///megváltoztatja a küldetés típusát "Visitable"-ről "Visited"-re
    void change();

    ///létrehoz egy dinamikus másolatot a példányból
    virtual Quest *clone() const = 0;

    //------------------------>
    ///paraméter nélkül hívható konstruktor
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
    std::string *getdesc() const;

    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

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
    std::string *getdesc() const;

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
