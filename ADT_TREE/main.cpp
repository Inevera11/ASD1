#include "mytree.h"

int main()
{
    // Create a RandomBinaryTree of integers
    RandomBinaryTree<int> tree;

    // Test: Initially, the tree should be empty
    assert(tree.empty());

    // Insert elements into the tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);

    // Test: After insertion, the tree should not be empty
    assert(!tree.empty());

    // Display the tree structure
    std::cout << "Tree structure after insertion:" << std::endl;
    tree.display();

    // Test: Calc total
    std::cout << "Total sum of elements (recursive):" << tree.calc_total_recursive() << std::endl;
    assert(tree.calc_total_recursive() == 75);

    std::cout << "Total sum of elements (iter):" << tree.calc_total_iter() << std::endl;
    assert(tree.calc_total_iter() == 75);

    // Test: Searching for an element that exists
    int *found = tree.search(15);
    assert(found != nullptr && *found == 15);

    // Test: Searching for an element that does not exist
    found = tree.search(30);
    assert(found == nullptr);

    // Perform inorder traversal
    std::cout << "Inorder traversal:" << std::endl;
    tree.inorder();

    // Perform preorder traversal
    std::cout << "Preorder traversal:" << std::endl;
    tree.preorder();

    // Perform postorder traversal
    std::cout << "Postorder traversal:" << std::endl;
    tree.postorder();

    // Perform BFS
    std::cout << "BFS traversal:" << std::endl;
    tree.bfs();

    // Perform iterative preorder traversal
    std::cout << "Iterative Preorder traversal:" << std::endl;
    tree.iter_preorder();

    // Clear the tree
    tree.clear();

    // Test: After clearing, the tree should be empty
    assert(tree.empty());

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
