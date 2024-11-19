#ifndef CRESULTSAVER_H
#define CRESULTSAVER_H
#include <fstream>
#include "CError.h"
#include "CResult.h"
#include "/Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.h"

//  --  Ogólny szablon  ------------------------------------------------------------------------------------------------

class CTree;

template<typename T>
class CResultSaver {
    public:
        static void save(CResult<T, CError> &result, const std::string &fileName) {
            std::ofstream file(fileName);

            if (!file.is_open()) return;

            std::vector<CError*> &errors = result.getErrors();

            if (!errors.empty()) {
                for (int i = 0; i < errors.size(); ++i) {
                    file << "Blad: " << errors[i]->getMessage() << "\n";
                }
            }
            else {
                file << "Wynik: " << *result.getValue() << "\n";
            }

            file.close();
        }
};

//  --  Specjalizacja dla CTree  ---------------------------------------------------------------------------------------

template<>
class CResultSaver<CTree> {
    public:
        static void save(CResult<CTree, CError> &result, const std::string &fileName) {
            std::ofstream file(fileName);

            if (!file.is_open()) return;

            std::vector<CError*> &errors = result.getErrors();

            if (!errors.empty()) {
                for (int i = 0; i < errors.size(); ++i) {
                    file << "Blad: " << errors[i]->getMessage() << "\n";
                }
            }
            else {
                file << "Drzewo: " << result.getValue()->convertTreeToString() << "\n";
            }

            file.close();
        }
};

#endif //CRESULTSAVER_H
