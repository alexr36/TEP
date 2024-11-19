#include "CMenu.h"

#include <iostream>
#include <sstream>

//  Uruchamianie programu - dzialanie menu
void CMenu::run() {
    CTree tree;
    std::string input;
    help();

    do {
        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "enter") {
            enter(tree, iss);
        }
        else if (command == "print") {
            tree.printPrefix();
        }
        else if (command == "comp") {
            comp(tree, iss);
        }
        else if (command == "vars") {
            tree.vars();
        }
        else if (command == "join") {
            join(tree, iss);
        }
        else if (command == "help") {
            help();
        }
        else if (command == "exit") {
            std::cout << "Konczenie pracy programu...\n";
        }
        else if (!command.empty()) {
            std::cout << "Blad: Nieprawodlowe polecenie.\n";
        }
    }
    while (input != "exit");
}


//  Wprowadzanie wyrażenia
void CMenu::enter(CTree &tree, std::istringstream &iss) {
    std::string formula;
    std::getline(iss, formula);
    tree.enter(formula);
}


//  Obliczanie wartości wyrażenia
void CMenu::comp(CTree &tree, std::istringstream &iss) {
    std::map<std::string, double> variableValues;

    // Wczytanie wartości zmiennych
    const std::vector<std::string>& variableNames = tree.getVariableNames(); // Pobierz nazwy zmiennych
    double value;

    for (std::vector<std::string>::const_iterator it = variableNames.begin(); it != variableNames.end(); ++it) {
        const std::string& varName = *it; // Nazwa bieżącej zmiennej

        if (iss >> value) {
            variableValues[varName] = value; // Przypisz wartość do zmiennej
        }
    }

    // Sprawdzenie, czy wprowadzono poprawną liczbę wartości
    if (variableValues.size() == variableNames.size()) {
        tree.comp(variableValues); // Wywołaj metodę obliczeniową
    }
    else {
        std::cout << "Blad: Liczba wprowadzonych wartosci nie zgadza sie z liczba zmiennych.\n";
    }
}


//  Łączenie drzew
void CMenu::join(CTree &tree, std::istringstream &iss) {
    CTree newTree;
    std::string formula;
    std::getline(iss, formula);

    tree = tree + newTree.enter(formula);
}


//  Wyświetlanie dostępnych poleceń
void CMenu::help() {
    std::cout << "> ##### Dostepne polecenia: #####\n";
    std::cout << "> enter <formula>\n";
    std::cout << "> vars\n";
    std::cout << "> print\n";
    std::cout << "> comp <var0> <var1> ... <varN>\n";
    std::cout << "> join <formula>\n";
    std::cout << "> help\n";
    std::cout << "> exit\n";
    std::cout << "> # # # # # # # # # # # # # # # #\n";
}

