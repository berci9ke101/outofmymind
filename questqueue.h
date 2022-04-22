#ifndef NAGYHF_QUESTQUEUE_H
#define NAGYHF_QUESTQUEUE_H

#include "quest.h"
#include "vector.hpp"

/**
 * A küldetések tárolásáért és az állapotátmenetekért felelős osztályű
 * (Quest heterogén kollekciója)
 */
class QuestQueue
{
    notstd::vector<Quest *> queue;              ///Maga a heterogén kollekció tömbje
    size_t current_state;                       ///Tárolja a jelenlegi állapotot
public:
    /**
     * Hozzáad egy újabb elemet a tárolóhoz
     * @param quest - Valamilyen Quest-re mutató pointer
     * */
    void add(Quest *quest);


    /**
     * Rendezi a tárolót küldetés ID szerinti növekvő sorrendbe
     * */
    void sort();


    /**
     * Kiválasztja az A opciót és a jelenlegi állapotot arra állítja (next state logika)
     * */
    void chooseA();


    /**
     * Kiválasztja a B opciót és a jelenlegi állapotot arra állítja (next state logika)
     * */
    void chooseB();


    ---???
    void autojmp();

    ///a jelenlegi állapot ID referenciáját adja vissza
    size_t &getcurrent_state();

    ///egy adott indexű elemet ad vissza a tárolóból
    Quest *operator[](size_t);

    //------------------------>
    ///konstruktor
    QuestQueue();

    ///másoló konstruktor
    QuestQueue(const QuestQueue &);

    ///destruktor
    ~QuestQueue();
};

template<class T>
void swap(T &x, T &y);

#endif //NAGYHF_QUESTQUEUE_H
