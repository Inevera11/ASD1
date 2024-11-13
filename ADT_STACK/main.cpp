#include "mystack.h"

int main()
{
    // Test default constructor
    MyStack<int> stack1;
    assert(stack1.empty());
    assert(!stack1.full());
    assert(stack1.size() == 0);
    assert(stack1.max_size() == 10);
    stack1.display(); // output: [ ]

    // Test parameterized constructor
    MyStack<int> stack2(5);
    assert(stack2.max_size() == 5);

    // Test push and size
    stack2.push(1);
    assert(!stack2.empty());
    assert(stack2.size() == 1);
    assert(stack2.top() == 1);
    stack2.display(); // output: [ 1 ]

    stack2.push(2);
    assert(stack2.size() == 2);
    assert(stack2.top() == 2);
    stack2.display(); // output: [ 2 1 ]

    stack2.push(3);
    stack2.push(4);
    stack2.push(5);
    assert(stack2.size() == 5);
    assert(stack2.full());
    stack2.display(); // output: [ 5 4 3 2 1 ]

    // Test overflow exception
    try
    {
        stack2.push(6);
    }
    catch (const std::overflow_error &e)
    {
        std::cout << "Overflow error caught: " << e.what() << std::endl;
    }

    // Test pop
    stack2.pop();
    assert(stack2.size() == 4);
    assert(stack2.top() == 4);

    stack2.pop();
    stack2.pop();
    assert(stack2.size() == 2);
    assert(stack2.top() == 2);
    stack2.display(); // output: [ 2 1 ]

    // Test pop until empty
    stack2.pop();
    stack2.pop();
    assert(stack2.empty());
    stack2.display(); // output: [ ]

    // Test underflow exception
    try
    {
        stack2.pop();
        assert(false); // This should not be reached
    }
    catch (const std::length_error &e)
    {
        std::cout << "Underflow error caught: " << e.what() << std::endl;
    }

    // Test clear
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);
    stack1.clear();
    assert(stack1.empty());
    assert(stack1.size() == 0);

    // Test copy constructor
    stack1.push(100);
    stack1.push(200);
    MyStack<int> stack3(stack1);
    assert(stack3.size() == 2);
    assert(stack3.top() == 200);
    stack3.pop();
    assert(stack3.top() == 100);
    stack3.display(); // output: [ 100 ]

    // Test move constructor
    MyStack<int> stack4(std::move(stack1));
    assert(stack4.size() == 2); // stack4 should have the elements
    assert(stack1.empty());     // stack1 should be empty after the move

    // Test copy assignment operator
    stack4.clear();
    stack4.push(300);
    stack4.push(400);
    stack3 = stack4;
    assert(stack3.size() == 2);
    assert(stack3.top() == 400);

    // Test move assignment operator
    stack3 = std::move(stack4);
    assert(stack3.size() == 2); // stack3 should have the elements
    assert(stack4.empty());     // stack4 should be empty after the move
    stack3.display();           // output: [ 400 300 ]

    std::cout << "All tests passed!" << std::endl;
    return 0;
}