#ifndef CTREE_H
#define CTREE_H
#include <string>
#include "CNode.h"
#include "Constants.h"

class CTree {
    public:
        CTree();                                                                                                        //  Konstruktor domyślny
        CTree(const CTree &other);                                                                                      //  Konstruktor kopiujący
        ~CTree();                                                                                                       //  Destruktor

        CTree& operator=(const CTree &other);                                                                           //  Operator przypisania
        CTree operator+(const CTree &other);                                                                            //  Operator dodawania

        CTree enter(const std::string &formula);                                                                        //  Wprowadzanie formuły
        void print();                                                                                                   //  Wyświetlanie drzewa
        void comp(const std::map<std::string, double> &variableValues);                                                 //  Obliczanie wartości formuły korzystając ze zbioru zmiennych
        void comp(double varValue);                                                                                     //  Obliczanie wartości podformuły korzystając z wartości dla zmiennej
        void vars();                                                                                                    //  Wypisanie zmiennych w formule
        std::string convertTreeToString();                                                                              //  Konwersja drzewa na postać drukowalną

        //  Gettery
        CNode* getRoot();
        int getVariableCount();
        std::vector<std::string> getVariableNames();

    private:
        bool isOperator(const std::string &token);                                                                      //  Sprawdzenie czy symbol jest operatorem
        bool isUnaryOperator(const std::string &token);                                                                 //  Sprawdzenie czy symbol jest operatorem unarnym
        bool isBinaryOperator(const std::string &token);                                                                //  Sprawdzenie czt symbol jest operatorem binarnym
        CNode* findNodeNeedingChild(CNode* node);                                                                       //  Wyszukiwanie węzłów bez wszystkich potomków

        CNode* root;                                                                                                    //  Korzeń drzewa
        int variable_count;                                                                                             //  Licznik zmiennych w drzewie
        std::vector<std::string> variable_names;                                                                        //  Zbiór nazw zmiennych
};

#endif //CTREE_H
