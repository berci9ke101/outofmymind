#ifndef NAGYHF_QUEST_H
#define NAGYHF_QUEST_H

#include <cstdio>
#include <string>

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
    const size_t ID;
    const std::string desc;
    const std::string optA;
    const size_t jmpA;
    const std::string optB;
    const size_t jmpB;
    const size_t jmpauto;
public:
    ///beolvassa a küldetést a szövegtömbből
    virtual void read(size_t) const = 0;

    ///visszaadja a küldetésst ID-jét
    const size_t getID() const;

    ///visszaadja, hogy a küldetés melyik másik küldetésre ugrik A válaszlehetőség választása esetén
    const size_t getjmpA() const;

    ///visszaadja, hogy a küldetés melyik másik küldetésre ugrik B válaszlehetőség választása esetén
    const size_t getjmpB() const;

    ///visszaadja az automatikus ugrás értékét
    virtual const size_t getautojmp() const;

    ///visszaadja A válaszlehetőség szövegét
    const std::string &getoptA() const;

    ///visszaadja B válaszlehetőség szövegét
    const std::string &getoptB() const;

    ///visszaadja a küldetés leírását
    virtual const std::string &getdesc() const;

    ///visszaadja a küüldetés típusát
    const questtype gettype() const;

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
    ///beolvassa a küldetést a szövegtömbből
    void read(size_t) const;

    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    SimpleQuest();

    ///konstruktor
    SimpleQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB,
    size_t jmpauto);

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
    ///beolvassa a küldetést a szövegtömbből
    void read(size_t) const;

    ///visszaadja a küldetés leírását
    const std::string &getdesc() const;

    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

    ///megváltoztatja a küldetés típusát "Visitable"-ről "Visited"-re és fordítva
    void change();

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    VisitedQuest();

    ///konstruktor
    VisitedQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB,
    size_t jmpauto, std::string alternatedesc);

    ///másoló konstruktor
    VisitedQuest(const SimpleQuest &);

    ///destruktor
    ~VisitedQuest();
};

///--------------------------------///
///a véletlenszerű küldetés osztály///
///--------------------------------///
class RandomQuest : public Quest
{
public:
    ///beolvassa a küldetést a szövegtömbből
    void read(size_t) const;

    ///létrehoz egy dinamikus másolatot a példányból
    Quest *clone() const;

    //------------------------>
    ///paraméter nélkül hívható konstruktor
    RandomQuest();

    ///konstruktor
    RandomQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB,
    size_t jmpauto);

    ///másoló konstruktor
    RandomQuest(const SimpleQuest &);

    ///destruktor
    ~RandomQuest();
};

#endif //NAGYHF_QUEST_H
