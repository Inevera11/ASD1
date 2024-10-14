// Implementacja dwóch algorytmów sortowania w C++, w tym co najmniej jednego zaawansowanego.
// Funkcje sortujące muszą być szablonami, muszą mieć podany interfejs tablicowy lub z iteratorami,
// wystarczy użyć standardowego porównywania (operator<).

#include <algorithm>
#include <vector>
#include <array>
#include <iostream>

// Bubble Sort
// Sorts the elements in the range [first, last) in non-descending order.
// Elements are compared using operator<.

template <typename Iterator>
void bubbleSort(Iterator first, Iterator last)
{
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (Iterator it = first; it < last - 1; ++it)
        {
            if (*(it + 1) < *it)
            {
                std::iter_swap(it, it + 1); // Zamiana elementów miejscami
                swapped = true;
            }
        }
        // Redukcja zakresu, ostatni element jest na swoim miejscu
        --last;
    }
}

int main()
{
    // Testowanie sortowania bąbelkowego z wektorem
    std::vector<int> vec = {9, 4, 7, 3, 6, 8, 2, 1, 5, 0};
    bubbleSort(vec.begin(), vec.end());
    std::cout << "Bubble Sort result for vector: ";
    for (const auto &val : vec)
        std::cout << val << " ";
    std::cout << std::endl;

    // Testowanie sortowania bąbelkowego z tablicą
    std::array<int, 10> arr = {9, 4, 7, 3, 6, 8, 2, 1, 5, 0};
    bubbleSort(arr.begin(), arr.end());
    std::cout << "Bubble Sort result for array: ";
    for (const auto &val : arr)
        std::cout << val << " ";
    std::cout << std::endl;

    // Testowanie sortowania bąbelkowego z klasyczną tablicą
    int c_array[] = {9, 4, 7, 3, 6, 8, 2, 1, 5, 0};
    bubbleSort(std::begin(c_array), std::end(c_array));
    std::cout << "Bubble Sort result for C array: ";
    for (const auto &val : c_array)
        std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}