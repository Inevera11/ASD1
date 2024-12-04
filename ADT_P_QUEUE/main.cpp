#include "mypriorityqueue.h"

int main()
{
    // Test default constructor
    MyPriorityQueue<int> pqueue1;
    assert(pqueue1.empty());
    assert(pqueue1.size() == 0);
    pqueue1.display(); // output: Queue: [ ]

    // Test push and size
    pqueue1.push(1);
    assert(!pqueue1.empty());
    assert(pqueue1.size() == 1);
    assert(pqueue1.top() == 1);
    pqueue1.display(); // output: Queue: [ 1 ]

    pqueue1.push(2);
    pqueue1.push(3);
    pqueue1.push(4);
    pqueue1.push(5);
    assert(pqueue1.size() == 5);
    pqueue1.display(); // output: Queue: [ 5 4 3 2 1 ]

    // Test pop
    pqueue1.pop();
    assert(pqueue1.size() == 4);
    assert(pqueue1.top() == 4);
    pqueue1.display(); // output: Queue: [ 4 3 2 1 ]

    pqueue1.pop();
    pqueue1.push(6);
    assert(pqueue1.size() == 4);
    assert(pqueue1.top() == 6);
    pqueue1.display(); // output: Queue: [ 6 3 2 1 ]

    // Test pop until empty
    pqueue1.pop();
    pqueue1.pop();
    pqueue1.pop();
    pqueue1.pop();
    assert(pqueue1.empty());
    pqueue1.display(); // output: Queue: [ ]

    // Test clear
    pqueue1.push(10);
    pqueue1.push(20);
    pqueue1.push(30);
    pqueue1.clear();
    assert(pqueue1.empty());
    assert(pqueue1.size() == 0);
    pqueue1.display(); // output: Queue: [ ]

    // Test copy constructor
    pqueue1.push(100);
    pqueue1.push(200);
    MyPriorityQueue<int> pqueue2(pqueue1);
    assert(pqueue2.size() == 2);
    assert(pqueue2.top() == 200);
    pqueue2.pop();
    assert(pqueue2.top() == 100);
    pqueue2.display(); // output: Queue: [ 100 ]

    // Test move constructor
    MyPriorityQueue<int> pqueue3(std::move(pqueue1));
    assert(pqueue3.size() == 2); // pqueue3 should have the elements
    assert(pqueue1.empty());     // pqueue1 should be empty after the move

    // Test copy assignment operator
    pqueue3.push(400);
    pqueue2 = pqueue3;
    pqueue2.push(300);
    assert(pqueue2.size() == 4);
    assert(pqueue2.top() == 400);
    pqueue2.display(); // output: Queue: [ 400 300 200 100 ]

    // Test move assignment operator
    pqueue2 = std::move(pqueue3);
    assert(pqueue2.size() == 3); // pqueue2 should have the elements
    assert(pqueue3.empty());     // pqueue3 should be empty after the move
    pqueue2.display();           // output: Queue: [ 400 200 100 ]

    std::cout << "All tests passed!" << std::endl;
    return 0;
};