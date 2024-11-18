#ifndef CNODE_H
#define CNODE_H
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <sstream>

//  Klasa CNode - abstrakcyjna
class CNode {
    public:
        CNode() { parent = NULL; }                                                                                      //  Konstruktor domyślny
        virtual ~CNode() {}                                                                                             //  Destruktor
        virtual double compute(double varValue) = 0;                                                                    //  Obliczanie wartości węzła korzystając z wartości dla zmiennej
        virtual double compute(const std::map<std::string, double> &variableValues) = 0;                                //  Obliczanie wartości formuły korzystając ze zbioru zmiennych
        virtual void printNode() = 0;                                                                                   //  Wyświetlanie zawartości węzła wraz z potomkami
        virtual void collectVariables(std::set<std::string> &vars) = 0;                                                 //  Zbieranie zmiennych
        virtual CNode* copyNode() = 0;                                                                                  //  Kopiowanie węzła
        virtual bool isOperator() { return false; }                                                                     //  Sprawdzanie czy węzeł jest operatorem
        virtual bool isConstant() { return false; }                                                                     //  Sprawdzanie czy węzeł jest stałą
        virtual bool isVariable() { return false; }                                                                     //  Sprawdzanie czy węzeł jest zmienną
        virtual void addChild(CNode* child) {}                                                                          //  Dodawanie potomka do węzła
        virtual bool isFullyPopulated() = 0;                                                                            //  Sprawdzanie czy węzeł ma wszystkich potomków
        virtual std::string toString() = 0;                                                                             //  Konwersja węzłą na postać drukowalną

        //  Settery
        virtual void setParent(CNode* newParent) { parent = newParent; }

        //  Gettery
        virtual CNode* getParent() { return parent; }
        virtual int getChildrenCount() { return 0; }
        virtual CNode* getChild(int index) { return NULL; }
        virtual CNode* getNextUnpopulatedChild() = 0;

    protected:
        CNode* parent;                                                                                                  //  Węzeł - rodzic
};

//  --  Podklasy dziedziczące z CNode   --------------------------------------------------------------------------------

//  Podklasa węzeł-operator
class COperatorNode : public CNode {
    public:
        COperatorNode(const std::string &operation, int childrenCount = 0, int maxChildrenCount = 1);                   //  Konstruktor przeciążony
        COperatorNode(const COperatorNode &other);                                                                      //  Konstruktor kopiujący
        ~COperatorNode();                                                                                               //  Destruktor
        double compute(double varValue);                                                                                //  Obliczanie wartości węzła korzystając z wartości dla zmiennej
        double compute(const std::map<std::string, double> &variableValues);                                            //  Obliczanie wartości formuły korzystając ze zbioru zmiennych
        void printNode();                                                                                               //  Wyświetlanie zawartości węzła wraz z potomkami
        void collectVariables(std::set<std::string> &vars) {}                                                           //  Zbieranie zmiennych
        CNode* copyNode();                                                                                              //  Kopiowanie węzła
        bool isOperator() { return true; }                                                                              //  Sprawdzanie czy węzeł jest operatorem
        bool isConstant() { return false; }                                                                             //  Sprawdzanie czy węzeł jest stałą
        bool isVariable() { return false; }                                                                             //  Sprawdzanie czy węzeł jest zmienną
        void addChild(CNode *child);                                                                                    //  Dodawanie potomka do węzła
        bool isFullyPopulated();                                                                                        //  Sprawdzanie czy węzeł ma wszystkich potomków
        CNode* getNextUnpopulatedChild();                                                                               //  Zwracanie następnego w kolejce węzła-potomka bez wszystkich swoich potomków
        std::string toString();                                                                                         //  Konwersja węzłą na postać drukowalną

        //  Settery
        void setChild(int index, CNode *child);
        void setMaxChildrenCount(int maxChildrenCount);

        //  Gettery
        int getMaxChildrenCount();
        int getChildrenCount();
        CNode* getChild(int index);
        std::string getOperationType();

    private:
        void copyNodeContents(COperatorNode &source, const COperatorNode &destination);                                 //  Kopiowanie zawartości węzła (z potomkami włącznie)

        std::string operation_type;                                                                                     //  Typ operacji
        CNode** children;                                                                                               //  Lista dzieci węzła
        int children_count;                                                                                             //  Licznik dzieci węzła
        int max_children_count;                                                                                         //  Maksymalna liczba potomków
};

//  Podklasa węzeł-stała
class CConstantNode : public CNode {
    public:
        CConstantNode(double val);                                                                                      //  Konstruktor przeciążony
        CConstantNode(const CConstantNode &other);                                                                      //  Konstruktor kopiujący
        double compute(double varValue);                                                                                //  Obliczanie wartości węzła korzystając z wartości dla zmiennej
        double compute(const std::map<std::string, double> &variableValues);                                            //  Obliczanie wartości formuły korzystając ze zbioru zmiennych
        void printNode();                                                                                               //  Wyświetlanie zawartości węzła
        void collectVariables(std::set<std::string> &vars) {}                                                           //  Zbieranie zmiennych
        CNode* copyNode();                                                                                              //  Kopiowanie węzła
        bool isOperator() { return false; }                                                                             //  Sprawdzanie czy węzeł jest operatorem
        bool isConstant() { return true; }                                                                              //  Sprawdzanie czy węzeł jest stałą
        bool isVariable() { return false; }                                                                             //  Sprawdzanie czy węzeł jest zmienną
        void addChild(CNode *child) {}                                                                                  //  Dodawanie potomka do węzła
        bool isFullyPopulated() { return true; }                                                                        //  Sprawdzanie czy węzeł ma wszystkich potomków
        CNode* getNextUnpopulatedChild() { return NULL; }                                                               //  Zwracanie następnego w kolejce węzła-potomka bez wszystkich swoich potomków
        std::string toString();                                                                                         //  Konwersja węzłą na postać drukowalną

    private:
        double constant_value;                                                                                          //  Wartość stałej
};

//  Podklasa węzeł-zmienna
class CVariableNode : public CNode {
    public:
        CVariableNode(const std::string &varName);                                                                      //  Konstruktor przeciążony
        CVariableNode(const CVariableNode &other);                                                                      //  Konstruktor kopiujący
        double compute(double varValue);                                                                                //  Obliczanie wartości węzła korzystając z wartości dla zmiennej
        double compute(const std::map<std::string, double> &variableValues);                                            //  Obliczanie wartości formuły korzystając ze zbioru zmiennych
        void printNode();                                                                                               //  Wyświetlanie zawartości węzła
        void collectVariables(std::set<std::string> &vars);                                                             //  Zbieranie zmiennych
        CNode* copyNode();                                                                                              //  Kopiowanie węzła
        bool isOperator() { return false; }                                                                             //  Sprawdzanie czy węzeł jest operatorem
        bool isConstant() { return false; }                                                                             //  Sprawdzanie czy węzeł jest stałą
        bool isVariable() { return true; }                                                                              //  Sprawdzanie czy węzeł jest zmienną
        void addChild(CNode *child) {}                                                                                  //  Dodawanie potomka do węzła
        bool isFullyPopulated() { return true; }                                                                        //  Sprawdzanie czy węzeł ma wszystkich potomków
        CNode* getNextUnpopulatedChild() { return NULL; }                                                               //  Zwracanie następnego w kolejce węzła-potomka bez wszystkich swoich potomków
        std::string toString();                                                                                         //  Konwersja węzłą na postać drukowalną

    private:
        std::string variable_name;                                                                                      //  Nazwa zmiennej
};

#endif //CNODE_H
