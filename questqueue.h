#ifndef NAGYHF_QUESTQUEUE_H
#define NAGYHF_QUESTQUEUE_H

#include "quest.h"
#include "vector.hpp"

///-----------------------///
///a küldetéseket tárolója///
///------------------ ----///
class QuestQueue
{
    notstd::vector<Quest *> queue;
    size_t current_state;
public:
    ///hozzáad egy újabb elemet a tárolóhoz
    void add(Quest *);

    ///rendezi a tárolót küldetés ID szerinti növekvő sorrendbe
    void sort();

    ///az A opciót választja ki
    void chooseA();

    ///a B opciót választja ki
    void chooseB();

    ///az automatikus ugrást bonyolítja le
    void autojmp();

    ///a jelenlegi állapot ID referenciáját adja vissza
    size_t &getcurrent_state();

    ///egy adott indexű elemet ad vissza a tárolóból
    Quest *operator[](size_t) const;

    //------------------------>
    ///konstruktor
    QuestQueue();

    ///másoló konstruktor
    QuestQueue(const QuestQueue &);

    ///destruktor
    ~QuestQueue();
};

bool compare(const Quest &a, const Quest &b);

#endif //NAGYHF_QUESTQUEUE_H
