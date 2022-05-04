#include "memtrace.h"

#include "quest.h"
#include "vector.hpp"
#include <utility>
#include <vector>
#include <iostream>
#include <sstream>

///-------------------------------///
///az absztrakt küldetés ősosztály///
///-------------------------------///

void Quest::settype(questtype qtype)
{
    (*this).type = qtype;
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

size_t &Quest::getautojmp()
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

const std::string Quest::getdesc() const
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
             size_t jmpauto) : type(type), ID(ID), desc(std::move(desc)), optA(std::move(optA)), jmpA(jmpA),
                               optB(std::move(optB)), jmpB(jmpB), jmpauto(jmpauto)
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
                         size_t jmpB, size_t jmpauto) : Quest(type, ID, std::move(desc), std::move(optA), jmpA,
                                                              std::move(optB), jmpB, jmpauto)
{}

SimpleQuest::SimpleQuest(const SimpleQuest &rhs) : Quest(rhs)
{}

SimpleQuest::~SimpleQuest()
{}

///------------------------------///
///a látogatható küldetés osztály///
///----------------- ------------///
const std::string VisitedQuest::getdesc() const
{
    if (gettype() == Visitable)
    {
        return Quest::getdesc();
    }
    return alternatedesc;
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
                           size_t jmpB, size_t jmpauto, std::string alternatedesc) : Quest(type, ID, std::move(desc),
                                                                                           std::move(optA), jmpA,
                                                                                           std::move(optB), jmpB,
                                                                                           jmpauto), alternatedesc(
        std::move(alternatedesc))
{}

VisitedQuest::VisitedQuest(const VisitedQuest &rhs) : Quest(rhs), alternatedesc(rhs.alternatedesc)
{}

VisitedQuest::~VisitedQuest()
{}

///--------------------------------///
///a véletlenszerű küldetés osztály///
///--------------------------------///
const std::string RandomQuest::getdesc() const
{
    ///a '#' szimbólummal tagolt szöveg szétszedése
    notstd::vector<std::string> stringarr;
    std::string tmp = Quest::getdesc();
    std::istringstream strings(tmp);
    std::string s;

    /// és belerakása egy dinamikus tömbbe
    while (getline(strings, s, '#'))
    {
        ///ha nem volt üres a string, akkor belerakjuk a vektorba
        if (s != std::string(""))
        {
            stringarr.push_back(s);
        }

    }

    ///ebből egy véletlen visszaadása
    return stringarr[rand() % stringarr.size()];
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

