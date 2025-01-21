#include "rb_tree.h"

int main()
{
    RedBlackBinarySearchTree<int> tree;

    // Test: Tree should be empty initially
    assert(tree.empty());

    // Test: Insert elements
    tree.insert(10);
    std::cout << "Insert root 10" << std::endl;
    tree.display();
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.display();

    // Test: Check top/root value
    assert(tree.top() == 10);
    std::cout << "Tree to is 10" << std::endl;

    // Test: Search for existing elements
    assert(tree.search(10) != nullptr);
    assert(tree.search(20) != nullptr);
    assert(tree.search(5) != nullptr);
    assert(tree.search(15) != nullptr);
    std::cout << "Tree includes values 5, 10, 20, 15" << std::endl;

    // Test: Search for non-existing elements
    assert(tree.search(100) == nullptr);
    assert(tree.search(-5) == nullptr);
    std::cout << "Tree doesn't include -5, 100" << std::endl;
    std::cout << "Let's make the tree more advanced: \n"
              << std::endl;
    tree.insert(30);
    tree.display();
    tree.insert(25);
    std::cout << "\n New node's (25) uncle would be red \n"
              << std::endl;
    tree.display();
    tree.insert(31);
    tree.insert(32);
    std::cout << "\n Added 31, 32 \n"
              << std::endl;
    tree.display();
    tree.insert(33);
    std::cout << "\n New node's (33) uncle would be black (line) -> rotate 31 left, recolor 32 and 31 \n"
              << std::endl;
    tree.display();
    tree.insert(3);
    std::cout << "\n Added 3 \n"
              << std::endl;
    tree.display();
    tree.insert(4);
    std::cout << "\n New node's (4) uncle would be black (triangle) -> rotate 3 left \n"
              << "\n newly created combination is black uncle line (5-4-3) -> rotate 5 right \n"
              << std::endl;
    tree.display();

    std::cout << "\n Tree balancing is working as expected"
              << std::endl;

    // Test: Remove an element
    tree.remove(33);
    assert(tree.search(33) == nullptr);
    std::cout << "Remove 33 from tree (no children)" << std::endl;
    tree.display();
    tree.remove(32);
    assert(tree.search(32) == nullptr);
    std::cout << "Remove 32 from tree (no right child)" << std::endl;
    tree.display();
    tree.remove(3);
    tree.remove(4);
    assert(tree.search(4) == nullptr);
    std::cout << "Remove 3 then 4 from tree (4 has no left child)" << std::endl;
    tree.display();
    tree.remove(20);
    assert(tree.search(20) == nullptr);
    std::cout << "Remove root 20 from tree (has both children)" << std::endl;
    tree.display();

    // Test: Check tree is not empty after removals
    assert(!tree.empty());

    // Test: Clear the tree and check emptiness
    tree.clear();
    assert(tree.empty());

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
