#include <vector>
#include <iostream>

// Funkcje sortujące muszą być szablonami, muszą mieć podany interfejs tablicowy lub z iteratorami,
// wystarczy użyć standardowego porównywania (operator<).

template <typename Iterator>
void selectSort(Iterator first, Iterator last)
{
    // last będzie posortowany po wykonaniu całości
    for (Iterator start = first; start != (last - 1); ++start)
    {
        Iterator min = start;                        // Zakładamy, że aktualny element jest minimalny
        for (Iterator l = start + 1; l != last; ++l) // Porównujemy od następnego elementu
        {
            if (*l < *min)
            {
                min = l; // Znajdujemy nowy minimum
            }
        }

        if (start != min) // Jeśli znaleźliśmy mniejsze
        {
            std::iter_swap(start, min); // Zamiana miejscami
        }
    }
}

int main()
{
    std::vector<int> vec = {8, 4, 7, 3, 6, 5, 2, 1, 9, 0};
    std::cout << "Unsorted vector: ";
    for (const auto &val : vec)
        std::cout << val << " ";
    std::cout << std::endl;

    selectSort(vec.begin(), vec.end());

    std::cout << "Sorted vector with selectSort: ";
    for (const auto &val : vec)
        std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}