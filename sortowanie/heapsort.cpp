#include <vector>
#include <iostream>
#include <utility>

template <typename Iterator>
void heapify(Iterator first, int last_idx, int root_idx)
// function that will fix punctual heap distortions
{
    int right_child_idx = 2 * root_idx + 2;
    int left_child_idx = 2 * root_idx + 1;

    std::pair<Iterator, int> max_val(first, root_idx);

    // if left child exist, check if its value is greater than root
    if (left_child_idx <= last_idx && *(first + (left_child_idx - root_idx)) > *max_val.first)
    {
        max_val.first = first + (left_child_idx - root_idx);
        max_val.second = left_child_idx;
    }
    // if right child exist
    if (right_child_idx <= last_idx && *(first + (right_child_idx - root_idx)) > *max_val.first)
    {
        max_val.first = (first + (right_child_idx - root_idx));
        max_val.second = right_child_idx;
    }

    if (max_val.second != root_idx)
    {
        std::iter_swap(first, max_val.first);
        heapify(max_val.first, last_idx, max_val.second);
    }
}

template <typename Iterator>
void buildHeap(Iterator first, Iterator last, int len)
// function that will build max heap
{

    for (int idx = len - 1; idx > -1; --idx)
    {
        heapify(first + idx, len - 1, idx);
    }
}

template <typename Iterator>
void heapSort(Iterator first, Iterator last)
{
    int len = std::distance(first, last);

    buildHeap(first, last, len);

    for (int n = len - 1; n > 0; --n)
    {
        std::iter_swap(first, first + n);
        heapify(first, n - 1, 0);
    }
}

int main()
{
    std::vector<int> vec = {3, 10, 8, 3, 11, 15, 2, 1, -1, -5};
    std::cout << "Unsorted vector: ";
    for (const auto &val : vec)
        std::cout << val << " ";
    std::cout << std::endl;

    heapSort(vec.begin(), vec.end());

    std::cout << "Sorted vector with heapSort: ";
    for (const auto &val : vec)
        std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}