#ifndef CTABLE_H
#define CTABLE_H

#include <iostream>

class CTable {
    public:
        //  Konstruktory
        CTable();                               //  Konstruktor bezparametrowy
        CTable(std::string sName, int iTableLen);    //  Konstruktor z parametrem
        CTable(const CTable &pcOther);                //  Konstruktor kopiujący

        ~CTable();                              //  Destruktor

        //  Metody
        void setName(std::string sName);
        bool bSetNewSize(int iTableLen);
        CTable* pcClone();

        // Metody pomocnicze
        void v_print_table();                                       //  Wyświetlanie zawartości tablicy
        int* pi_copy_table_contents(int iTableLen, int* piTable);   //  Kopiowanie zawartości tablicy
        int* pi_copy_table_contents(int iTableLen, const CTable &pcOther);
        bool b_fill_table(int iTableLen, int iFillingValue, int* piTable);        //  Wypełnianie tablicy zadaną wartością
        int iGetSize();
        std::string sGetName();
        int* piGetPointer();

    private:
        std::string s_name;
        int i_table_len;
        int* pi_table;
};

//  Pozostałe metody
void v_mod_tab(CTable *pcTab, int iNewSize);
void v_mod_tab(CTable cTab, int iNewSize);

#endif //CTABLE_H
