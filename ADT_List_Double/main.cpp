#include "doublelist.h"
#include <cassert>

int main()
{
    DoubleList<int> list;

    // Basic functionality tests
    assert(list.empty());
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    assert(list.size() == 3);
    assert(list.front() == 5);
    assert(list.back() == 20);

    list.display();          // Expected output: 5 10 20
    list.display_reversed(); // Expected output: 20 10 5

    // Testing pop_front
    list.pop_front();
    assert(list.front() == 10);
    assert(list.size() == 2);

    // Testing pop_back
    list.pop_back();
    assert(list.back() == 10);
    assert(list.size() == 1);

    // Clear the list
    list.clear();
    assert(list.empty());

    // Insert elements again for more tests
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    assert(list.size() == 5);

    list.display(); // Expected output: 1 2 3 4 5

    // Testing move semantics
    DoubleList<int> list2 = std::move(list);
    assert(list.empty());
    assert(list2.size() == 5);

    list2.display(); // Expected output: 1 2 3 4 5

    // Testing copy constructor
    DoubleList<int> list3(list2);
    list3.display();
    list3.push_front(0);
    assert(list3.size() == 6);
    list3.display(); // Expected output: 0 1 2 3 4 5

    // Testing copy assignment operator
    DoubleList<int> list4;
    list4 = list3;
    list4.push_back(6);
    assert(list4.size() == 7);
    list4.display_reversed(); // Expected output: 6 5 4 3 2 1 0

    list2.clear();
    assert(list2.empty());

    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}
