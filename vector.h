#ifndef NAGYHF_VECTOR_H
#define NAGYHF_VECTOR_H

#include <iostream>

namespace notstd
{
    template<typename T>
    class vector
    {
        T *pVec;
        size_t curr_size;
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

        ///a vektor hátuljára beerakja az adattagot (nem konstans adattagra is működik)
        void push_back(T *x);

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
        return curr_size;
    }

    template<typename T>
    T &vector<T>::at(size_t n)
    {
        if (n >= curr_size or n < 0)
        {
            throw std::out_of_range("");
        }
        return (*this)[n];
    }

    template<typename T>
    const T &vector<T>::at(size_t n) const
    {
        if (n >= curr_size or n < 0)
        {
            throw std::out_of_range("");
        }
        return (*this)[n];
    }

    template<typename T>
    bool vector<T>::empty() const
    {
        return curr_size == 0;
    }

    template<typename T>
    T &vector<T>::operator[](size_t n)
    {
        return (*this).pVec[n];
    }

    template<typename T>
    const T &vector<T>::operator[](size_t n) const
    {
        return (*this).pVec[n];
    }

    template<typename T>
    void vector<T>::push_back(const T &x)
    {
        T **temp = new T *[curr_size + 1];
        for (size_t i = 0; i < curr_size; i++)
        {
            temp[i] = pVec[i];
        }

        temp[curr_size++] = x;

        delete[] pVec;
        pVec = temp;
    }

    template<typename T>
    void vector<T>::push_back(T *x)
    {
        T **temp = new T *[curr_size + 1];
        for (size_t i = 0; i < curr_size; i++)
        {
            temp[i] = pVec[i];
        }

        temp[curr_size++] = x;

        delete[] pVec;
        pVec = temp;
    }

    template<typename T>
    vector<T>::vector(): pVec(nullptr), curr_size(0)
    {}

    template<typename T>
    vector<T>::vector(size_t size): pVec(new T[size]), curr_size(size)
    {}

    template<typename T>
    vector<T>::vector(const vector &rhs): pVec(new T[rhs.curr_size]), curr_size(rhs.curr_size)
    {
        for (size_t i = 0; i < curr_size; i++)
        {
            pVec[i] = new T(*(rhs.pVec[i]));
        }
    }

    template<typename T>
    vector<T>::~vector()
    {
        delete[] pVec;
    }


}
#endif //NAGYHF_VECTOR_H
