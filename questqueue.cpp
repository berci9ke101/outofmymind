#include "memtrace.h"

#include "questqueue.h"
#include <algorithm>

bool compare(Quest *a, Quest *b)
{
    return a->getID() <= b->getID();
}

///-----------------------///
///a küldetéseket tárolója///
///------------------ ----///
void QuestQueue::add(Quest *quest)
{
    queue.push_back(quest);
}

void QuestQueue::sort()
{
    std::sort(queue.begin(), queue.end(), compare);
}

void QuestQueue::chooseA()
{
    ///ez a varázslás elengedhetetlen az elvárt működéshez (elmentjük a jelenlegi állapotot és megváltoztatjuk a következőre, majd a tároló elmentett állapotindexén található küldetés típusát átállítjuk, ha át kell)
    size_t temp_state = current_state;
    current_state = queue[current_state]->getjmpA();

    ///ha most látogatjuk elsőre, akkor jelöljük látogatottnak
    queue[temp_state]->change();

}

void QuestQueue::chooseB()
{
    ///ez a varázslás elengedhetetlen az elvárt működéshez (elmentjük a jelenlegi állapotot és megváltoztatjuk a következőre, majd a tároló elmentett állapotindexén található küldetés típusát átállítjuk, ha át kell)
    size_t temp_state = current_state;
    current_state = queue[current_state]->getjmpB();

    ///ha most látogatjuk elsőre, akkor jelöljük látogatottnak
    queue[temp_state]->change();
}

void QuestQueue::autojmp()
{
    if (queue[current_state]->gettype() == Visited)
    {
        current_state = queue[current_state]->getautojmp();
    }
}

size_t &QuestQueue::getcurrent_state()
{
    return current_state;
}

Quest *QuestQueue::operator[](size_t n)
{
    return queue[n];
}

QuestQueue::QuestQueue() : current_state(0)
{}

QuestQueue::~QuestQueue()
{
    for (size_t i = 0; i < queue.size(); i++)
    {
        delete queue[i];
    }
}

void QuestQueue::clear()
{
    for (size_t i = 0; i < queue.size(); i++)
    {
        delete queue[i];
    }
}
