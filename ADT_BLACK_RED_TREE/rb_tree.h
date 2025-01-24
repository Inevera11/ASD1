#ifndef RB_TREE
#define RB_TREE

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>
#include <stdexcept>

template <typename T>
struct RBNode
{
    // the default access mode and default inheritance mode are public
    T value;
    RBNode *left, *right, *parent;
    bool is_black;
    // RBNode *parent;   // używane w pewnych zastosowaniach
    //  kostruktor domyślny
    RBNode() : value(T()), left(nullptr), right(nullptr), parent(nullptr), is_black(false) {}
    // konstruktor zwykły
    RBNode(const T &item) : value(item), left(nullptr), right(nullptr), parent(nullptr), is_black(false) {}
    // konstruktor z uwzględnieniem koloru
    RBNode(const T &item, bool is_black) : value(item), left(nullptr), right(nullptr), parent(nullptr), is_black(is_black) {}
    ~RBNode()
    {
        delete left;
        delete right;
    } // destruktor rekurencyjny
};

template <typename T>
class RedBlackBinarySearchTree
{
    RBNode<T> *root;

public:
    RedBlackBinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    ~RedBlackBinarySearchTree() { delete root; }  // trzeba wyczyścić
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
    void insert(const T &item)
    {
        RBNode<T> *new_node = new RBNode<T>(item);
        insert(new_node);
        insert_fixup(new_node);
    }
    void remove(const T &item) // usuwanie
    {
        RBNode<T> *node = search(root, item);
        if (node == nullptr)
            return;
        remove(node);
    };
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T *search(const T &item) const
    {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    void display()
    {
        std::cout << "RB Tree: " << std::endl;
        display(root, 0);
    }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void insert(RBNode<T> *node);
    void insert_fixup(RBNode<T> *node);                      // naprawia kolory node
    RBNode<T> *search(RBNode<T> *node, const T &item) const; // zwraca węzeł
    void remove(RBNode<T> *node);
    void remove_fixup(RBNode<T> *node);
    RBNode<T> *minimum(RBNode<T> *node) const;
    void transplant(RBNode<T> *to_delete, RBNode<T> *sub_root); // Podstawia sub_root w miejsce to_delete.
    void display(RBNode<T> *node, int level);
    void rotate_right(RBNode<T> *node);
    void rotate_left(RBNode<T> *node);
    virtual void visit(RBNode<T> *node)
    {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

template <typename T>
void RedBlackBinarySearchTree<T>::rotate_right(RBNode<T> *node)
{
    RBNode<T> *y = node->left;
    node->left = y->right;
    if (y->right != nullptr)
    {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr)
    {
        root = y;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = y;
    }
    else
    {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
}

template <typename T>
void RedBlackBinarySearchTree<T>::rotate_left(RBNode<T> *node)
{
    RBNode<T> *y = node->right;
    node->right = y->left;
    if (y->left != nullptr)
    {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

template <typename T>
void RedBlackBinarySearchTree<T>::display(RBNode<T> *node, int level)
{
    if (node == nullptr)
    {
        for (int i = 0; i < level; i++)
        {
            std::cout << "   |";
        }
        std::cout << "---" << "null" << 'B' << std::endl;
        return;
    }
    display(node->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        std::cout << "   |";
    }
    char colour = node->is_black ? 'B' : 'R';
    std::cout << "---" << node->value << colour << std::endl;
    display(node->left, level + 1);
}

template <typename T>
RBNode<T> *RedBlackBinarySearchTree<T>::minimum(RBNode<T> *node) const
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}

template <typename T>
void RedBlackBinarySearchTree<T>::transplant(RBNode<T> *to_delete, RBNode<T> *successor)
{
    // za uaktualnienie successor->left /  successor->right odpowiada funkcja wywołująca
    if (to_delete->parent == nullptr) // to_delete jest korzeniem
        root = successor;
    else
    {
        if (to_delete == to_delete->parent->left) // to_delete jest lewym dzieckiem
            to_delete->parent->left = successor;
        else // to_delete jest prawym dzieckiem
            to_delete->parent->right = successor;
    }
    if (successor != nullptr)
        // ustaw poprwanie wskaźnik parenta w następniku
        successor->parent = to_delete->parent;
}

template <typename T>
void RedBlackBinarySearchTree<T>::remove(RBNode<T> *to_delete)
{
    RBNode<T> *top_node = to_delete;             // Początkowo węzeł to_delete jest "najwyższym" nodem w rozważanym poddrzewie
    RBNode<T> *successor;                        // Wskaźnik na następnik najwyższego węzła
    bool is_top_node_black = top_node->is_black; // Drzewo wymaga korekty jeśli usunięty węzeł jest czarny
    if (to_delete->left == nullptr)              // to_delete nie ma lewego dziecka
    {
        successor = to_delete->right;
        transplant(to_delete, to_delete->right); // Prawe dziecko zajmie miejsce to_delete
    }
    else if (to_delete->right == nullptr) // to_delete nie ma prawego dziecka
    {
        successor = to_delete->left;
        transplant(to_delete, to_delete->left); // Lewe dziecko zajmie miejsce to_delete
    }
    else // to_delete posiada 2 dzieci
    {
        top_node = minimum(to_delete->right);   // Szukamy minimum w prawym poddrzewie to_delete (następnika)
        is_top_node_black = top_node->is_black; // Drzewo wymaga korekty jeśli następnik jest czarny
        successor = top_node->right;            // Aktualizujemy następnik najwyższego węzła
        if (top_node->parent == to_delete)
        {
            // Jeśli top_node jest bezpośrednim prawym dzieckiem to_delete
            // successor->parent = top_node;
            ;
        }
        else
        { // zastąp top_node jego prawym dzieckiem w drzewie
            transplant(top_node, top_node->right);
            top_node->right = to_delete->right;
            top_node->right->parent = top_node;
        }
        // zastępujemy to_delete jego następnikiem
        transplant(to_delete, top_node);
        top_node->left = to_delete->left;
        top_node->left->parent = top_node;
        top_node->is_black = to_delete->is_black;
    }
    // izolujemy to_delete od drzewa żeby je bezpiecznie usunąć
    to_delete->left = nullptr;
    to_delete->right = nullptr;
    delete to_delete;
    if (is_top_node_black)
        remove_fixup(successor); // korekta kolorow
}

template <typename T>
void RedBlackBinarySearchTree<T>::remove_fixup(RBNode<T> *x)
{ // x ma dodatkowy czarny kolor
    while (x != root && x->is_black)
    {
        if (x == x->parent->left)
        {
            RBNode<T> *w = x->parent->right;
            if (!w->is_black)
            { // Przypadek 1 - brat x jest czerwony
                w->is_black = true;
                x->parent->is_black = false;
                rotate_left(x->parent);
                w = x->parent->right;
            }
            if (w->left->is_black && w->right->is_black)
            { // Przypadek 2 - brat x jest czany i  ma 2 czarnych dzieci
                w->is_black = false;
                x = x->parent;
            }
            else
            {
                if (w->right->is_black)
                { // przypadek 3 - tylko prawy syn brata x jest czarny
                    w->left->is_black = true;
                    w->is_black = false;
                    rotate_right(w);
                    w = x->parent->right;
                }
                // przpadek 4 - prawy syn brata x jest czerwony
                w->is_black = x->parent->is_black;
                x->parent->is_black = true;
                w->right->is_black = true;
                rotate_left(x->parent);
                x = root; // kończymy
            }
        }
        else
        { // symetryczna sytuacja
            RBNode<T> *w = x->parent->left;
            if (!w->is_black)
            {
                w->is_black = true;
                x->parent->is_black = false;
                rotate_right(x->parent);
                w = x->parent->left;
            }
            if (w->right->is_black && w->left->is_black)
            {
                w->is_black = false;
                x = x->parent;
            }
            else
            {
                if (w->left->is_black)
                {
                    w->right->is_black = true;
                    w->is_black = false;
                    rotate_left(w);
                    w = x->parent->left;
                }
                w->is_black = x->parent->is_black;
                x->parent->is_black = true;
                w->left->is_black = true;
                rotate_right(x->parent);
                x = root; // kończymy
            }
        }
    }
    if (x != nullptr)
        x->is_black = true; // root musi być czarny
}

template <typename T>
void RedBlackBinarySearchTree<T>::insert(RBNode<T> *node)
{
    RBNode<T> *parent = nullptr;
    RBNode<T> *curr = root;
    while (curr != nullptr)
    {
        parent = curr;
        if (node->value < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }
    node->parent = parent;
    if (parent == nullptr)
        root = node;
    else
    {
        if (node->value < parent->value)
            parent->left = node;
        else
            parent->right = node;
    }
}

template <typename T>
void RedBlackBinarySearchTree<T>::insert_fixup(RBNode<T> *node)
{
    while (node->parent && !node->parent->is_black)
    {
        if (node->parent == node->parent->parent->left) // is parent left child
        {
            RBNode<T> *uncle = node->parent->parent->right;
            if (uncle && !uncle->is_black) // red-uncle case
            {
                node->parent->is_black = true;
                uncle->is_black = true;
                node->parent->parent->is_black = false;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right) // black-uncle-triangle case
                {
                    node = node->parent;
                    rotate_left(node);
                }
                // black-uncle-line case
                node->parent->is_black = true;
                node->parent->parent->is_black = false;
                rotate_right(node->parent->parent);
            }
        }
        else // is parent right child
        {
            RBNode<T> *uncle = node->parent->parent->left;
            if (uncle && !uncle->is_black) // red-uncle case
            {
                node->parent->is_black = true;
                uncle->is_black = true;
                node->parent->parent->is_black = false;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left) // black-uncle-triangle case
                {
                    node = node->parent;
                    rotate_right(node);
                }
                // black-uncle-line  case
                node->parent->is_black = true;
                node->parent->parent->is_black = false;
                rotate_left(node->parent->parent);
            }
        }
    }
    root->is_black = true; // root must always be black
}

template <typename T>
RBNode<T> *RedBlackBinarySearchTree<T>::search(RBNode<T> *node, const T &item) const
{
    while (node != nullptr && node->value != item)
    {
        if (item < node->value)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

#endif