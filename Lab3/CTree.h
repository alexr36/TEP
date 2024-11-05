#ifndef CTREE_H
#define CTREE_H
#include <string>

//  --  Klasa CNode ----------------------------------------------------------------------------------------------------
class CNode {
    public:
        CNode();                                    //  Konstruktor domyślny
        CNode(const CNode &cnOther);                //  Konstruktor kopiujący
        ~CNode();                                   //  Destruktor

        //  --  Settery -------------------------------------------------------------
        void vSetValue(std::string sValue);
        void vSetLeftChild(CNode* cnLeftChild);
        void vSetRightChild(CNode* cnRightChild);

        //  --  Gettery -------------------------------------------------------------
        std::string sGetValue();
        CNode* pcnGetLeftChild();
        CNode* pcnGetRightChild();
        CNode** pcnGetChildren();

        //  --  Pozostałe metody ----------------------------------------------------
        void vAddChild(CNode* cnChild);             //  Dodawanie potomka do węzła

    private:
        //  Pola klasy
        CNode* cn_left_child;                       //  Lewe dziecko węzła
        CNode* cn_right_child;                      //  Prawe dziecko węzła
        std::string s_node_value;                   //  Wartość węzła
        int i_children_count;                       //  Licznik potomków węzła
        CNode** pcn_children;                       //  Wskaźnik na tablicę dzieci
};


//  --  Klasa CTree ----------------------------------------------------------------------------------------------------
class CTree {
    public:
        CTree();                                //  Konstruktor domyślny
        CTree(const CTree &ctOther);            //  Konstruktor kopiujący
        ~CTree();                               //  Destruktor

        //  --  Operatory   ---------------------------------------------------------
        void operator=(const CTree &pctOther);         //  Operator przyrówania
        CTree* operator+(const CTree &pctOther);       //  Operator dodawania

        //  --  Settery -------------------------------------------------------------
        void setRoot(CNode* cnRoot);

        //  --  Gettery -------------------------------------------------------------
        CNode* getRoot();

    private:
        //  Pola klasy
        CNode* cn_root;                         //  Korzeń drzewa

};
#endif //CTREE_H
