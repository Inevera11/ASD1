#include "adtlist.h"
#include <iostream>
#include <stdexcept>

template <typename T>
ADTList<T>::ADTList(const int size)
    : capacity{size}, count{0}
{
    if (size < 2)
        throw std::invalid_argument("Minimalny rozmiar musi być co najmniej 2.");
    data = new T[capacity];
}

template <typename T>
const T &ADTList<T>::operator[](const int index) const
{
    if (index >= count)
        throw std::invalid_argument("Index out of range.");
    return data[index];
};

template <typename T>
bool ADTList<T>::isEmpty()
{
    return (count == 0);
};

template <typename T>
int ADTList<T>::size()
{
    return count;
};

template <typename T>
void ADTList<T>::resize(const int new_size)
{
    if (new_size < 4)
        return;
    T *new_data = new T[new_size];
    for (int i = 0; i < count; ++i)
    {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_size;
};

template <typename T>
void ADTList<T>::push_front(const T &item)
{
    if (capacity <= count)
    {
        resize(2 * capacity);
    }
    for (int i = count; i > 0; --i)
    {
        data[i] = data[i - 1];
    }
    data[0] = item;
    count += 1;
};

template <typename T>
void ADTList<T>::push_back(const T &item)
{
    if (capacity <= count)
    {
        resize(2 * capacity);
    }
    data[count] = item;
    count += 1;
};

template <typename T>
void ADTList<T>::insert(const int index, const T &item)
{
    if (capacity <= count)
    {
        resize(2 * capacity);
    }

    T *new_data = new T[capacity];
    for (int i = 0; i < index; ++i)
    {
        new_data[i] = data[i];
    }
    new_data[index] = item;
    for (int i = index; i < count; ++i)
    {
        new_data[i + 1] = data[i];
    }
    delete[] data;
    data = new_data;

    count += 1;
};

template <typename T>
T ADTList<T>::pop_back()
{
    if (capacity / 2 > count)
    {
        resize(capacity / 2);
    }
    count -= 1;

    T *new_data = new T[capacity];
    for (int i = 0; i < count; ++i)
    {
        new_data[i] = data[i];
    }

    T elToDelete = data[count];

    delete[] data;
    data = new_data;
    return elToDelete;
};

template <typename T>
T ADTList<T>::pop_front()
{
    if (capacity / 2 > count)
    {
        resize(capacity / 2);
    }

    T *new_data = new T[capacity];
    for (int i = 1; i < count; ++i)
    {
        new_data[i - 1] = data[i];
    }

    T elToDelete = data[0];
    delete[] data;
    data = new_data;
    count -= 1;
    return elToDelete;
};

template <typename T>
T ADTList<T>::erase(const int index)
{
    if (capacity / 2 > count)
    {
        resize(capacity / 2);
    }

    T *new_data = new T[capacity];
    for (int i = 0; i < index; ++i)
    {
        new_data[i] = data[i];
    }
    for (int i = index; i < count; ++i)
    {
        new_data[i] = data[i + 1];
    }

    T elToDelete = data[index];
    delete[] data;
    data = new_data;
    count -= 1;
    return elToDelete;
};

template <typename T>
const T &ADTList<T>::front()
{
    if (isEmpty())
        throw std::out_of_range("Lista jest pusta. Nie można uzyskać dostępu do pierwszego elementu.");
    return data[0];
}

template <typename T>
const T &ADTList<T>::back()
{
    if (isEmpty())
        throw std::out_of_range("Lista jest pusta. Nie można uzyskać dostępu do ostatniego elementu.");
    return data[count - 1];
}

template <typename T>
void ADTList<T>::clear()
{
    if (isEmpty())
        return;

    capacity = MIN_SIZE;
    count = 0;

    T *new_data = new T[capacity];
    delete[] data;
    data = new_data;
}

template <typename T>
void ADTList<T>::sort()
{
    if (count > 1)
    {
        std::sort(data, data + count);
    }
}

template <typename T>
void ADTList<T>::merge(ADTList<T> &obj)
{
    // we assume that lists are sorted
    int newCapacity = capacity;
    int newCount = count + obj.size();
    while (newCapacity <= newCount)
    {
        newCapacity *= 2;
    }
    T *newData = new T[newCapacity];

    int k = 0;
    int i = 0;
    int j = 0;
    while (i < newCount)
    {
        while (j < count && k < obj.size())
        {
            if (data[j] <= obj[k])
            {
                newData[i] = data[j];
                j++;
            }
            else
            {
                newData[i] = obj[k];
                k++;
            }
            i++;
        }
        while (j < count)
        {
            newData[i] = data[j];
            j++;
            i++;
        }
        while (k < obj.size())
        {
            newData[i] = data[k];
            k++;
            i++;
        }
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
    count = newCount;
};

template <typename T>
ADTList<T>::~ADTList()
{
    delete[] data;
}