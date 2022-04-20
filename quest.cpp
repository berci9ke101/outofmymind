#include "quest.h"
#include "vector.hpp"
#include <iostream>
#include <sstream>

///-------------------------------///
///az absztrakt küldetés ősosztály///
///-------------------------------///

void Quest::settype(questtype type)
{
    (*this).type = type;
}

void Quest::change()
{}

const size_t Quest::getID() const
{
    return ID;
}

size_t &Quest::getjmpA()
{
    return jmpA;
}

size_t &Quest::getjmpB()
{
    return jmpB;
}

size_t Quest::getautojmp()
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

std::string *Quest::getdesc() const
{
    return new std::string(desc);
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

SimpleQuest::SimpleQuest(const SimpleQuest &rhs) : Quest(rhs)
{}

SimpleQuest::~SimpleQuest()
{}

///------------------------------///
///a látogatható küldetés osztály///
///----------------- ------------///
std::string *VisitedQuest::getdesc() const
{
    if (gettype() == Visitable)
    {
        return Quest::getdesc();
    }
    return new std::string(alternatedesc);
}

Quest *VisitedQuest::clone() const
{
    return new VisitedQuest(*this);
}

void VisitedQuest::change()
{
    (*this).getjmpB() = (*this).getautojmp();
    (*this).getjmpA() = (*this).getautojmp();
    (*this).settype(Visited);
}

VisitedQuest::VisitedQuest() : Quest(), alternatedesc("N/A")
{}

VisitedQuest::VisitedQuest(questtype type, size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB,
                           size_t jmpB, size_t jmpauto, std::string alternatedesc) : Quest(type, ID, desc, optA, jmpA,
                                                                                           optB, jmpB, jmpauto),
                                                                                     alternatedesc(alternatedesc)
{}

VisitedQuest::VisitedQuest(const VisitedQuest &rhs) : Quest(rhs), alternatedesc(rhs.alternatedesc)
{}

VisitedQuest::~VisitedQuest()
{}

///--------------------------------///
///a véletlenszerű küldetés osztály///
///--------------------------------///
std::string *RandomQuest::getdesc() const
{
    ///a '#' szimbólummal tagolt szöveg szétszedése és belerakása egy dinamikus tömbbe
    notstd::vector<std::string> stringarr;
    std::string *sp = Quest::getdesc();
    std::string tmp = *sp;
    std::istringstream strings(tmp);
    std::string s;

    while (getline(strings, s, '#'))
    {
        stringarr.push_back(s);
    }

    ///kitöröljük a dinamikusan foglalt string részt
    delete sp;

    ///véletlen sorszámú kiválasztása
    srand(14);

    ///ennek dinamikus foglalása és visszaadása
    std::string ret = stringarr[rand() % stringarr.size()];
    std::string *ret_ptr = new std::string;
    *ret_ptr = ret;

    return ret_ptr;
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

RandomQuest::RandomQuest(const RandomQuest &rhs) : Quest(rhs)
{}

RandomQuest::~RandomQuest()
{}

