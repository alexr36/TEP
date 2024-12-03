#ifndef CTESTS_H
#define CTESTS_H
#include "CError.h"
#include "CResult.h"
#include "/Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.h"

class CTests {
public:
    CTests();
    ~CTests();

    //  --  Dzielenie   ------------------------------------------------------------------------------------------------

    CResult<double, CError> divide(double dividend, double divisor);
    void dividePositiveTest();
    void divideNegativeTest();
    void divisionTests();

    //  --  Tworzenie drzewa    ----------------------------------------------------------------------------------------

    CResult<CTree, CError> createTree(std::string &formula);
    void createTreeTest(std::string &formula);
    void treeCreatingTests();

    //  --  Modyfikacja ------------------------------------------------------------------------------------------------

    CResult<int*, CError> test0(int value);
    CResult<double*, CError> test1(int value);
    void modificationTests();

    void runTests();
};



#endif //CTESTS_H
