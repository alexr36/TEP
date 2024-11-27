#include "CTests.h"
#include "CResultSaver.h"

CTests::CTests() {}

CTests::~CTests() {}


void CTests::runTests() {
    //divisionTests();
    treeCreatingTests();
}



//  --  Dzielenie   ----------------------------------------------------------------------------------------------------

CResult<double, CError> CTests::divide(double dividend, double divisor) {
    if (divisor == 0) return CResult<double, CError>::fail(new CError("Nie mozna dzielic przez zero.\n"));

    return CResult<double, CError>::ok(dividend / divisor);
}

void CTests::dividePositiveTest() {
    CResult<double, CError> result_positive = divide(1.0, 10.0);

    std::cout << "Wynik: " << result_positive.getValue();

    CResult<double, CError> copy = CResult<double, CError>(result_positive);

    std::cout << "\nWynik (op. kop.): " << copy.getValue();

    CResult<double, CError> copy_second = result_positive;

    std::cout << "\nWynik ('='): " << copy_second.getValue();
}


void CTests::divideNegativeTest() {
    CResult<double, CError> result = divide(1.0, 0);
    CResultSaver<double>::saveToFile(result, "result_errors.txt");

    if (result.isSuccess()) {
        std::cout << "Wynik: " << result.getValue() << "\n";
    }
    else {
        std::cout << "\nPodczas dzielenia wystapil blad." << "\n";
    }
}


void CTests::divisionTests() {
    //dividePositiveTest();
    divideNegativeTest();
}

//  --  Tworzenie drzewa    --------------------------------------------------------------------------------------------

CResult<CTree, CError> CTests::createTree(std::string &formula) {
    CTree tree;

    return tree.enter(formula);
}


void CTests::createTreeTest(std::string &formula) {
    CResult<CTree, CError> result = createTree(formula);
    CResultSaver<CTree>::saveToFile(result, "result_tree_errors.txt");

    // Wyświetlenie wyniku drzewa
    if (result.isSuccess()) {
        std::cout << "Drzewo: " << result.getValue().convertTreeToString() << "\n";
    }
    else {
        std::cout << "Przy tworzeniu drzewa wystapily bledy." << "\n";
    }
}


void CTests::treeCreatingTests() {
    std::string formula_positive = "+ * 5 sin x * + a b 8";
    std::string formula_negative = "* 5";
    createTreeTest(formula_positive);
    //createTreeTest(formula_negative);
}
