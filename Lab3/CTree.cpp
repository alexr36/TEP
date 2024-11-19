#include "CTree.h"
#include <iostream>
#include <sstream>
#include <unordered_set>

//  Konstruktor domyślny
CTree::CTree() {
    root = NULL;
    variable_count = 0;
}


//  Konstruktor kopiujący
CTree::CTree(const CTree &other) {
    root = NULL;
    variable_count = other.variable_count;
    variable_names = other.variable_names;

    if (other.root != NULL) root = other.root->copyNode();
}


//  Destruktor
CTree::~CTree() {
    delete root;
}


//  Operator przypisania
CTree &CTree::operator=(const CTree &other) {
    if (this != &other) {                                                                                               //  Zabezpieczenie przed samoprzypisaniem
        delete root;
        root = (other.root != NULL) ? other.root->copyNode() : NULL;
    }

    return *this;
}


//  Operator dodawania
CTree CTree::operator+(const CTree &other) {
    CTree newTree;
    COperatorNode* newRoot = new COperatorNode(ADDING_OPERATOR, BINARY_OPERATOR_ARGS_COUNT);

    // Unikalne zmienne - najpierw zbieramy zmienne w zbiór
    std::set<std::string> unique_variables;
    unique_variables.insert(variable_names.begin(), variable_names.end());
    unique_variables.insert(other.variable_names.begin(), other.variable_names.end());

    // Przepisanie wartości ze zbioru do wektora
    std::vector<std::string> result;

    for (std::set<std::string>::iterator it = unique_variables.begin(); it != unique_variables.end(); it++) {
        result.push_back(*it);
    }

    //  Ustawienie odpowiednich potomków dla nowego korzenia
    newRoot->setChild(0, (root != NULL) ? root->copyNode() : NULL);
    newRoot->setChild(1, (other.root != NULL) ? other.root->copyNode() : NULL);

    //  Aktualizacja korzenia i zbioru zmiennych
    newTree.root = newRoot;
    variable_count = result.size();
    variable_names = result;

    return newTree;
}


