#ifndef NAGYHF_VECTOR_HPP
#define NAGYHF_VECTOR_HPP

#include "memtrace.h"

namespace notstd
{
/**
 * Dinamikus méretű generikus tömb.
 * @tparam T - tárolt adattípus
 */

    template<typename T>
    class vector
    {
        T *data;             ///A vektor tömbjének pointere
        size_t siz;          ///A jelenlegi maximális méret értéke
    public:
        /**
         * Visszaadja az elemek tényleges számát
         * @return - ténylegesen tárolt elemek száma
         * */
        const size_t size() const;

        /**
         * Visszaadja, hogy üres-e a vektor vagy nem
         * @return - logikai változó az ürességre
         * */
        bool empty() const;


        /**
         * Iterátor a vektor elejére
         * @return - egy iterátor a vektor első elemére
         */
        T *begin();


        /**
         * Iterátor a vektor utolsó utáni elemére
         * @return - egy iterátor a vektor utolsó utáni
         */
        T *end();


        /**
         * Visszaadja a vektor n-edik indexén lévő elemet,
         * std::out_of_range kivételt dob alúl vagy túlindexeléskor
         * @param n - az index
         * @return - referencia az n-edik indexű elemre
         * */
        T &at(size_t n);


        /**
         * Visszaadja a konstans vektor n-edik indexén lévő elemet,
         * std::out_of_range kivételt dob alúl vagy túlindexeléskor
         * @param n - az index
         * @return - konstans referencia az n-edik indexű elemre
         * */
        const T &at(size_t n) const;


        /**
         * Visszaadja a vektor n-edik indexén lévő elemet
         * @param n - az index
         * @return - referencia az n-edik indexű elemre
         * */
        T &operator[](size_t n);


        /**
         * Visszaadja a konstans vektor n-edik indexén lévő elemet
         * @param n - az index
         * @return - konstans referencia az n-edik indexű elemre
         * */
        const T &operator[](size_t n) const;


        /**
         * A vektor hátuljára beerakja az adattagot
         * @param x - berakandó adattag
         * */
        void push_back(const T &x);


        /**
         * Paraméter nélkül hívható konstruktor
         * */
        vector();


        /**
         * Másolókonstruktor
         * @param rhs - jobbérték
         * */
        vector(const vector &rhs);


        /**
         * Destruktor
         * */
        ~vector();
    };

    template<typename T>
    const size_t vector<T>::size() const
    {
        return siz;
    }

    template<typename T>
    T *vector<T>::begin()
    {
        return data;
    }

    template<typename T>
    T *vector<T>::end()
    {
        return data + siz;
    }

    template<typename T>
    T &vector<T>::at(size_t n)
    {
        ///túlindexeléskor std::out_of_range kivételt dobunk
        if (n >= siz)
        {
            throw std::out_of_range("");
        }
        return (*this)[n];
    }

    template<typename T>
    const T &vector<T>::at(size_t n) const
    {
        ///túlindexeléskor std::out_of_range kivételt dobunk
        if (n >= siz)
        {
            throw std::out_of_range("");
        }
        return (*this)[n];
    }

    template<typename T>
    bool vector<T>::empty() const
    {
        return siz == 0;
    }

    template<typename T>
    T &vector<T>::operator[](size_t n)
    {
        return (*this).data[n];
    }

    template<typename T>
    const T &vector<T>::operator[](size_t n) const
    {
        return (*this).data[n];
    }

    template<typename T>
    void vector<T>::push_back(const T &x)
    {
        T *temp = new T[siz + 1];
        for (size_t i = 0; i < siz; i++)
        {
            temp[i] = data[i];
        }

        temp[siz++] = x;

        delete[] data;
        data = temp;
    }

    template<typename T>
    vector<T>::vector(): data(nullptr), siz(0)
    {}

    template<typename T>
    vector<T>::vector(const vector &rhs): data(new T[rhs.siz]), siz(rhs.siz)
    {
        for (size_t i = 0; i < siz; i++)
        {
            data[i] = rhs.data[i];
        }
    }

    template<typename T>
    vector<T>::~vector()
    {
        delete[] data;
    }
}
#endif //NAGYHF_VECTOR_HPP
