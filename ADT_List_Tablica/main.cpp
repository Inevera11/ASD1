#include "adtlist.h"
#include <iostream>

int main()
{

    // Tworzymy listę z minimalnym rozmiarem 4
    ADTList<int> list;

    // Sprawdźmy, czy lista jest pusta
    if (list.isEmpty())
    {
        std::cout << "Lista jest pusta. size: " << list.size() << std::endl;
    }

    // Dodajmy elementy na koniec listy
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    std::cout << "Dodano elementy 10, 20, 30 na koniec." << std::endl;

    // Dodajmy elementy na początek listy
    list.push_front(5);
    list.push_front(6);
    std::cout << "Dodano element 5, 6 na początek." << std::endl;

    list.insert(3, 7);
    std::cout << "Wstawiono element 7 pod index 3." << std::endl;

    // Wyświetlmy zawartość listy
    std::cout << "Aktualna zawartość listy: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Dostęp do 1 elementu: " << list.front() << " Dostęp do ostatniego elementu: " << list.back() << std::endl;

    // Wyświetlmy zawartość listy po posortowaniu:
    list.sort();
    std::cout << "Zawartość listy po posortowaniu: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    ADTList<int> list2;
    list2.push_back(4);
    list2.push_back(8);
    list2.push_back(9);

    std::cout << "Utworzono drugą ADT list, do ktrej dodano elementy 5, 6, 7 na koniec. Zmergujemy teraz obie listy." << std::endl;
    list.merge(list2);
    std::cout << "Zawartość listy po zmergowaniu: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    // Usuńmy element z końca
    std::cout << "Usunięto element " << list.pop_back() << " z końca. ";

    // Wyświetlmy zawartość listy po usunięciu
    std::cout << "Zawartość listy: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    // Usuńmy element z początku
    std::cout << "Usunięto element " << list.pop_front() << " z początku. ";

    // Wyświetlmy zawartość listy po usunięciu
    std::cout << "Zawartość listy: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    // Usuńmy konkretny element z początku
    std::cout << "Usunięto element " << list.erase(2) << " z indexu 2. ";

    // Wyświetlmy zawartość listy po usunięciu
    std::cout << "Zawartość listy: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.clear();
    std::cout << "Zawartość listy po wyczyszczeniu (size " << list.size() << ") :";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}