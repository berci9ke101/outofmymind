#include "questqueue.h"
#include <algorithm>

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
    std::sort(queue.begin(), queue.end(),)
}
