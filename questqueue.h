#ifndef NAGYHF_QUESTQUEUE_H
#define NAGYHF_QUESTQUEUE_H

#include "quest.h"
#include "vector.hpp"
#include <vector>

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


    /**
     * Kiválasztja az automatikus ugrás opciót és a jelenlegi állapotot arra állítja (next state logika)
     * */
    void autojmp();


    /**
     * Visszaadja a jelenlegi állapotot
     * @return - referencia a jelenlegi állapotra, hogy változtatható legyen
     * */
    size_t &getcurrent_state();


    /**
     * Egy adott indexű elemet ad vissza a tárolóból
     * @param n - az index
     * @return - egy küldetésre mutató pointer
     * */
    Quest *operator[](size_t n);


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    QuestQueue();


    /**
     * Másolókonstruktor
     * @param rhs - jobbérték
     * */
    QuestQueue(const QuestQueue &rhs);


    /**
     * Destruktor
     * */
    ~QuestQueue();
};

/**
 * Felcseréli a két adattagot
 * @tparam T - felcserélendő adattípus
 * @param x - egyik bemenet
 * @param y - másik bemenet
 * */
template<class T>
void swap(T &x, T &y);

#endif //NAGYHF_QUESTQUEUE_H
