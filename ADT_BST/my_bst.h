#ifndef MYBST_H
#define MYBST_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>
#include <stdexcept>

template <typename T>
struct BSTNode
{
    // the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    // BSTNode *parent;   // używane w pewnych zastosowaniach
    //  kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T &item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode()
    {
        delete left;
        delete right;
    } // destruktor rekurencyjny
};

template <typename T>
class BinarySearchTree
{
    BSTNode<T> *root;

public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    ~BinarySearchTree() { delete root; }  // trzeba wyczyścić
    void clear()
    {
        delete root;
        root = nullptr;
    }
    bool empty() const { return root == nullptr; }
    T &top()
    {
        assert(root != nullptr);
        return root->value;
    } // podgląd korzenia
    void insert(const T &item) { root = insert(root, item); }
    void remove(const T &item); // usuwanie przez złączanie
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T *search(const T &item) const
    {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T *iter_search(const T &item) const
    { // wg libavl
        for (auto node = root; node != nullptr;)
        {
            if (item == node->value)
            {
                return &(node->value);
            }
            else if (item < node->value)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return nullptr;
    }
    T *find_min();
    T *find_max();
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder();   // trudne
    void iter_postorder(); // trudne
    void bfs();            // przejście poziomami (wszerz)
    void dsw();            // zrownoważenie drzewa
    void rotate_root_right() { rotate_right(root, nullptr); }
    void rotate_root_left() { rotate_left(root, nullptr); }
    void convert_to_list();
    void rotate_every_second();
    void display()
    {
        display(root, 0);
    }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T> *insert(BSTNode<T> *node, const T &item);       // zwraca nowy korzeń
    BSTNode<T> *search(BSTNode<T> *node, const T &item) const; // zwraca węzeł
    BSTNode<T> *remove(BSTNode<T> *node);                      // zwraca nowy korzeń poddrzewa
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    void rotate_right(BSTNode<T> *node, BSTNode<T> *parent);
    void rotate_left(BSTNode<T> *node, BSTNode<T> *parent);
    virtual void visit(BSTNode<T> *node)
    {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

template <typename T>
void BinarySearchTree<T>::rotate_every_second()
{
    BSTNode<T> *curr = root;
    BSTNode<T> *curr_parent = nullptr;
    while (curr->right != nullptr)
    {
        BSTNode<T> *tmp = curr->right;
        rotate_left(curr, curr_parent);
        curr_parent = tmp;
        if (curr_parent->right == nullptr)
        {
            break;
        }
        curr = curr_parent->right;
    }
}

template <typename T>
void BinarySearchTree<T>::convert_to_list()
{
    while (root->left != nullptr)
    {
        rotate_right(root, nullptr);
    }
    BSTNode<T> *curr = root;
    BSTNode<T> *curr_parent = nullptr;
    while (curr->right != nullptr)
    {
        while (curr->left != nullptr)
        {
            BSTNode<T> *tmp = curr->left;
            rotate_right(curr, curr_parent);
            curr = tmp;
        }
        curr_parent = curr;
        curr = curr->right;
    }
}

template <typename T>
void BinarySearchTree<T>::dsw()
{
    convert_to_list();
    int node_count = 0;
    for (BSTNode<T> *curr = root; curr != nullptr; curr = curr->right)
    {
        node_count++;
    }

    // Policzenie wysokości najbliższego pełnego drzewa BST
    int m = 1;
    while (m <= node_count)
    {
        m = m * 2 + 1; // dodajemy liczbę węzłów potrzebnych do kolejnego poziomu drzewa
    }
    m = (m - 1) / 2; //  zmieniamy liczbę węzłow na wysokość

    while (m > 1)
    {
        m /= 2;
        rotate_every_second();
    }
}

template <typename T>
void BinarySearchTree<T>::rotate_right(BSTNode<T> *start, BSTNode<T> *grand_parent)
{
    if (start == nullptr || start->left == nullptr)
    {
        return;
    }
    BSTNode<T> *new_parent = start->left;
    if (grand_parent != nullptr)
    {
        grand_parent->right = new_parent;
    }
    else
    {
        root = new_parent;
    }
    start->left = new_parent->right;
    new_parent->right = start;
}

template <typename T>
void BinarySearchTree<T>::rotate_left(BSTNode<T> *start, BSTNode<T> *grand_parent)
{
    if (start == nullptr || start->right == nullptr)
    {
        return;
    }
    BSTNode<T> *new_parent = start->right;
    if (grand_parent != nullptr)
    {
        grand_parent->right = new_parent;
    }
    else
    {
        root = new_parent;
    }
    start->right = new_parent->left;
    new_parent->left = start;
}

template <typename T>
void BinarySearchTree<T>::display(BSTNode<T> *node, int level)
{
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
void BinarySearchTree<T>::remove(const T &item)
{ // usuwanie przez złączanie
    // Najpierw znajdujemy węzeł i jego rodzica.
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;
    while (node != nullptr)
    {
        if (node->value == item)
            break;
        prev = node;
        if (item < node->value)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    // Szukamy przyczyny przerwania pętli while.
    if (node != nullptr && node->value == item)
    {
        // node ma być usunięty.
        if (node == root)
        {
            root = remove(node);
        }
        else if (prev->left == node)
        {
            prev->left = remove(node);
        }
        else
        {
            prev->right = remove(node);
        }
    }
    else if (root != nullptr)
    {
        ; // klucza nie znaleziono
    }
    else
    {     // root == nullptr
        ; // drzewo jest puste
    }
}

template <typename T>
BSTNode<T> *BinarySearchTree<T>::remove(BSTNode<T> *node)
{
    // Mamy usunąć węzeł i zwrócić nowy korzeń poddrzewa.
    assert(node != nullptr);
    BSTNode<T> *new_root;
    if (node->right == nullptr)
    { // node nie ma prawego dziecka
        new_root = node->left;
    }
    else if (node->left == nullptr)
    { // node nie ma lewego dziecka
        new_root = node->right;
    }
    else
    {                      // obecne lewe i prawe dziecko
        new_root = node;   // zapisujemy stary korzeń
        node = node->left; // idziemy w lewo
        while (node->right != nullptr)
        { // idziemy w prawo do końca
            node = node->right;
        }
        node->right = new_root->right; // prawe poddrzewo przełączone
        node = new_root;               // węzeł do usunięcia
        new_root = node->left;         // nowy korzeń
    }
    delete node;
    return new_root;
}

template <typename T>
BSTNode<T> *BinarySearchTree<T>::insert(BSTNode<T> *node, const T &item)
{
    if (node == nullptr)
    {
        return new BSTNode<T>(item);
    }
    if (item < node->value)
    {
        node->left = insert(node->left, item);
    }
    else
    {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}

template <typename T>
BSTNode<T> *BinarySearchTree<T>::search(BSTNode<T> *node, const T &item) const
{
    if (node == nullptr || node->value == item)
    {
        return node;
    }
    else if (item < node->value)
    {
        return search(node->left, item);
    }
    else
    {
        return search(node->right, item);
    }
}

#endif