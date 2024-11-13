#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>
#include <stdexcept>
#include <forward_list>
#include <algorithm>

template <typename T>
class MyStack
{
    std::forward_list<T> lst;
    int msize;
    int curr_size;

public:
    MyStack(int s = 10) : msize(s), curr_size(0) {} // default constructor
    ~MyStack() {}
    MyStack(const MyStack &other) : msize{other.msize}, curr_size{other.curr_size} // copy constructor
    {
        if (!other.empty())
        {
            lst = other.lst;
        }
    }
    MyStack(MyStack &&other) : msize{other.msize}, curr_size{other.curr_size} // move constructor
    {
        if (!other.empty())
        {
            lst = std::move(other.lst);
            other.curr_size = 0;
        }
    }
    MyStack &operator=(const MyStack &other) // copy assignment operator, return *this
    {
        if (this != &other)
        {
            lst = other.lst;
            curr_size = other.curr_size;
            msize = other.msize;
        }
        return *this;
    }
    MyStack &operator=(MyStack &&other) // move assignment operator, return *this
    {
        if (this != &other)
        {
            lst = std::move(other.lst);
            curr_size = other.curr_size;
            msize = other.msize;
            other.curr_size = 0;
            other.msize = 0;
        }
        return *this;
    }
    bool empty() const { return lst.empty(); } // checks if the container has no elements
    bool full() const { return curr_size == msize; }
    std::size_t size() const { return curr_size; }
    std::size_t max_size() const { return msize; }
    void push(const T &item)
    {
        if (!full())
        {
            curr_size += 1;
            lst.push_front(item);
        }
        else
            throw std::overflow_error("Stack is full.");
    }
    void push(T &&item)
    {
        if (!full())
        {
            curr_size += 1;
            lst.push_front(std::move(item));
        }
        else
            throw std::overflow_error("Stack is full.");
    }
    T &top() { return lst.front(); } // zwraca koniec, nie usuwa
    void pop()
    {
        if (!empty())
        {
            lst.pop_front();
            curr_size -= 1;
        }
        else
            throw std::length_error("Stack is empty.");
    }
    void clear()
    {
        lst.clear();
        curr_size = 0;
    }
    void display()
    {
        std::cout << "MyStack: [ ";
        if (!empty())
        {
            for (const T &item : lst)
            {
                std::cout << item << " ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

#endif