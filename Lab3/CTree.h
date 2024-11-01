#ifndef CTREE_H
#define CTREE_H

//  --  Klasa CNode ----------------------------------------------------------------------------------------------------
class CNode {
public:
    CNode();                        //  Konstruktor domyślny
    ~CNode();                       //  Destruktor

    //  --  Settery
    void setValue(int value);
    void addChild(CNode* child);

    //  --  Gettery
    int getValue();
    CNode* getChild();

private:
    CNode* left_child;              //  Lewe dziecko węzła
    CNode* right_child;             //  Prawe dziecko węzła
    CNode* next_sibling;            //  Następne w kolei rodzeństwo
    char* node_value;               //  Wartość węzła
};


//  --  Klasa CTree ----------------------------------------------------------------------------------------------------
class CTree {
    public:
        CTree();                        //  Konstruktor domyślny
        ~CTree();                       //  Destruktor

    //  --  Operatory
        void operator=(CTree &pcOther);         //  Operator przyrówania
        CTree* operator+(CTree &pcOther);       //  Operator dodawania

    //  --  Settery
        void setRoot(CTree* root);

    //  --  Gettery
        CNode* getRoot();

    private:
        CNode* root;                    //  Korzeń drzewa
};
#endif //CTREE_H
