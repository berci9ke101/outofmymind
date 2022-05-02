#ifndef NAGYHF_QUESTQUEUE_H
#define NAGYHF_QUESTQUEUE_H

#include "memtrace.h"

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
     * Kitörli a heterogén kollekciót és ezzel dinamikusan foglalt részeket
     */
     void clear();


    /**
     * Paraméter nélkül hívható konstruktor
     * */
    QuestQueue();


    /**
     * Destruktor
     * */
    ~QuestQueue();
};

/**
 * Összehasonlítja a két Quest ID-jét és igazat ad vissza, ha b azonosítója nagyobb vagy egyenlő a azonosítójánál
 * @param a - mutató az egyik küldetésobjektumra
 * @param b - mutató a másik küldetésobjektumra
 * @return - igaz, ha b ID-je >= a ID-je, hamis, ha b ID-je <> a ID-je
 * */
bool compare(Quest *a, Quest *b);

#endif //NAGYHF_QUESTQUEUE_H
