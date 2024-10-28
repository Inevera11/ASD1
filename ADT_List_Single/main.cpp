#include "singlelist.h"
#include <iostream>

int main()
{
    // Test 1: Create an empty list and check its properties
    SingleList<int> list;
    assert(list.empty());
    assert(list.size() == 0);

    // Test 2: Push elements to the front
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    list.display(); // Expected output: 1 2 3

    // Test 3: Push elements to the back
    list.push_back(4);
    list.push_back(5);
    assert(list.size() == 5);
    assert(list.back() == 5);
    list.display(); // Expected output: 1 2 3 4 5

    // Test 4: Pop elements from the front
    list.pop_front();
    assert(list.front() == 2);
    assert(list.size() == 4);
    list.display(); // Expected output: 2 3 4 5

    // Test 5: Pop elements from the back
    list.pop_back();
    assert(list.back() == 4);
    assert(list.size() == 3);
    list.display(); // Expected output: 2 3 4

    // Test 6: Clear the list
    list.clear();
    assert(list.empty());
    assert(list.size() == 0);
    list.display(); // Expected output: (nothing)

    // Test 7: Copy constructor
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    SingleList<int> list2(list); // Copy list
    assert(list2.size() == 3);
    assert(list2.front() == 3);
    assert(list2.back() == 1);
    list2.display(); // Expected output: 3 2 1

    // Test 8: Move constructor
    SingleList<int> list3(std::move(list2));
    assert(list2.empty()); // list2 should be empty after move
    assert(list3.size() == 3);
    list3.push_back(0);
    assert(list3.front() == 3);
    assert(list3.back() == 0);
    list3.display(); // Expected output: 3 2 1 0

    // Test 9: Assignment operator (copy)
    list2 = list; // list2 now should be same as list
    assert(list2.size() == 3);
    assert(list2.front() == 3);
    assert(list2.back() == 1);
    list2.display(); // Expected output: 3 2 1

    // Test 10: Assignment operator (move)
    list2 = std::move(list3);
    assert(list3.empty()); // list3 should be empty after move
    assert(list2.size() == 4);
    assert(list2.front() == 3);
    assert(list2.back() == 0);
    list2.display(); // Expected output: 3 2 1 0

    // Test 11: Reverse the list
    list2.reverse();
    assert(list2.front() == 0);
    assert(list2.back() == 3);
    list2.display(); // Expected output: 0 1 2 3

    // Test 12: Edge case for pop_front on single element
    list.clear();
    list.push_front(5);
    list.push_back(6);
    list.pop_front();
    list.pop_front();
    assert(list.size() == 0);
    assert(list.empty());

    // Test 13: Edge case for pop_back on single element
    list.push_front(7);
    list.push_back(8);
    list.pop_back();
    assert(list.back() == 7);
    list.pop_back();
    assert(list.size() == 0);
    assert(list.empty());

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