//  Wprowadzanie formuły
CTree CTree::enter(const std::string &formula) {
    delete root;                                                                                                        //  Usunięcie poprzedniego korzenia
    root = NULL;

    std::istringstream iss(formula);                                                                                    //  Inicjalizacja iss i przekazanie zmiennej string formula do iss
    std::string token;                                                                                                  //  Inicjalizacja zmiennej do przechowywania procesowanego symbolu
    variable_names.clear();                                                                                             //  Wyczyszczenie zbioru zmiennych
    variable_count = 0;                                                                                                 //  Ustawienie licznika zmiennych na zero
    bool was_corrected = false;                                                                                         //  Inicjalizacja i ustawienie flagi poprawienia formuły

    std::vector<CNode*> pendingNodes;                                                                                   //  Inicjalizacja zbioru oczekujących węzłów

    while (iss >> token) {                                                                                              //  Pętla wykonuje się tak długo, jak we wprowadzonym tekście są symbole
        bool processed = false;                                                                                         //  Inicjalizacja i ustawienie flagi przeprocesowania symbolu

        if (isOperator(token)) {                                                                                        //  Jeśli proceoswany symbol jest operatorem
            COperatorNode* operatorNode = new COperatorNode(token);                                                     //  Inicjalizacja węzła - operatora o podanym symbolu

            if (isUnaryOperator(token)) {                                                                               //  Jeśli procesowany symbol jest operatorem unarnym
                operatorNode->setMaxChildrenCount(UNARY_OPERATOR_ARGS_COUNT);                                           //  Ustawienie liczby argumentów operatora na 1
            }
            else if (isBinaryOperator(token)) {                                                                         //  Jeśli procesowany symbol jest operatorem binarnym
                operatorNode->setMaxChildrenCount(BINARY_OPERATOR_ARGS_COUNT);                                          //  Ustawienie liczby argumentów operatora na 2
            }
            else {                                                                                                      //  Jeśli wprowadzony został nieprawidłowy symbol -> usuń procesowany węzeł
                std::cout << "Nieprawidłowy operator: " << token << "\n";
                delete operatorNode;
                processed = true;                                                                                       //  Oznaczenie formuły jako przeprocesowanej
            }

            if (!processed) {                                                                                           //  Jeśli formuła nie została przeprocesowana
                if (root == NULL) {                                                                                     //  Jeśli korzeń nie istnieje - ustawienie operatora jako korzenia
                    root = operatorNode;
                }
                else {                                                                                                  //  Jeśli korzeń istnieje
                    while (!pendingNodes.empty() && pendingNodes.back()->isFullyPopulated()) {                          //  Pętla wykonuje się tak długo jak istnieją nieprzeprocesowane węzły oraz ostatni węzeł jest 'wypełniony'
                        pendingNodes.pop_back();                                                                        //  Usunięcie ostatiego węzła w kolejce
                    }

                    if (!pendingNodes.empty()) {                                                                        //  Jeśli istnieją nieprzeprocesowane węzły
                        pendingNodes.back()->addChild(operatorNode);                                                    //  Dodanie ostatniego operatora jako potomka ostatniego węzła w kolejce
                    }
                    else {                                                                                              //  Jeśli nie istnieją nieprzeprocesowane węzły
                        std::cout << "Blad: Operator w niewlasciwym miejscu.\n";
                        delete operatorNode;                                                                            //  Usuń węzeł - operator
                        processed = true;                                                                               //  Oznaczenie formuły jako przeprocesowanej
                    }
                }
            }

            if (!processed) {                                                                                           //  Jeśli formuła nie została przeprocesowana
                pendingNodes.push_back(operatorNode);                                                                   //  Dodanie na koniec kolejki węzła - operatora
            }
        }
        else if (isdigit(token[0])) {                                                                                   //  Jeśli procesowany symbol jest wartością liczbową
            double value = std::atof(token.c_str());                                                                    //  Konwersja na typ double z typu string
            CConstantNode* constantNode = new CConstantNode(value);                                                     //  Inicjalizacja węzła - stałej

            if (root == NULL) {                                                                                         //  Jeśli korzeń nie istnieje - ustawienie stałej jako korzenia
                root = constantNode;
            }
            else {                                                                                                      //  Jeśli korzeń istnieje
                while (!pendingNodes.empty() && pendingNodes.back()->isFullyPopulated()) {                              //  Pętla wykonuje się tak długo jak istnieją nieprzeprocesowane węzły oraz ostatni węzeł jest 'wypełniony'
                    pendingNodes.pop_back();                                                                            //  Usunięcie ostatiego węzła w kolejce
                }

                if (!pendingNodes.empty()) {                                                                            //  Jeśli istnieją nieprzeprocesowane węzły
                    pendingNodes.back()->addChild(constantNode);                                                        //  Dodanie ostatniego operatora jako potomka ostatniego węzła w kolejce
                }
                else {                                                                                                  //  Jeśli nie istnieją nieprzeprocesowane węzły
                    std::cout << "Blad: Liczba w niewlasciwym miejscu.\n";
                    delete constantNode;                                                                                //  Usuń węzeł - stalą
                }
            }
        }
        else if (isalpha(token[0])) {                                                                                   //  Jeśli procesowany symbol jest wartością zmienną
            CVariableNode* variableNode = new CVariableNode(token);                                                     //  Inicjalizacja węzła - zmiennej

            if (std::find(variable_names.begin(), variable_names.end(), token) == variable_names.end()) {               //  Jeśli zmienna nie znajduje się w zbiorze zmienncyh
                variable_names.push_back(token);                                                                        //  Dodanie symbolu zmiennej do listy zimennych
                variable_count++;                                                                                       //  Inkrementacja licznika zmiennych
            }

            if (root == NULL) {                                                                                         //  Jeśli korzeń nie istnieje - ustawienie zmiennej jako korzenia
                root = variableNode;
            }
            else {                                                                                                      //  Jeśli korzeń istnieje
                while (!pendingNodes.empty() && pendingNodes.back()->isFullyPopulated()) {                              //  Pętla wykonuje się tak długo jak istnieją nieprzeprocesowane węzły oraz ostatni węzeł jest 'wypełniony'
                    pendingNodes.pop_back();                                                                            //  Usunięcie ostatiego węzła w kolejce
                }

                if (!pendingNodes.empty()) {                                                                            //  Jeśli istnieją nieprzeprocesowane węzły
                    pendingNodes.back()->addChild(variableNode);                                                        //  Dodanie ostatniego operatora jako potomka ostatniego węzła w kolejce
                }
                else {                                                                                                  //  Jeśli nie istnieją nieprzeprocesowane węzły
                    std::cout << "Blad: Zmienna w niewlasciwym miejscu.\n";
                    delete variableNode;                                                                                //  Usuń węzeł - zmienna
                }
            }
        }
        else {                                                                                                          //  Jeśli nie rozpoznano procesowanego symbolu - powiadom o tym
            std::cout << "Pominieto niewlasciwy symbol: " << token << "\n";
        }
    }

    while (!pendingNodes.empty()) {                                                                                     //  Jeśli istnieją nieprzeprocesowane węzły
        CNode* node = pendingNodes.back();                                                                              //  Inicjalizacja wskaźnika na ostatni węzeł w kolejce

        while (!node->isFullyPopulated()) {                                                                             //  Pętla działa tak długo jak ostatni węzeł w kolejce nie został 'wypełniony'
            std::cout << "Blad: Za malo argumentow dla operatora. Uzupelnianie wartoscia domyslna.\n";
            node->addChild(new CConstantNode(DEFAULT_NODE_VALUE));                                                      //  Dodanie do procesowanego węzła potomka o domyślnej wartości
            was_corrected = true;                                                                                       //  Oznaczenie formuły jako poprawionej
        }

        pendingNodes.pop_back();                                                                                        //  Usunięcie ostatniego węzła z kolejki
    }

    if (root == NULL) {                                                                                                 //  Jeśli korzeń nie istnieje
        std::cout << "Wyrazenie niekompletne. Dodano domyślny węzeł.\n";
        root = new CConstantNode(DEFAULT_NODE_VALUE);                                                                   //  Ustawienie węzła o domyślnej wartości jako korzenia
    }

    if (was_corrected) {                                                                                                //  Jeśli formuła została oznaczona jako poprawiona
        std::cout << "Przetwarzana formuła: ";
        printPrefix();                                                                                                  //  Pokazaine poprawioną formułę
    }

    return *this;                                                                                                       //  Zwrócenie wskaźnika
}


