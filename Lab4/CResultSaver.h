#ifndef CRESULTSAVER_H
#define CRESULTSAVER_H

#include <fstream>
#include "CResult.h"
#include "/Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.h"


//  --  Definicja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T>
class CResultSaver {
    public:
        static void saveToFile(CResult<T, CError> &result, const std::string &fileName);                                //  Zapisywanie wyników do pliku
};

//  --  Implementacja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T>
void CResultSaver<T>::saveToFile(CResult<T, CError> &result, const std::string &fileName) {                             //  Zapisywanie wyników do pliku
    std::ofstream file(fileName);                                                                                       //  Otworzenie strumienia zapisującego do pliku

    if (!file.is_open()) return;                                                                                        //  Jeśli strumień nie został otwarty to wyjście

    if (!result.getErrors().empty()) {                                                                                  //  Jeśli istnieją błędy w wektorze błędów
        for (int i = 0; i < result.getErrors().size(); ++i) {                                                           //  Dla każdego błędu
            file << "Blad: " << result.getErrors()[i]->getMessage() << "\n";                                            //  Zapisz do pliku jego opis
        }
    }

    file.close();                                                                                                       //  Zamknięcie strumienia zapisującego do pliku
}

//  --  Specjalizacja dla typu CTree -----------------------------------------------------------------------------------

//  --  Definicja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<>
class CResultSaver<CTree> {
public:
    static void saveToFile(CResult<CTree, CError> &result, const std::string &fileName);                                //  Zapisywanie wyników do pliku
};

//  --  Implementacja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

inline void CResultSaver<CTree>::saveToFile(CResult<CTree, CError> &result, const std::string &fileName) {
    std::ofstream file(fileName);                                                                                       //  Otworzenie strumienia zapisującego do pliku

    if (!file.is_open()) return;                                                                                        //  Jeśli strumień nie został otwarty to wyjście

    if (!result.getErrors().empty()) {                                                                                  //  Jeśli istnieją błędy w wektorze błędów
        for (int i = 0; i < result.getErrors().size(); ++i) {                                                           //  Dla każdego błędu
            file << "Blad: " << result.getErrors()[i]->getMessage() << "\n";                                            //  Zapisanie do pliku jego opisu
        }
    }
    else {                                                                                                              //  Jeśli nie istniały błędy
        file << "Drzewo: " << result.getValue().convertTreeToString() << "\n";                                          //  Zapisanie do pliku wynikowe drzewo
    }

    file.close();                                                                                                       //  Zamknięcie strumienia zapisującego do pliku
}


#endif //CRESULTSAVER_H
