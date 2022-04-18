#include "quest.h"
#include <vector>
#include <iostream>
#include <sstream>

///-------------------------------///
///az absztrakt küldetés ősosztály///
///-------------------------------///

void Quest::settype(questtype type)
{
    this->type = type;
}

const size_t Quest::getID() const
{
    return ID;
}

const size_t Quest::getjmpA() const
{
    return jmpA;
}

const size_t Quest::getjmpB() const
{
    return jmpB;
}

const size_t Quest::getautojmp() const
{
    return jmpauto;
}

const std::string &Quest::getoptA() const
{
    return optA;
}

const std::string &Quest::getoptB() const
{
    return optB;
}

const std::string &Quest::getdesc() const
{
    return desc;
}

const questtype Quest::gettype() const
{
    return type;
}

Quest::Quest() : type(Simple), ID(-1), desc("N/A"), optA("N/A"), jmpA(-1), optB("N/A"), jmpB(-1), jmpauto(-1)
{}

Quest::Quest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB,
             size_t jmpauto) : type(type), ID(ID), desc(desc), optA(optA), jmpA(jmpA), optB(optB), jmpB(jmpB),
                               jmpauto(jmpauto)
{}

Quest::Quest(const Quest &rhs) : type(rhs.type), ID(rhs.ID), desc(rhs.desc), optA(rhs.optA), jmpA(rhs.jmpA),
                                 optB(rhs.optB), jmpB(rhs.jmpB), jmpauto(rhs.jmpauto)
{}

Quest::~Quest()
{}

///----------------------------///
///az egyszerű küldetés osztály///
///----------------------------///
Quest *SimpleQuest::clone() const
{
    return new SimpleQuest(*this);
}

SimpleQuest::SimpleQuest() : Quest()
{}

SimpleQuest::SimpleQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                         size_t jmpB, size_t jmpauto) : Quest(type, ID, desc, optA, jmpA, optB, jmpB, jmpauto)
{}

SimpleQuest::SimpleQuest(const SimpleQuest &rhs) : Quest(rhs.gettype(), rhs.getID(), rhs.getdesc(), rhs.getoptA(),
                                                         rhs.getjmpA(), rhs.getoptB(), rhs.getjmpB(), rhs.getautojmp())
{}

SimpleQuest::~SimpleQuest()
{}

///------------------------------///
///a látogatható küldetés osztály///
///----------------- ------------///
const std::string &VisitedQuest::getdesc() const
{
    if (gettype() == Visitable)
    {
        return Quest::getdesc();
    }
    else if (gettype() == Visited)
    {
        return alternatedesc;
    }
}

Quest *VisitedQuest::clone() const
{
    return new VisitedQuest(*this);
}

void VisitedQuest::change()
{
    gettype() == Visited ? settype(Visitable) : settype(Visited);
}

VisitedQuest::VisitedQuest() : Quest(), alternatedesc("N/A")
{}

VisitedQuest::VisitedQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                           size_t jmpB, size_t jmpauto, std::string alternatedesc) : Quest(type, ID, desc, optA, jmpA,
                                                                                           optB, jmpB, jmpauto),
                                                                                     alternatedesc(alternatedesc)
{}

VisitedQuest::VisitedQuest(const SimpleQuest &rhs) : Quest(rhs.gettype(), rhs.getID(), rhs.getdesc(), rhs.getoptA(),
                                                           rhs.getjmpA(), rhs.getoptB(), rhs.getjmpB(),
                                                           rhs.getautojmp()), alternatedesc(rhs.getdesc())
{}

VisitedQuest::~VisitedQuest()
{}

///--------------------------------///
///a véletlenszerű küldetés osztály///
///--------------------------------///
const std::string &RandomQuest::getdesc() const
{
    ///a '#' szimbólummal tagolt szöveg szétszedése és belerakása egy dinamikus tömbbe
    std::vector<std::string> stringarr;
    std::istringstream strings(Quest::getdesc());
    std::string s;

    while (getline(strings, s, '#'))
    {
        stringarr.push_back(s);
    }

    ///véletlen sorszámú kiválasztása
    srand(14);

    ///ennek dinamikus foglalása és visszaadása
    std::string *ret = new std::string;
    ret = &stringarr[rand() % stringarr.size()];
    return *ret;
}

Quest *RandomQuest::clone() const
{
    return new RandomQuest(*this);
}

RandomQuest::RandomQuest() : Quest()
{}

RandomQuest::RandomQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                         size_t jmpB, size_t jmpauto) : Quest(type, ID, desc, optA, jmpA, optB, jmpB, jmpauto)
{}

RandomQuest::RandomQuest(const SimpleQuest &rhs) : Quest(rhs.gettype(), rhs.getID(), rhs.getdesc(), rhs.getoptA(),
                                                         rhs.getjmpA(), rhs.getoptB(), rhs.getjmpB(), rhs.getautojmp())
{}

RandomQuest::~RandomQuest()
{}

