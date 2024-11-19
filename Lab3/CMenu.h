#ifndef CMENU_H
#define CMENU_H
#include "CTree.h"

class CMenu {
    public:
        void run();                                                                                                     //  Uruchamianie programu - dzialanie menu

    private:
        void enter(CTree &tree, std::istringstream &iss);                                                               //  Wprowadzanie wyrazenia
        void comp(CTree &tree, std::istringstream &iss);                                                                //  Obliczanie wartości wyrażenia
        void join(CTree &tree, std::istringstream &iss);                                                                //  Łączenie drzew
        void help();                                                                                                    //  Wyswietlanie dostepnych polecen

        //  Modyfikacja
        void cntgt(CTree &tree, std::istringstream &iss);                                                               //  Zliczanie stałych większych od zadanej wartości
};

#endif //CMENU_H
