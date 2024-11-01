#include "CTable.h"
#include "Constants.h"
#include <iostream>
#include <string>

//  Konstruktor domyślny
CTable::CTable() : s_name(s_DEFAULT_NAME), i_table_len(i_DEFAULT_TABLE_LEN) {
    std::cout << "bezp:\t'" << s_name << "'" << std::endl;
    pi_table = new int[i_table_len];
}

//  Konstruktor z parametrem
CTable::CTable(std::string sName, int iTableLen) {
    s_name = sName;

    std::cout << "parametr:\t'" << s_name << "'" << std::endl;

    i_table_len = iTableLen;
    pi_table = new int[i_table_len];
}

//  Konstruktor kopiujący
CTable::CTable(const CTable &pcOther) {
    s_name = pcOther.s_name + "_copy";
    i_table_len = pcOther.i_table_len;
    //pi_table = new int[i_table_len];

    //for (int i = 0; i < i_table_len; i++) {
    //    pi_table[i] = pcOther.pi_table[i];
    //}

    pi_table = pi_copy_table_contents(i_table_len, pcOther.piGetPointer());

    std::cout << "kopiuj:\t'" << pcOther.s_name << "'" << std::endl;
}

//  Destruktor
CTable::~CTable() {
    delete[] pi_table;

    std::cout << "usuwam:\t'" << s_name << "'" << std::endl;
}

//  Setter dla s_name
void CTable::setName(std::string sName) {
    s_name = sName;
}

//  Setter dla i_table_len
bool CTable::bSetNewSize(int iTableLen) {
    if (iTableLen <= 0) return false;

   // pi_table = new int[i_table_len];
    int* new_table = pi_copy_table_contents(i_table_len, pi_table);
    delete[] pi_table;

    pi_table = new_table; //pi_copy_table_contents(i_table_len, pi_table);

    i_table_len = iTableLen;

    //delete[] pi_table;

    return true;
}

//  Metoda kopiująca
CTable *CTable::pcClone() {
    return new CTable(*this);
}

// -- Metody pomocnicze ------------------------------------------------------------------------------------------------

//  Metoda do wyświetlania zawartości tablicy
void CTable::v_print_table() {
    if (pi_table == NULL) {
        std::cout << "Tablica nie została utworzona." << std::endl;
        return;
    }

    std::cout << "\nNazwa tablicy:\t" << s_name << std::endl;
    std::cout << "\nDlugosc tablicy:\t" << i_table_len << std::endl;
    std::cout << "\nZawartosc tablicy:" << std::endl;

    for (int i = 0; i < i_table_len; i++) {
        std::cout << pi_table[i] << "\t";
    }

    std::cout << "\n" << std::endl;
}

//  Metoda do kopiowania zawartości tablicy
int* CTable::pi_copy_table_contents(int iTableLen, int pi_table[]) {
    int* pi_table_copy = new int[iTableLen];

    for (int i = 0; i < i_table_len; i++) {
        pi_table_copy[i] = pi_table[i];
    }

    //delete[] pi_table;

    return pi_table_copy;
}

 //  Metoda do wypełniania tablicy zadaną wartością
 bool CTable::b_fill_table(int iTableLen, int iFillingValue, int pi_table[]) {
     if (iTableLen <= 0 || pi_table == NULL) return false;

     for (int i = 0; i < iTableLen; i++) {
         pi_table[i] = iFillingValue;
     }

     return true;
}

//  Getter dla i_table_len
int CTable::iGetSize() {
    return i_table_len;
}

//  Getter dla s_name
std::string CTable::sGetName() {
    return s_name;
}

//  Getter dla wskaźnika na tablicę
int *CTable::piGetPointer() {
    return pi_table;
}

//  Pozostałe metody
void v_mod_tab(CTable *pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}