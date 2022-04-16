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
    size_t ID;
    std::string desc;
    std::string optA;
    std::string optB;
    size_t jmpA;
    size_t jmpB;
public:
    ///beolvassa a küldetést a szövegtömbből
    virtual void read(size_t) = 0;

    ///visszaadja a küldetésst ID-jét
    const size_t getID() const;

    ///visszaadja, hogy a küldetés melyik másik küldetésre ugrik A válaszlehetőség választása esetén
    size_t getjmpA();

    ///visszaadja, hogy a küldetés melyik másik küldetésre ugrik B válaszlehetőség választása esetén
    size_t getjmpB();

    ///visszaadja A válaszlehetőség szövegét
    const std::string &getoptA();

    ///visszaadja B válaszlehetőség szövegét
    const std::string &getoptB();

    ///visszaadja a küldetés leírását
    virtual const std::string &getdesc() = 0;

    ///visszaadja a küüldetés típusát
    const questtype gettype();

    //------------------------>
    ///konstruktor
    Quest();

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
    void read(size_t);

    ///visszaadja a küldetés leírását
    const std::string &getdesc();

    //------------------------>
    ///konstruktor
    SimpleQuest();

    ///másoló konstruktor
    SimpleQuest(const SimpleQuest &);

    ///destruktor
    ~SimpleQuest();
};

class VisitedQuest : public Quest
{
    std::string alternatedesc;
    size_t jmpauto;
public:
    ///beolvassa a küldetést a szövegtömbből
    void read(size_t);

    ///visszaadja a küldetés leírását
    const std::string &getdesc();

    ///megváltoztatja a küldetés típusát "Visitable"-ről "Visited"-re és fordítva
    void change();

    ///visszaadja, hogy az automatikus ugrás melyik másik küldetésre ugrik
    size_t getautojmp();

    //------------------------>
    ///konstruktor
    VisitedQuest();

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
    void read(size_t);

    ///visszaadja a küldetés leírását
    const std::string &getdesc();

    //------------------------>
    ///konstruktor
    RandomQuest();

    ///másoló konstruktor
    RandomQuest(const SimpleQuest &);

    ///destruktor
    ~RandomQuest();
};

#endif //NAGYHF_QUEST_H
