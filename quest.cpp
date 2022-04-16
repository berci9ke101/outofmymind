#include "quest.h"

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

Quest::Quest(const Quest &cp) : type(cp.type), ID(cp.ID), desc(cp.desc), optA(cp.optA), jmpA(cp.jmpA), optB(cp.optB),
                                jmpB(cp.jmpB), jmpauto(cp.jmpauto)
{}

Quest::~Quest()
{}

///----------------------------///
///az egyszerű küldetés osztály///
///----------------------------///
void SimpleQuest::read(size_t) const
{
    ;
}


