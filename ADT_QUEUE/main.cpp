#include "myqueue.h"

int main()
{
    // Test default constructor
    MyQueue<int> queue1;
    assert(queue1.empty());
    assert(queue1.size() == 0);
    queue1.display(); // output: Queue: [ ]

    // Test push and size
    queue1.push(1);
    assert(!queue1.empty());
    assert(queue1.size() == 1);
    assert(queue1.front() == 1);
    assert(queue1.back() == 1);
    queue1.display(); // output: Queue: [ 1 ]

    queue1.push(2);
    queue1.push(3);
    queue1.push(4);
    queue1.push(5);
    assert(queue1.size() == 5);
    queue1.display(); // output: Queue: [ 1 2 3 4 5 ]

    // Test pop
    queue1.pop();
    assert(queue1.size() == 4);
    assert(queue1.front() == 2);
    queue1.display(); // output: Queue: [ 2 3 4 5 ]

    queue1.pop();
    queue1.push(6);
    assert(queue1.size() == 4);
    assert(queue1.front() == 3);
    queue1.display(); // output: Queue: [ 3 4 5 6 ]

    // Test pop until empty
    queue1.pop();
    queue1.pop();
    queue1.pop();
    queue1.pop();
    assert(queue1.empty());
    queue1.display(); // output: Queue: [ ]

    // Test underflow exception
    try
    {
        queue1.pop();
        assert(false); // This should not be reached
    }
    catch (const std::length_error &e)
    {
        std::cout << "Underflow error caught: " << e.what() << std::endl;
    }

    // Test clear
    queue1.push(10);
    queue1.push(20);
    queue1.push(30);
    queue1.clear();
    assert(queue1.empty());
    assert(queue1.size() == 0);
    queue1.display(); // output: Queue: [ ]

    // Test copy constructor
    queue1.push(100);
    queue1.push(200);
    MyQueue<int> queue2(queue1);
    assert(queue2.size() == 2);
    assert(queue2.front() == 100);
    assert(queue2.back() == 200);
    queue2.pop();
    assert(queue2.front() == 200);
    queue2.display(); // output: Queue: [ 200 ]

    // Test move constructor
    MyQueue<int> queue3(std::move(queue1));
    assert(queue3.size() == 2); // queue3 should have the elements
    assert(queue1.empty());     // queue1 should be empty after the move

    // Test copy assignment operator
    queue3.clear();
    queue3.push(300);
    queue3.push(400);
    queue2 = queue3;
    assert(queue2.size() == 2);
    assert(queue2.front() == 300);
    assert(queue2.back() == 400);
    queue2.display(); // output: Queue: [ 300 400 ]

    // Test move assignment operator
    queue2 = std::move(queue3);
    assert(queue2.size() == 2); // queue2 should have the elements
    assert(queue3.empty());     // queue3 should be empty after the move
    queue2.display();           // output: Queue: [ 300 400 ]

    std::cout << "All tests passed!" << std::endl;
    return 0;
};