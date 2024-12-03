#include "CTests.h"

#include "Constants.cpp"
#include "CResultSaver.h"

CTests::CTests() {}

CTests::~CTests() {}


void CTests::runTests() {
    //divisionTests();
    //treeCreatingTests();
    modificationTests();
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
    CResultSaver<double>::saveToFile(result, FILENAME_ERRORS_NORMAL);

    if (result.isSuccess()) {
        std::cout << "Wynik: " << result.getValue() << "\n";
    }
    else {
        std::cout << "\nPodczas dzielenia wystapil blad." << "\n";
    }
}


void CTests::divisionTests() {
    dividePositiveTest();
    //divideNegativeTest();
}

//  --  Tworzenie drzewa    --------------------------------------------------------------------------------------------

CResult<CTree, CError> CTests::createTree(std::string &formula) {
    CTree tree;

    return tree.enter(formula);
}


void CTests::createTreeTest(std::string &formula) {
    CResult<CTree, CError> result = createTree(formula);
    CResultSaver<CTree>::saveToFile(result, FILENAME_ERRORS_TREE);

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


//  --  Modyfikacja    -------------------------------------------------------------------------------------------------

CResult<int*, CError> CTests::test0(int value) {
    if (value == 0) return new CError("error!");

    return new int(value);
}


CResult<double *, CError> CTests::test1(int value) {
    return test0(value).toResult<double>(new double(value / 2.0));
}


void CTests::modificationTests() {
    std::cout << test1(0).isSuccess() << "\n";
    std::cout << test1(1).isSuccess() << "\n";
}
