#include "questqueue.h"

template<class T>
void swap(T &x, T &y)
{
    T temp;
    temp = x;
    x = y;
    y = temp;
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
    size_t i, j;
    size_t n = queue.size();
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (queue[j]->getID() > queue[j + 1]->getID())
            {
                swap(queue[j], queue[j + 1]);
            }
        }
    }
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
    ///nem foglalkozunk a hibakezeléssel, mert az notstd::vector::at() megvéd bennünket a túlindexeléstől
    return queue.at(n);
}

QuestQueue::QuestQueue() : current_state(0)
{}

QuestQueue::QuestQueue(const QuestQueue &rhs) : queue(), current_state(rhs.current_state)
{
    for (size_t i = 0; i < rhs.queue.size(); i++)
    {
        queue.push_back(rhs.queue[i]->clone());
    }
}

QuestQueue::~QuestQueue()
{
    for (size_t i = 0; i < queue.size(); i++)
    {
        delete queue[i];
    }
}