//  Wyświetlanie drzewa - wariant prefix
void CTree::printPrefix() {
    if (root != NULL) {
        root->printPrefixNode();
        std::cout << "\n";
    }
    else std::cout << "Nie wprowadzono formuly.\n";
}


//  Wyświetlanie drzewa - wariant postfix
void CTree::printPostfix() {
    if (root != NULL) {
        root->printPostfixNode();
        std::cout << "\n";
    }
    else std::cout << "Nie wprowadzono formuly.\n";
}


//  Wyświetlanie drzewa - wariant infix
void CTree::printInfix() {
    if (root != NULL) {
        root->printInfixNode();
        std::cout << "\n";
    }
    else std::cout << "Nie wprowadzono formuly.\n";
}


//  Obliczanie wartości formuły korzystając ze zbioru zmiennych
void CTree::comp(const std::map<std::string, double> &variableValues) {
    if (root == NULL) {
        std::cout << "Brak wyrazenia do obliczenia wartosci." << std::endl;
        return;
    }

    // Przekazanie wartości zmiennej do metody dla obliczenia wartości konkretnego węzłą
    double result = root->compute(variableValues);
    std::cout << "Wynik: " << result << std::endl;
}


//  Obliczanie wartości podformuły korzystając z wartości dla zmiennej
void CTree::comp(const double varValue) {
    // Zakładając, że metoda powinna obsługiwać wszystkie zmienne
    std::map<std::string, double> variableValues;

    // Dodawanie zmienneych do mapy (w przypadku, gdy mamy do czynienia z konkretnymi zmiennymi)
    std::string variable_name;
    for (int i = 0; i < variable_count; i++) {
        std::cin >> variable_name;
        variableValues[variable_name] = varValue;
    }

    // Wywołanie compute dla każdego węzła w drzewie
    if (root != NULL) {
        double result = root->compute(variableValues);
        std::cout << "Wynik: " << result << std::endl;
    }
    else {
        std::cout << "Brak formuły." << std::endl;
    }
}


//  Wypisanie zmiennych w formule
void CTree::vars() {
    std::cout << "Zmienne: ";

    if (root != NULL && !root->isOperator()) {
        std::set<std::string> variables;

        root->collectVariables(variables);

        std::cout << *variables.begin();
    }
    else {
        for (std::vector<std::string>::const_iterator it = variable_names.begin(); it != variable_names.end(); it++) {
            std::cout << *it << " ";
        }
    }

    std::cout << "\n";
}


std::string CTree::convertTreeToString() {
    if (root == NULL) return "";
/*
    std::string result = root->toString();
    CNode* currentNode = root;

    for (int i = 0; i < currentNode->getChildrenCount(); i++) {
        result += " " + currentNode->toString();
        currentNode = currentNode->getChild(i);
    }
*/

    std::string result = root->toString();
    return result + "\n";
}


//  Sprawdzenie czy symbol jest operatorem
bool CTree::isOperator(const std::string &token) {
    return isUnaryOperator(token) || isBinaryOperator(token);
}

//  Sprawdzenie czy symbol jest operatorem unarnym
bool CTree::isUnaryOperator(const std::string &token) {
    return token == SINUS_OPERATOR || token == COSINUS_OPERATOR;
}

//  Sprawdzenie czt symbol jest operatorem binarnym
bool CTree::isBinaryOperator(const std::string &token) {
    return token == ADDING_OPERATOR || token == SUBTRACTING_OPERATOR || token == MULTIPLICATION_OPERATOR || token == DIVISION_OPERATOR;
}

//  Wyszukiwanie węzłów bez wszystkich potomków
CNode* CTree::findNodeNeedingChild(CNode* node) {
    if (node->isOperator() && !node->isFullyPopulated()) {
        return node;
    }

    for (int i = 0; i < node->getChildrenCount(); i++) {
        CNode* foundNode = findNodeNeedingChild(node->getChild(i));

        if (foundNode) {
            return foundNode;
        }
    }
    return NULL;
}

//  --  Gettery --------------------------------------------------------------------------------------------------------

CNode* CTree::getRoot() {
    return root;
}

int CTree::getVariableCount() {
    return variable_count;
}

std::vector<std::string> CTree::getVariableNames() {
    return variable_names;
}
