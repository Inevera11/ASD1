#include "mydeque.h"

int main()
{
    // Test 1: Create an empty list and check its properties
    MyDeque<int> deque;
    assert(deque.empty());
    assert(deque.size() == 0);

    // Test 2: Push elements to the front
    deque.push_front(3);
    deque.push_front(2);
    deque.push_front(1);
    assert(deque.size() == 3);
    assert(deque.front() == 1);
    assert(deque.back() == 3);
    deque.display(); // Expected output: 1 2 3

    // Test 3: Push elements to the back
    deque.push_back(4);
    deque.push_back(5);
    assert(deque.size() == 5);
    assert(deque.back() == 5);
    deque.display(); // Expected output: 1 2 3 4 5

    // Test 4: Pop elements from the front
    deque.pop_front();
    assert(deque.front() == 2);
    assert(deque.size() == 4);
    deque.display(); // Expected output: 2 3 4 5

    // Test 5: Pop elements from the back
    deque.pop_back();
    assert(deque.back() == 4);
    assert(deque.size() == 3);
    deque.display(); // Expected output: 2 3 4

    // Test 6: Clear the deque
    deque.clear();
    assert(deque.empty());
    assert(deque.size() == 0);
    deque.display(); // Expected output: (nothing)

    // Test 7: Copy constructor
    deque.push_front(1);
    deque.push_front(2);
    deque.push_front(3);
    MyDeque<int> deque2(deque); // Copy deque
    assert(deque2.size() == 3);
    assert(deque2.front() == 3);
    assert(deque2.back() == 1);
    deque2.display(); // Expected output: 3 2 1

    // Test 8: Move constructor
    MyDeque<int> deque3(std::move(deque2));
    assert(deque2.empty()); // deque2 should be empty after move
    assert(deque3.size() == 3);
    deque3.push_back(0);
    assert(deque3.front() == 3);
    assert(deque3.back() == 0);
    deque3.display(); // Expected output: 3 2 1 0

    // Test 9: Assignment operator (copy)
    deque2 = deque; // deque2 now should be same as deque
    assert(deque2.size() == 3);
    assert(deque2.front() == 3);
    assert(deque2.back() == 1);
    deque2.display(); // Expected output: 3 2 1

    // Test 10: Assignment operator (move)
    deque2 = std::move(deque3);
    assert(deque3.empty()); // deque3 should be empty after move
    assert(deque2.size() == 4);
    assert(deque2.front() == 3);
    assert(deque2.back() == 0);
    deque2.display(); // Expected output: 3 2 1 0

    // Test 11: Display reversed deque
    deque2.display_reversed(); // Expected output: 0 1 2 3

    // Test 12: Edge case for pop_front on single element
    deque.clear();
    deque.push_front(5);
    deque.push_back(6);
    deque.pop_front();
    deque.pop_front();
    assert(deque.size() == 0);
    assert(deque.empty());

    // Test 13: Edge case for pop_back on single element
    deque.push_front(7);
    deque.push_back(8);
    deque.pop_back();
    assert(deque.back() == 7);
    deque.pop_back();
    assert(deque.size() == 0);
    assert(deque.empty());

    std::cout << "All tests passed!" << std::endl;
    return 0;
}