#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>
#include <stdexcept>
#include <stack>

template <typename T>
class MyQueue
{
    std::stack<T> stack_put;
    std::stack<T> stack_pop;

public:
    MyQueue() = default; // default constructor
    ~MyQueue() = default;
    MyQueue(const MyQueue &other)
    { // copy constructor
        stack_put = other.stack_put;
        stack_pop = other.stack_pop;
    };
    MyQueue(MyQueue &&other)
    { // move constructor
        stack_put = std::move(other.stack_put);
        stack_pop = std::move(other.stack_pop);
    };
    MyQueue &operator=(const MyQueue &other)
    { // copy assignment operator, return *this
        if (this != &other)
        {
            stack_put = other.stack_put;
            stack_pop = other.stack_pop;
        }
        return *this;
    };
    MyQueue &operator=(MyQueue &&other)
    { // move assignment operator, return *this
        if (this != &other)
        {
            stack_put = std::move(other.stack_put);
            stack_pop = std::move(other.stack_pop);
        }
        return *this;
    };
    bool empty() const { return stack_pop.empty() && stack_put.empty(); };    // checks if the container has no elements
    std::size_t size() const { return stack_pop.size() + stack_put.size(); }; // liczba elementów w kolejce
    void push(const T &item) { stack_put.push(item); };                       // dodanie na koniec, push_back(item)
    void push(T &&item) { stack_put.push(std::move(item)); };                 // dodanie na koniec, push_back(std::move(item))
    T &front()                                                                // zwraca początek, nie usuwa
    {
        if (empty())
        {
            throw std::length_error("Queue is empty.");
        }

        if (stack_pop.empty())
        {
            while (!stack_put.empty())
            {
                stack_pop.push(stack_put.top());
                stack_put.pop();
            }
        }
        return stack_pop.top();
    };
    T &back() // zwraca koniec, nie usuwa
    {
        if (empty())
        {
            throw std::length_error("Queue is empty.");
        }
        if (stack_put.empty())
        {
            std::stack<T> tmp_stack = stack_pop;
            T *last_item = nullptr;
            while (!tmp_stack.empty())
            {
                last_item = &tmp_stack.top();
                tmp_stack.pop();
            }
            return *last_item;
        }
        return stack_put.top();
    };
    void pop() // usuwa początek kolejki, pop_front()
    {
        if (empty())
        {
            throw std::length_error("Queue is empty.");
        }
        if (stack_pop.empty())
        {
            while (!stack_put.empty())
            {
                stack_pop.push(stack_put.top());
                stack_put.pop();
            }
        }
        return stack_pop.pop();
    };
    void clear()
    {
        // czyszczenie listy z elementów
        while (!stack_pop.empty())
        {
            stack_pop.pop();
        }
        while (!stack_put.empty())
        {
            stack_put.pop();
        }
    };
    void display()
    {
        std::cout << "Queue: [ ";
        std::stack<T> reversed_put_stack;
        std::stack<T> tmp_stack = stack_put;
        while (!tmp_stack.empty())
        {
            reversed_put_stack.push(tmp_stack.top());
            tmp_stack.pop();
        }
        tmp_stack = stack_pop;
        while (!tmp_stack.empty())
        {
            std::cout << tmp_stack.top() << " ";
            tmp_stack.pop();
        }
        while (!reversed_put_stack.empty())
        {
            std::cout << reversed_put_stack.top() << " ";
            reversed_put_stack.pop();
        }
        std::cout << "]" << std::endl;
    };
};

#endif