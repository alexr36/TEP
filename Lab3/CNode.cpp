#include "CNode.h"
#include <iostream>

#include "Constants.h"

//  --  Klasa COperatorNode --------------------------------------------------------------------------------------------


//  Konstruktor przeciążony
COperatorNode::COperatorNode(const std::string &operation, int childrenCount, int maxChildrenCount) {
    operation_type = operation;                                                                                         //  Inicjalizacja pól klasy
    children_count = childrenCount;
    children = new CNode*[childrenCount];
    max_children_count = maxChildrenCount;

    for (int i = 0; i < childrenCount; i++) {                                                                           //  Inicjalizacja tablicy potomków jako pustej
        children[i] = NULL;
    }
}


//  Konstruktor kopiujący
COperatorNode::COperatorNode(const COperatorNode &other) {
    operation_type = other.operation_type;                                                                              //  Przepisanie wartości pól klasy
    children_count = other.children_count;
    max_children_count = other.max_children_count;
    children = new CNode*[children_count];                                                                              //  Rezerwacja odpowiedniej przestrzeni dla tablicy potomków

    copyNodeContents(*this, other);                                                                                 //  Skopiowanie tablicy potomków
}


//  Destruktor
COperatorNode::~COperatorNode() {
    for (int i = 0; i < children_count; i++) {                                                                          //  Usuwanie każdego obiekty CNode z tablicy potomków
        delete children[i];
    }

    delete[] children;                                                                                                    //  Usunięcie tablicy potomków
}


//  Obliczanie wartości węzła korzystając z wartości dla zmiennej
double COperatorNode::compute(double varValue) {
    double result = INT_MIN;

    // Zależnie od typu operacji, wywołanie odpowiedniej logiki
    if (operation_type == ADDING_OPERATOR) {
        result = 0;

        for (int i = 0; i < children_count; i++) {
            result += (children[i] != NULL) ? children[i]->compute(varValue) : 0;
        }
    }
    else if (operation_type == SUBTRACTING_OPERATOR) {
        if (children[0] != NULL && children[1] != NULL) {
            result = children[0]->compute(varValue) - children[1]->compute(varValue);
        }
    }
    else if (operation_type == MULTIPLICATION_OPERATOR) {
        result = 1;

        for (int i = 0; i < children_count; i++) {
            result *= (children[i] != NULL) ? children[i]->compute(varValue) : 1;
        }
    }
    else if (operation_type == DIVISION_OPERATOR) {
        if (children[0] != NULL && children[1] != NULL) {
            if (children[1]->compute(varValue) == 0) {
                result = INT_MAX;
            }
            else {
                result = children[0]->compute(varValue) / children[1]->compute(varValue);
            }
        }
    }
    else if (operation_type == SINUS_OPERATOR) {
        if (children[0] != NULL) result = sin(children[0]->compute(varValue));
    }
    else if (operation_type == COSINUS_OPERATOR) {
        if (children[0] != NULL) result = cos(children[0]->compute(varValue));
    }

    return result;
}


//  Obliczanie wartości formuły korzystając ze zbioru zmiennych
double COperatorNode::compute(const std::map<std::string, double> &variableValues) {
    double result = INT_MIN;

    // Zależnie od typu operacji, wywołanie odpowiedniej logiki
    if (operation_type == ADDING_OPERATOR) {
        result = 0;

        for (int i = 0; i < children_count; i++) {
            result += (children[i] != NULL) ? children[i]->compute(variableValues) : 0;
        }
    }
    else if (operation_type == SUBTRACTING_OPERATOR) {
        if (children[0] != NULL && children[1] != NULL) {
            result = children[0]->compute(variableValues) - children[1]->compute(variableValues);
        }
    }
    else if (operation_type == MULTIPLICATION_OPERATOR) {
        result = 1;

        for (int i = 0; i < children_count; i++) {
            result *= (children[i] != NULL) ? children[i]->compute(variableValues) : 1;
        }
    }
    else if (operation_type == DIVISION_OPERATOR) {
        if (children[0] != NULL && children[1] != NULL) {
            if (children[1]->compute(variableValues) == 0) {
                result = INT_MAX;
            }
            else {
                result = children[0]->compute(variableValues) / children[1]->compute(variableValues);
            }
        }
    }
    else if (operation_type == SINUS_OPERATOR) {
        if (children[0] != NULL) {
            result = sin(children[0]->compute(variableValues));
        }
    }
    else if (operation_type == COSINUS_OPERATOR) {
        if (children[0] != NULL) {
            result = cos(children[0]->compute(variableValues));
        }
    }

    return result;
}


