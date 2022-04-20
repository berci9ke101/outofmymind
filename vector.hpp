#ifndef NAGYHF_VECTOR_HPP
#define NAGYHF_VECTOR_HPP

#include <iostream>

namespace notstd
{
    template<typename T>
    class vector
    {
        T *data;
        size_t siz;
    public:
        ///visszaadja a vektor hosszát
        const size_t size() const;


        ///visszaadja az adott indexén lévő elemet, std::out_of_range hibát dob, alúl vagy túlindexeléskor
        ///------------
        ///nem konstans objektumnál nem konstans referencia
        T &at(size_t n);

        ///konstans objektumnál konstans referencia
        const T &at(size_t n) const;
        ///------------


        ///visszaadja, hogy üres-e a vektor vagy nem
        bool empty() const;


        ///visszaadja a vektor i-edik indezén lévő adattagot
        ///-----------
        ///nem konstans objektumnál nem konstans referencia
        T &operator[](size_t n);

        ///konstans objektumnál konstans referencia
        const T &operator[](size_t n) const;
        ///-----------


        ///a vektor hátuljára beerakja az adattagot
        void push_back(const T &x);

        ///---------->
        ///paraméter nélkül hívható konstruktor
        vector();

        ///konstruktor
        vector(size_t);

        ///másolókonstruktor
        vector(const vector &);

        ///destruktor
        ~vector();
    };

    ////////////////////
    ///---implementáció----///
    ///////////////////

    template<typename T>
    const size_t vector<T>::size() const
    {
        return siz;
    }

    template<typename T>
    T &vector<T>::at(size_t n)
    {
        if (n >= siz)
        {
            throw std::out_of_range("");
        }
        return (*this)[n];
    }

    template<typename T>
    const T &vector<T>::at(size_t n) const
    {
        if (n >= siz or n < 0)
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
    vector<T>::vector(size_t size): data(new T[size]), siz(size)
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
