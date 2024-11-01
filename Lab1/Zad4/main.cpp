//  ZADANIE 4

#include <iostream>
#include "Constants.h"
#include "CTable.h"

//  -- MODYFIKACJA -----------------------------------------------------------------------------------------------------

int iMax(int* piTable, int iLength) {
    //  Sprawdzenie czy mozna przeprowadzic operacje
    if (piTable == NULL || iLength < 0) {
        std::cout << "\nBlad: przekazany wskaznik jest rowny NULL lub przekazana dlugosc tablicy jest mniejsza od zera." << std::endl;
        return INT_MIN;
    }

    //  Inicjalizacja zmiennej do przechowywania maksyalnej wartosci
    int i_max_value = piTable[0];

    //  Obliczanie maksymalnej wartosci
    for (int i = 0; i < iLength; i++) {
        if (piTable[i] > i_max_value) i_max_value = piTable[i];
    }

    //  Zwrocenie wartosci
    return i_max_value;
}

int main() {
    //  --  Testy konstruktorow ----------------------------------------------------------------------------------------

    CTable c_table_def;                                         // Test konstruktora bezparametrowego
    CTable c_table_param("Test", i_PARAM_TABLE_LEN);      //  Test konstruktora z parametrem
    CTable c_table_copy(c_table_param);                         //  Test konstruktora kopiującego

    //  --  Test klonowania --------------------------------------------------------------------------------------------

    /*
        Metoda klonująca jest podobna funkcjonalnie do konstruktora kopiującego,
        a zatem w celu niepowielania kodu, nalezałoby zrezygnować z tej metody,
        polegając jedynie na odpowiednim konstruktorze
    */

    std::cout << "\n-------------------------- Sklonowana tablica:  --------------------------" << std::endl;
    CTable* pc_new_tab = c_table_param.pcClone();
    pc_new_tab->v_print_table();

    std::cout << "\n------------------------ Tablica, ktora klonowano: -----------------------" << std::endl;
    c_table_param.v_print_table();

    //  --  Test funkcji modyfikujących --------------------------------------------------------------------------------

    std::cout << "\n-------------------------- Oryginalna tablica: ---------------------------" << std::endl;

    c_table_def.b_fill_table(c_table_def.iGetSize(), i_FILLING_VALUE, c_table_def.piGetPointer());

    c_table_def.v_print_table();

    std::cout << "\n------------------------ Modyfikacja przez kopie:  ------------------------" << std::endl;
    v_mod_tab(c_table_def, i_NEW_TABLE_LEN);       //  Modyfikacja przez kopię - nie modyfikuje oryginalnego obiektu
    c_table_def.v_print_table();

    std::cout << "\n----------------------- Modyfikacja przez wskaznik:  ----------------------" << std::endl;
    v_mod_tab(&c_table_def, i_NEW_TABLE_LEN);        //  Modyfikacja przez wskaźnik - modyfikuje oryginalny obiekt
    c_table_def.v_print_table();

    //  --  Test alokacji  ---------------------------------------------------------------------------------------------

    std::cout << "Test alokacji:" << std::endl;

    CTable c_static_table;              //  Alokacja statyczna
    CTable* pc_dynamic_table_copy;      //  Alokacja dynamiczna - deklaracja wskaźnika na dynamiczny obiekt

    pc_dynamic_table_copy = new CTable(c_static_table);   //  Tworzona jest dynamiczna kopia statycznego obiektu

    CTable c_static_table_copy(c_static_table);             //  Tworzona jest statyczna kopia statycznego obiektu

    std::cout << "\nAlokacja i dealokacja tablicy obiektow klasy CTable: " << std::endl;

    CTable* c_table = new CTable[i_DEFAULT_TABLE_LEN];

    delete[] c_table;

    //  Dealokacja pamięci

    std::cout << "\nDealokacja pozostalej czesci pamieci:" << std::endl;

    delete pc_new_tab;
    delete pc_dynamic_table_copy;

    //  Test modyfikacji
    std::cout << "\n==========Test modyfikacji:==============" << std::endl;
    CTable c_modif_table_test_1("Name", i_PARAM_TABLE_LEN);


    for (int i = 0; i < c_modif_table_test_1.iGetSize(); i++) {
        c_modif_table_test_1.piGetPointer()[i] = i + 1;
    }


    c_modif_table_test_1.v_print_table();
    std::cout << "Najwieksza wartosc 1:\t" << iMax(c_modif_table_test_1.piGetPointer(), c_modif_table_test_1.iGetSize()) << std::endl;

    std::cout << "\n====================================================" << std::endl;

    CTable c_modif_table_test_2("Name2", 5);

    c_modif_table_test_2.piGetPointer()[0] = 125;
    c_modif_table_test_2.piGetPointer()[1] = 56;
    c_modif_table_test_2.piGetPointer()[2] = 256;
    c_modif_table_test_2.piGetPointer()[3] = 255;
    c_modif_table_test_2.piGetPointer()[4] = 12;

    c_modif_table_test_2.v_print_table();
    std::cout << "Najwieksza wartosc 2:\t" << iMax(c_modif_table_test_2.piGetPointer(), c_modif_table_test_2.iGetSize()) << std::endl;

    std::cout << "============Koniec modyfikacji==============\n" << std::endl;

    return 0;
}