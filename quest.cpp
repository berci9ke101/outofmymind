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

const questtype Quest::gettype() const
{
    return type;
}

Quest::Quest(size_t ID, std::string desc, std::string optA, size_t jmpA, std::string optB, size_t jmpB, size_t jmpauto)
        : ID(ID), desc(desc), optA(optA), jmpA(jmpA), optB(optB), jmpB(jmpB), jmpauto(jmpauto)
{}
