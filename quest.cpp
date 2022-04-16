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

size_t Quest::getjmpA()
{
    return jmpA;
}

size_t Quest::getjmpB()
{
    return jmpB;
}

const std::string &Quest::getoptA()
{
    return optA;
}

const std::string &Quest::getoptB()
{
    return optB;
}

const questtype Quest::gettype()
{
    return type;
}
