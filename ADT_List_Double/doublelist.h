// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>  // assert()

template <typename T>
struct DoubleNode
{
    // the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T &item, DoubleNode *nptr = nullptr, DoubleNode *pptr = nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {}                             // destruktor
};

template <typename T>
class DoubleList
{
    DoubleNode<T> *head, *tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList &other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList &&other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList &operator=(const DoubleList &other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList &operator=(DoubleList &&other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    std::size_t size() const;                // O(n) bo trzeba policzyc
    void push_front(const T &item);          // O(1)
    void push_front(T &&item);               // O(1) NIEOBOWIAZKOWE
    void push_back(const T &item);           // O(1)
    void push_back(T &&item);                // O(1) NIEOBOWIAZKOWE
    T &front() const { return head->value; } // zwraca poczatek, nie usuwa
    T &back() const { return tail->value; }  // zwraca koniec, nie usuwa
    void pop_front();                        // usuwa poczatek O(1)
    void pop_back();                         // usuwa koniec O(1)
    void clear();                            // czyszczenie listy z elementow O(n)
    void display();                          // O(n)
    void display_reversed();                 // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T &operator[](std::size_t pos);             // podstawienie L[pos]=item, odczyt L[pos]
    const T &operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T &item);                    // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T &item); // inserts item before pos,
    void insert(std::size_t pos, T &&item);      // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
DoubleList<T>::DoubleList(const DoubleList &other) : head(nullptr), tail(nullptr)
{
    if (other.head)
    {
        head = new DoubleNode<T>(other.head->value);
        tail = head;
        DoubleNode<T> *otherCurr = other.head->next;
        while (otherCurr != nullptr)
        {
            push_back(otherCurr->value);
            otherCurr = otherCurr->next;
        }
    }
}

template <typename T>
DoubleList<T>::DoubleList(DoubleList &&other) : head(other.head), tail(other.tail)
{
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
DoubleList<T>::~DoubleList()
{
    while (!empty())
    {
        pop_front();
    }
}

template <typename T>
DoubleList<T> &DoubleList<T>::operator=(const DoubleList &other)
{
    if (this == &other) // Self-assignment check
        return *this;

    clear(); // Delete existing nodes to avoid memory leaks

    if (other.empty())
    {
        head = tail = nullptr;
        return *this;
    }
    head = new DoubleNode<T>(other.head->value);
    tail = head;
    DoubleNode<T> *otherCurr = other.head->next;
    while (otherCurr != nullptr)
    {
        push_back(otherCurr->value);
        otherCurr = otherCurr->next;
    }
    return *this;
};

template <typename T>
DoubleList<T> &DoubleList<T>::operator=(DoubleList &&other)
{
    if (this == &other)
        return *this;

    clear(); // Delete existing nodes to avoid memory leaks

    if (other.empty())
    {
        head = tail = nullptr;
        return *this;
    }
    head = other.head;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
    return *this;
};

template <typename T>
std::size_t DoubleList<T>::size() const
{
    size_t len = 0;
    DoubleNode<T> *curr = head;
    while (curr != nullptr)
    {
        ++len;
        curr = curr->next;
    }
    return len;
}

template <typename T>
void DoubleList<T>::display()
{
    DoubleNode<T> *curr = head;
    while (curr != nullptr)
    {
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
};

template <typename T>
void DoubleList<T>::display_reversed()
{
    DoubleNode<T> *curr = tail;
    while (curr != nullptr)
    {
        std::cout << curr->value << " ";
        curr = curr->prev;
    }
    std::cout << std::endl;
};

template <typename T>
void DoubleList<T>::pop_front()
{
    if (!empty())
    {
        DoubleNode<T> *newHead = head->next;
        delete head;
        head = newHead;
        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
    }
};

template <typename T>
void DoubleList<T>::pop_back()
{
    if (!empty())
    {
        DoubleNode<T> *newTail = tail->prev;
        delete tail;
        tail = newTail;
        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
    }
};

template <typename T>
void DoubleList<T>::clear()
{
    while (!empty())
    {
        pop_back();
    }
};

template <typename T>
void DoubleList<T>::push_front(const T &item)
{
    if (!empty())
    {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    }
    else
    {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_back(const T &item)
{
    if (!empty())
    {
        tail = new DoubleNode<T>(item, nullptr, tail);
        tail->prev->next = tail;
    }
    else
    {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T &&item)
{
    if (!empty())
    {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    }
    else
    {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::push_back(T &&item)
{
    if (!empty())
    {
        tail = new DoubleNode<T>(std::move(item), nullptr, tail);
        tail->prev->next = tail;
    }
    else
    {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

#endif

// EOF