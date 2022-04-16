#include "questqueue.h"
#include <algorithm>

///-----------------------///
///a küldetéseket tárolója///
///------------------ ----///
void QuestQueue::add(Quest *quest)
{
    queue.push_back(quest);
}

bool compare(const Quest &a, const Quest &b)
{
    return a.getID() > b.getID();
}

void QuestQueue::sort()
{
    std::sort(queue.begin(), queue.end(), compare);
}

void QuestQueue::chooseA()
{
    current_state = queue[current_state]->getjmpA();
}

void QuestQueue::chooseB()
{
    current_state = queue[current_state]->getjmpB();
}

void QuestQueue::autojmp()
{
    current_state = queue[current_state]->getautojmp();
}

const size_t QuestQueue::getcurrent_state() const
{
    return current_state;
}

Quest *QuestQueue::operator[](size_t idx)
{
    ///nem foglalkozunk a hibakezeléssel, mert az std::vector::at() megvéd bennünket a túlindexeléstől
    return queue.at(idx);
}

QuestQueue::QuestQueue() : current_state(0)
{}

QuestQueue::QuestQueue(const QuestQueue &cp) : queue(), current_state(cp.current_state)
{
    for (size_t i = 0; i < cp.queue.size(); i++)
    {
        queue.push_back(cp.queue[i]->clone());
    }
}

QuestQueue::~QuestQueue()
{
    for (size_t i = 0; i < queue.size(); i++)
    {
        delete queue[i];
    }
    current_state = -1;
}
