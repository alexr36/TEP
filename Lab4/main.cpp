#include <iostream>

#include "CError.h"
#include "CResult.h"
#include "CResultSaver.h"

CResult<double, CError> eDivide(double dDividend, double dDivisor) {
    if (dDivisor == 0) return CResult<double, CError>::fail(new CError("Nie mozna dzielic przez zero."));

    return CResult<double, CError>::ok(dDividend / dDivisor);
}

CResult<CTree, CError> createTree(CTree *tree, std::string &formula) {
    if (formula == "") return CResult<CTree, CError>::fail(new CError("Nie udało utworzyć się drzewa."));

    tree->enter(formula);

    return CResult<CTree, CError>::ok(*tree);
}

void test() {
    CResult<double, CError> result = eDivide(10.0, 0.0);
    CResultSaver<double>::save(result, "result_or_errors.txt");

    if (result.isSuccess()) {
        std::cout << "Wynik: " << *result.getValue() << "\n";
    }
    else {
        std::vector<CError*>& errors = result.getErrors();

        for (int i = 0; i < errors.size(); i++) {
            std::cout << "Blad: " << errors[i]->getMessage() << "\n";
        }
    }

    CResult<CTree, CError> resultTree = CTree();
    std::string valid_formula = "+ * 5 sin x * + a b 8";
    std::string invalid_formula = "";

    std::string formula = invalid_formula;
    resultTree = createTree(new CTree(), formula);
    CResultSaver<CTree>::save(resultTree, "result_or_errors_tree.txt");

    if (resultTree.isSuccess()) {
        if (resultTree.getValue()->getRoot() != NULL) {
            std::cout << "Drzewo: " << resultTree.getValue()->convertTreeToString() << "\n";
        }
    }
    else {
        std::vector<CError*>& errors = resultTree.getErrors();

        for (int i = 0; i < errors.size(); i++) {
            std::cout << "Blad: " << errors[i]->getMessage() << "\n";
        }
    }
}

int main() {
    test();

    return 0;
}