//  Wyświetlanie węzła wraz - wartiant prefix
void COperatorNode::printPrefixNode() {
    std::cout << operation_type;                                                                                        //  Wyświetlenie rodzaju operacji

    for (int i = 0; i < children_count; i++) {
        std::cout << " ";

        if (children[i] != NULL) children[i]->printPrefixNode();                                                        //  Jeśli potomek istnieje to wyświetlamy jego zawartość
    }
}


//  Wyświetlanie węzła wraz - wartiant postfix
void COperatorNode::printPostfixNode() {
    for (int i = 0; i < children_count; ++i) {
        if (children[i] != NULL) {
            children[i]->printPostfixNode();
            std::cout << " ";
        }
    }

    std::cout << operation_type;
}


//  Wyświetlanie węzła wraz - wartiant infix
void COperatorNode::printInfixNode() {
    // Operator jednoargumentowy
    if (children_count == 1) {
        std::cout << operation_type << "(";
        if (children[0] != NULL) {
            children[0]->printInfixNode();
        }

        std::cout << ")";
        return;
    }

    // Operator wieloargumentowy
    if (children_count > 1) std::cout << "(";

    for (int i = 0; i < children_count; ++i) {
        if (children[i] != NULL) {
            children[i]->printInfixNode();
        }

        if (i < children_count - 1) {
            std::cout << " " << operation_type << " ";
        }
    }

    if (children_count > 1) std::cout << ")";
}


//  Kopiowanie węzła
CNode* COperatorNode::copyNode() {
    COperatorNode* copiedNode = new COperatorNode(*this);                                                               //  Inicjalizacja wskaźnika na kopiowany obiekt

    for (int i = 0; i < children_count; i++) {
        if (children[i] != NULL) copiedNode->children[i] = children[i]->copyNode();                                     //  Jeśli potomek istnieje wykonujemy dla niego operację kopiowania
    }

    return copiedNode;                                                                                                  //  Zwrócenie kopii
}


//  Dodawanie potomka do węzła
void COperatorNode::addChild(CNode* child) {
    if (children_count < max_children_count) {                                                                          //  Dodawanie potomka jest możliwe tylko, gdy węzeł nie jest 'zapełniony'
        CNode** newChildren = new CNode*[children_count + 1];                                                           //  Inicjalizacja tablicy wskaźników na węzły (potomków)

        for (int i = 0; i < children_count; i++) {                                                                      //  Przekopiowanie istniejących potomków do nowej tablicy
            newChildren[i] = children[i];
        }

        newChildren[children_count] = child;                                                                            //  Dopisanie nowego węzła jako potomka
        delete[] children;                                                                                              //  Usunięcie dotychczasowej tablicy potomków
        children = newChildren;                                                                                         //  Nadpisanie pustej tablicy potomków nowostworzoną tablicą z dodanym węzłem
        children_count++;                                                                                               //  Inkrementacja licznika potomków węzła
    }
}


//  Sprawdzanie czy węzeł ma wszystkich potomków
bool COperatorNode::isFullyPopulated() {
    return children_count >= max_children_count;
}


//  Zwracanie następnego w kolejce węzła-potomka bez wszystkich swoich potomków
CNode* COperatorNode::getNextUnpopulatedChild() {
    for (int i = 0; i < children_count; i++) {
        if (children[i] == NULL) return this;                                                                           // Zwracanie operatora, który wymaga uzupełnienia

        if (children[i]->isOperator()) {                                                                                //  Dla każdego potomka będącego operatorem wykonujemy przeszukanie wśród jego potomków
            CNode* unpopulated = children[i]->getNextUnpopulatedChild();

            if (unpopulated != NULL) return unpopulated;
        }
    }

    return NULL;                                                                                                        // Brak 'nieuzupełnionych' potomków
}


//  Konwersja węzłą na postać drukowalną
std::string COperatorNode::toString() {
    std::string result = operation_type;

    for (int i = 0; i < getMaxChildrenCount(); i++) {
        CNode* child = getChild(i);

        if (child != NULL) result += " " + child->toString();
    }

    return result;
}

