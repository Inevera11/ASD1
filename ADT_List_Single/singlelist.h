// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>  // assert()

template <typename T>
struct SingleNode
{
    // the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T &item, SingleNode *ptr = nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList
{
    SingleNode<T> *head, *tail;

public:
    SingleList() : head(nullptr), tail(nullptr) {}
    ~SingleList(); // tu trzeba wyczyscic wezly

    SingleList(const SingleList &other); // copy constructor
    // usage:   SingleList<int> list2(list1);

    SingleList(SingleList &&other); // move constructor NIEOBOWIAZKOWE
    //  usage:   SingleList<int> list2(std::move(list1));

    SingleList &operator=(const SingleList &other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    SingleList &operator=(SingleList &&other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    int size() const;                        // O(n) bo trzeba policzyc
    void push_front(const T &item);          // O(1), L.push_front(item)
    void push_front(T &&item);               // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T &item);           // O(1), L.push_back(item)
    void push_back(T &&item);                // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE
    T &front() const { return head->value; } // zwraca poczatek, nie usuwa
    T &back() const { return tail->value; }  // zwraca koniec, nie usuwa
    void pop_front();                        // usuwa poczatek O(1)
    void pop_back();                         // usuwa koniec O(n)
    void clear();                            // czyszczenie listy z elementow O(n)
    void display();                          // O(n)
    void reverse();                          // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T &operator[](int pos);             // podstawienie L[pos]=item, odczyt L[pos]
    const T &operator[](int pos) const; // dostep do obiektu const
    void erase(int pos);
    int index(const T &item);            // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T &item); // inserts item before pos,
    void insert(int pos, T &&item);      // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
SingleList<T> &SingleList<T>::operator=(const SingleList &other)
{
    if (this != &other)
    {
        SingleList<T> temp(other);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        // The destructor of `temp` will clean up the old data of `*this`
    }

    return *this;
}

template <typename T>
SingleList<T> &SingleList<T>::operator=(SingleList &&other)
{
    if (this != &other)
    {
        clear(); // Release any existing resources

        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
    }

    return *this;
}

template <typename T>
SingleList<T>::SingleList(SingleList &&other) : head(other.head), tail(other.tail)
{
    other.head = nullptr;
    other.tail = nullptr;
};

template <typename T>
SingleList<T>::SingleList(const SingleList &other) : head(nullptr), tail(nullptr)
{
    if (other.size() > 0)
    {
        head = new SingleNode<T>(other.head->value);
        SingleNode<T> *curr = head;
        SingleNode<T> *templateNode = other.head;
        while (templateNode != other.tail)
        {
            templateNode = templateNode->next;
            SingleNode<T> *nextNode = new SingleNode<T>(templateNode->value);
            curr->next = nextNode;
            curr = nextNode;
        }
        tail = curr;
    }
}

template <typename T>
SingleList<T>::~SingleList()
{
    // I sposob.
    for (SingleNode<T> *node; !empty();)
    {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    head = tail = nullptr;
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <typename T>
void SingleList<T>::reverse()
{

    if (head == tail)
    {
        if (head == nullptr)
            return;

        tail->next = head;
    }

    if (head != tail)
    {
        SingleNode<T> *prev = head;
        SingleNode<T> *curr = head->next;
        while (curr != tail)
        {
            SingleNode<T> *temp_next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp_next;
        }
        tail->next = prev;
    }
    head->next = nullptr;
    SingleNode<T> *temp = head;
    head = tail;
    tail = temp;
}

template <typename T>
void SingleList<T>::clear()
{
    SingleNode<T> *curr = head;
    while (curr->next != nullptr)
    {
        SingleNode<T> *toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    delete curr;
    head = tail = nullptr;
}

template <typename T>
int SingleList<T>::size() const
{
    if (empty())
    {
        return 0;
    }
    else
    {
        int len = 1;
        SingleNode<T> *curr = head;
        while (curr != tail)
        {
            len++;
            curr = curr->next;
        }
        return len;
    }
}
template <typename T>
void SingleList<T>::push_front(const T &item)
{
    if (!empty())
    {
        head = new SingleNode<T>(item, head);
    }
    else
    {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_front(T &&item)
{
    if (!empty())
    {
        head = new SingleNode<T>(std::move(item), head);
    }
    else
    {
        head = tail = new SingleNode<T>(std::move(item));
    }
}

template <typename T>
void SingleList<T>::push_back(const T &item)
{
    if (!empty())
    {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    }
    else
    {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_back(T &&item)
{
    if (!empty())
    {
        tail->next = new SingleNode<T>(std::move(item));
        tail = tail->next;
    }
    else
    {
        head = tail = new SingleNode<T>(std::move(item));
    }
}

template <typename T>
void SingleList<T>::display()
{
    SingleNode<T> *node = head;
    while (node != nullptr)
    {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleList<T>::pop_front()
{
    assert(!empty());
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail)
    { // jeden wezel na liscie
        head = tail = nullptr;
    }
    else
    { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
}

template <typename T>
void SingleList<T>::pop_back()
{
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail)
    { // jeden wezel na liscie
        head = tail = nullptr;
    }
    else
    { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before = head;
        while (before->next != tail)
        {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

#endif