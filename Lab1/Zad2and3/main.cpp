//  ZADANIE 2

#include <iostream>
#include "constants.h"

//  Metoda do sprawdzania, czy podane wymiary tablicy dwuwymiarowej są poprawne
bool b_check_size(int iSizeX, int iSizeY) {
    return iSizeX <= 0 || iSizeY <= 0;
}

/*
    Jeśli nie jest mozliwe przekazanie wskaźnika przez referencję,
    mozna przekazać wskaźnik do owego wskaźnika tak,
    by modyfikowana była jego wartość, a nie tworzona przez funckję jego kopia
*/

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    //  Sprawdzenie, czy przekazany wskaźnik nie jest równy NULL oraz czy podane wymiary są poprawne
    if (piTable == NULL || b_check_size(iSizeX, iSizeY)) {
        return false;
    }

    //  Ustawienie wskaźnika na tablicę wskaźników o rozmiarze iSizeX
    *piTable = new int *[iSizeX];

    //  Utworzenie tablicy int dla każdego wskaźnika w utworzonej tablicy wskaźników
    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new int[iSizeY];

        //  Sprawdzenie, czy wskaźniki na tablice zostały zainicjalizowane poprawnie
        //  Jeśli nie -> dealokacja dotychczas zaalokowanej pamięci
        if ((*piTable)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                delete[] *piTable[j];
            }

            //  Dealokacja pierwotnej tablicy wskaźników
            delete[] *piTable[i];
            return false;
        }
    }

    //  Jeśli nie wykryto błędow w alokacji -> pamięć zaalokowana poprawnie
    return true;
}

//  ZADANIE 3

/*
    Poniźsza funkcja moźe mieć mniej parametrów
    (niepptrzebne: int iSizeY - ponieważ nie rezerwujemy miejsca w pamięci o wymaganym wymiarze iSizeY,
    przy dealokacji wystarczy użyć polecenia delete[],
    aby zwolnić zarezerwowany obszar pamięci w przypadku tablicy - nie musimy znać rozmiaru zaalokowanego obszaru
    pamięci w celu zwolnienia go)
 */

/*
    Nie jest konieczne przekazywanie wskaźnika przez referencję ani przez kolejny wskaźnik w przypadku dealokacji
    (mozna przekazać sam wskaźnik przez jego wartość (jako argument)), gdyż wystarczy, że zwolnimy obszar pamięci,
    na który dany wskaźnik wskazuje, niepotrzebne jest modyfikowanie samego wskaźnika
*/

bool b_dealloc_table_2_dim(int **piTable, int iSizeX) {
    //  Jeśli wskaźnik wskazuje na puste miejsce w pamięci -> nie ma moliwości deaalokacji niezaalokowanego obszaru pamięci
    if (piTable == NULL) {
        return false;
    }

    //  Dealokacja kazdego wiersza zaalokowanej tablicy
    for (int i = 0; i < iSizeX; i++) {
        if (piTable[i] == NULL) {
            return false;
        }

        delete[] piTable[i];
    }

    //  Dealokacja pierwotnej tablicy wskaźnikow
    delete[] piTable;

    //  Jeśli nie wykryto błędow w dealokacji -> pamięć dealokowana poprawnie
    return true;
}


int main() {
    //  Deklaracja zmiennej wskaźnikowej (wskaźnik na wskaźnik)
    int **pi_table;

    //  Test alokacji
    //  W przypadku alokacji, jako agrument przekazujemy adres pamięci, pod ktorym przechowywana jest wartośćwskaźnika
    if (b_alloc_table_2_dim(&pi_table, i_SIZE_X, i_SIZE_Y)) {
        std::cout << "Alokacja pamieci zakonczona powodzeniem." << std::endl;
    }
    else {
        std::cout << "Alokacja pamieci zakonczona niepowodzeniem." << std::endl;
    }

    //  Test dealokacji
    //  W przypadku dealokacji, jako argument przekazujemy wskaźnik przez wartość
    if (b_dealloc_table_2_dim(pi_table, i_SIZE_X)) {
        std::cout << "Dealokacja pamieci zakonczona powodzeniem." << std::endl;
    }
    else {
        std::cout << "Dealokacja pamieci zakonczona niepowodzeniem." << std::endl;
    }

    return 0;
}