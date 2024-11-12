#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>
#include <stdexcept>

template <typename T>
class MyDeque
{
    T *tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head;  // pierwszy do pobrania
    std::size_t tail;  // pierwsza wolna pozycja
public:
    MyDeque(std::size_t s = 10) : msize(s + 1), head(0), tail(0)
    {
        tab = new T[s + 1];
        assert(tab != nullptr);
    } // default constructor
    ~MyDeque() { delete[] tab; }
    MyDeque(const MyDeque &other); // copy constructor
    MyDeque(MyDeque &&other);      // move constructor NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyDeque &operator=(const MyDeque &other); // copy assignment operator, return *this
    MyDeque &operator=(MyDeque &&other);      // move assignment operator, return *this NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize - 1; }
    void push_front(const T &item);                       // dodanie na początek O(1)
    void push_front(T &&item);                            // dodanie na początek O(1) NIEOBOWIĄZKOWE
    void push_back(const T &item);                        // dodanie na koniec O(1)
    void push_back(T &&item);                             // dodanie na koniec O(1) NIEOBOWIĄZKOWE
    T &front() { return tab[head]; }                      // zwraca poczatek
    T &back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop_front();                                     // usuwa początek kolejki O(1)
    void pop_back();                                      // usuwa koniec kolejki O(1)
    void clear();                                         // czyszczenie listy z elementów
    void display();
    void display_reversed();
    // Operacje z indeksami. NIEOBOWIĄZKOWE
    T &operator[](std::size_t pos);             // podstawienie L[pos]=item, odczyt L[pos]
    const T &operator[](std::size_t pos) const; // dostęp do obiektu const
    void erase(std::size_t pos);
    int index(const T &item);                    // jaki index na liście (-1 gdy nie ma)
    void insert(std::size_t pos, const T &item); // inserts item before pos
    void insert(std::size_t pos, T &&item);      // inserts item before pos
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque &other) : msize(other.msize), head(0), tail(0)
{
    tab = new T[msize];
    if (!other.empty())
    {
        std::size_t el = other.head;
        while (el != other.tail)
        {
            push_back(other.tab[el]);
            el = (el + 1) % msize;
        }
    }
};

template <typename T>
MyDeque<T>::MyDeque(MyDeque &&other) : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail)
{
    tab = other.tab;
    other.tab = nullptr;
    other.head = other.tail = 0;
    other.msize = 1;
};

template <typename T>
MyDeque<T> &MyDeque<T>::operator=(const MyDeque &other)
{
    if (this != &other)
    {
        clear();
        delete[] tab;
        msize = other.msize;
        tab = new T[msize];

        std::size_t el = other.head;
        while (el != other.tail)
        {
            push_back(other.tab[el]);
            el = (el + 1) % msize;
        }
    }
    return *this;
};

template <typename T>
MyDeque<T> &MyDeque<T>::operator=(MyDeque &&other)
{
    if (this != &other)
    {
        clear();
        delete[] tab;
        msize = other.msize;
        tab = other.tab;
        head = other.head;
        tail = other.tail;
        other.tab = nullptr;
        other.msize = 1;
        other.head = other.tail = 0;
    }
    return *this;
};

template <typename T>
void MyDeque<T>::clear()
{
    head = tail = 0;
};

template <typename T>
void MyDeque<T>::push_front(const T &item)
{
    if (full())
    {
        throw std::overflow_error("Deque is full.");
    }
    head = (head + msize - 1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_front(T &&item)
{
    if (full())
    {
        throw std::overflow_error("Deque is full.");
    }
    head = (head + msize - 1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(const T &item)
{
    if (full())
    {
        throw std::overflow_error("Deque is full.");
    }
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::push_back(T &&item)
{
    if (full())
    {
        throw std::overflow_error("Deque is full.");
    }
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back()
{
    if (empty())
    {
        throw std::length_error("Deque is empty.");
    }
    tail = (tail - 1 + msize) % msize;
}

template <typename T>
void MyDeque<T>::pop_front()
{
    if (empty())
    {
        throw std::length_error("Deque is empty.");
    }
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::display()
{
    std::cout << "MyDeque: [ ";
    if (!empty())
    {
        std::size_t el = head;
        while (el != tail)
        {
            std::cout << tab[el] << " ";
            el = (el + 1) % msize;
        }
    }

    std::cout << "]" << std::endl;
}

template <typename T>
void MyDeque<T>::display_reversed()
{
    std::cout << "MyDeque reversed: [ ";
    if (!empty())
    {
        std::size_t el = tail;
        while (el != head)
        {
            el = (el + msize - 1) % msize;
            std::cout << tab[el] << " ";
        }
    }

    std::cout << "]" << std::endl;
}

#endif