//  --  Settery   --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

void COperatorNode::setChild(int index, CNode *child) {
    if (index >= 0 && index < children_count) {
        delete children[index];
        children[index] = child;
    }
}

void COperatorNode::setMaxChildrenCount(int maxChildrenCount) {
    if (maxChildrenCount > 0) {
        max_children_count = maxChildrenCount;
    }
}

//  --  Gettery   --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

int COperatorNode::getMaxChildrenCount() {
    return max_children_count;
}

int COperatorNode::getChildrenCount() {
    return children_count;
}

CNode* COperatorNode::getChild(int index) {
    if (index >= 0 && index < children_count) {
        return children[index];
    }
}

std::string COperatorNode::getOperationType() {
    return operation_type;
}


//  Kopiowanie zawartości węzła (z potomkami włącznie)
void COperatorNode::copyNodeContents(COperatorNode &source, const COperatorNode &destination) {
    for (int i = 0; i < source.children_count; i++) {
        if (destination.children[i] != NULL) {
            source.setChild(i, destination.children[i]->copyNode());                                                //  Jeśli potomek istnieje wykonujemy dla niego operację kopiowania
        }
    }
}

//  --  Klasa CConstantNode --------------------------------------------------------------------------------------------

//  Konstruktor przeciążony
CConstantNode::CConstantNode(double val) {
    constant_value = val;                                                                                               //  Przypisanie wartości dla węzła typu stałego
}


//  Konstruktor kopiuący
CConstantNode::CConstantNode(const CConstantNode &other) {
    constant_value = other.constant_value;                                                                              //  Przepisanie wartości dla węzła typu stałego
}


//  Obliczanie wartości węzła korzystając z wartości dla zmiennej
double CConstantNode::compute(double varValue) {
    return constant_value;
}


//  Obliczanie wartości formuły korzystając ze zbioru zmiennych
double CConstantNode::compute(const std::map<std::string, double> &variableValues) {
    return constant_value;
}


//  Wyświetlanie węzła - wartiant prefix
void CConstantNode::printPrefixNode() {
    std::cout << constant_value;
}


//  Wyświetlanie węzła - wartiant postfix
void CConstantNode::printPostfixNode() {
    printPrefixNode();
}


//  Wyświetlanie węzła - wartiant infix
void CConstantNode::printInfixNode() {
    printPrefixNode();
}


//  Kopiowanie węzła
CNode* CConstantNode::copyNode() {
    return new CConstantNode(constant_value);
}


//  Konwersja węzłą na postać drukowalną
std::string CConstantNode::toString() {
    std::ostringstream oss;
    oss << constant_value;

    return oss.str();
}

//  --  Klasa CVariableNode --------------------------------------------------------------------------------------------

//  Konstruktor przeciążony
CVariableNode::CVariableNode(const std::string &varName) {
    variable_name = varName;                                                                                            //  Przypisanie nazwy do zmiennej
}


//  Konstruktor kopiujący
CVariableNode::CVariableNode(const CVariableNode &other) {
    variable_name = other.variable_name;                                                                                //  Przepisanie nazwy zmiennej
}


//  Obliczanie wartości węzła korzystając z wartości dla zmiennej
double CVariableNode::compute(double varValue) {
    return varValue;
}


//  Obliczanie wartości formuły korzystając ze zbioru zmiennych
double CVariableNode::compute(const std::map<std::string, double>& variableValues) {
    std::map<std::string, double>::const_iterator it = variableValues.find(variable_name);

    if (it != variableValues.end()) {
        return it->second;
    }
}


//  Wyświetlanie węzła - wartiant prefix
void CVariableNode::printPrefixNode() {
    std::cout << variable_name;
}


//  Wyświetlanie węzła - wartiant postfix
void CVariableNode::printPostfixNode() {
    printPrefixNode();
}


//  Wyświetlanie węzła - wartiant infix
void CVariableNode::printInfixNode() {
    printPrefixNode();
}



//  Zbieranie zmiennych
void CVariableNode::collectVariables(std::set<std::string> &vars) {
    vars.insert(variable_name);
}


//  Kopiowanie węzła
CNode* CVariableNode::copyNode() {
    return new CVariableNode(variable_name);
}


//  Konwersja węzłą na postać drukowalną
std::string CVariableNode::toString() {
    return variable_name;
}
