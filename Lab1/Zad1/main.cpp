//  ZADANIE 1

#include <iostream>
#include "constants.h"

int main() {
    //  Sprawdzenie, czy podany rozmiar tablicy jest większy od zera
    if (i_TABLE_SIZE <= 0) {
        std::cout << "Rozmiar tablicy musi byc wiekszy od zera." << std::endl;
    }

    //  Deklaracja i definicja wskaźnika na początek nowej tablicy
    int* pi_tab = new int[i_TABLE_SIZE];

    //  Wypełnianie tablicy wartościami
    for (int i = 0; i < i_TABLE_SIZE; i++) {
        pi_tab[i] = i_FILLER_VALUE;
    }

    //  Wyświetlanie zawartości tablicy
    std::cout << "Tablica: " << std::endl;
    for (int i = 0; i < i_TABLE_SIZE; i++) {
        std::cout << pi_tab[i] << "\t";
    }

    std::cout << std::endl;

    //  Dealokacja pamięci
    delete[] pi_tab;

    return 0;
}
