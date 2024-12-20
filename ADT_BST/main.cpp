#include "my_bst.h"

int main()
{
    // Create a BinarySearchTree of integers
    BinarySearchTree<int> tree;

    // Test: Initially, the tree should be empty
    assert(tree.empty());
    tree.insert(8);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    tree.insert(9);
    assert(tree.top() == 8);

    std::cout << "Created tree: " << std::endl;
    tree.display();
    tree.rotate_root_right();
    assert(tree.top() == 6);
    std::cout << "Right rotated tree (root): " << std::endl;
    tree.display();
    tree.rotate_root_left();
    assert(tree.top() == 8);
    std::cout << "Left rotated tree (root): " << std::endl;
    tree.display();
    std::cout << "Tree after dsw: " << std::endl;
    tree.dsw();
    tree.display();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}