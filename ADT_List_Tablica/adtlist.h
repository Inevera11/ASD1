#ifndef ADT_LIST_H
#define ADT_LIST_H

#include <algorithm>

#define MIN_SIZE 4

template <typename T>
class ADTList
{
public:
    ADTList(const int size = MIN_SIZE); // c-or
    ~ADTList();                         // d-or
    const T &operator[](const int index) const;
    bool isEmpty();
    int size();
    void push_front(const T &item);
    void push_back(const T &item);
    T pop_front();
    T pop_back();
    const T &front();
    const T &back();
    void insert(const int index, const T &item);
    T erase(const int index);
    void clear();
    void sort();
    void merge(ADTList &obj);

private:
    int capacity;
    int count;
    T *data; // pointer to the data structure
    void resize(const int new_size);
};

#include "adtlist.tpp"
#endif