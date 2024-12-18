#include <iostream>
#include "/Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.h"

//  --  Modyfikacja ----------------------------------------------------------------------------------------------------

void printChain(int &&chain_len) {
    for (int i = 0; i < chain_len * 2; i++) {
        std::cout << "*- ";
    }

    std::cout << "\n";
}

void printChain(int &chain_len) {
    for (int i = 0; i < chain_len; i++) {
        std::cout << "*- ";
    }

    std::cout << "\n";
}


int main() {
    CTree tree1;
    tree1.enter("+ * 3 2 x");

    std::cout << "Tree 1 (prefix): ";
    tree1.printPrefix();
    std::cout << "\nTree 1 (postfix): ";
    tree1.printPostfix();
    std::cout << "\nTree 1 (infix): ";
    tree1.printInfix();
    std::cout << "\nZmienne w Tree 1: " << tree1.vars() << "\n";

    // Test konstruktora kopiującego
    CTree tree2 = tree1;
    std::cout << "\nTree 2 (kopia Tree 1): ";
    tree2.printPrefix();

    // Test operatora przypisania
    CTree tree3;
    tree3 = tree1;
    std::cout << "\nTree 3 (przypisane z Tree 1): ";
    tree3.printPrefix();

    // Test operatora przeniesienia
    CTree tree4 = std::move(tree1);
    std::cout << "\nTree 4 (przeniesione z Tree 1): ";
    tree4.printPrefix();
    std::cout << "\nTree 1 po przeniesieniu (powinno byc puste): ";
    tree1.printPrefix();

    // Test operatora przypisania przenoszącego
    CTree tree5;
    tree5 = std::move(tree2);
    std::cout << "\nTree 5 (przeniesione operatorem z Tree 2): ";
    tree5.printPrefix();
    std::cout << "\nTree 2 po przeniesieniu operatorem (powinno byc puste): ";
    tree2.printPrefix();

    // Test operatora dodawania
    CTree tree6 = tree4 + tree5;
    std::cout << "\nTree 6 (Tree 4 + Tree 5): ";
    tree6.printPrefix();
    std::cout << "\nZmienne w Tree 6: " << tree6.vars() << "\n";

    // Test liczby zmiennych i liczenia stałych większych od wartości
    double valueThreshold = 2.5;
    std::cout << "\nStale w Tree 6 większe niż " << valueThreshold << ": "
              << tree6.countConstantsGreaterThan(valueThreshold) << "\n";

    // Test modyfikacji drzewa
    CTree tree7;
    tree7.enter("+ sin x cos y");
    std::cout << "\nTree 7 (nowa formula): ";
    tree7.printPrefix();
    std::cout << "\nZmienne w Tree 7: " << tree7.vars() << "\n";

    // Test działania semantyki przeniesienia w dużej pętli
    CTree tree8;
    for (int i = 0; i < 10; ++i) {
        CTree tempTree;
        tempTree.enter("+ x " + std::to_string(i));
        tree8 = std::move(tempTree);  // Move-assignment w pętli
    }

    std::cout << "\nTree 8 po 10 iteracjach przeniesienia: ";
    tree8.printPrefix();
    std::cout << "\nZmienne w Tree 8: " << tree8.vars() << "\n";

    std::cout << "\nTree 8: ";
    tree8.printPrefix();

    std::cout << "\nTree 7: ";
    tree7.printPrefix();

    std::cout << "\nTree 6: ";
    tree6.printPrefix();

    std::cout << "\nTree 9 (Tree 8 + Tree 7 + Tree 6): ";
    CTree tree9 = tree8 + tree7 + tree6;
    tree9.printPrefix();


    //  --  Modyfikacja ------------------------------------------------------------------------------------------------

    std::cout << "\nModyfikacja:\n";
    int val = 5;
    std::cout << "Oczekiwane 6 lancuchow: ";
    printChain(3);             //  Duplikowanie wartosci podanej czyli łańcuch 6-elementowy

    std::cout << "Oczekiwane 5 lancuchow: ";
    printChain(val);        //  Normalnie, 5 elementów

    return 0;
}