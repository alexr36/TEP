#include "CTree.h"
#include "Constants.h"

//  --  Klasa CNode ----------------------------------------------------------------------------------------------------

//  Konstruktor domyślny
CNode::CNode() {
    cn_left_child = NULL;
    cn_right_child = NULL;
    s_node_value = s_DEFAULT_NODE_VALUE;
    i_children_count = 0;
    pcn_children = NULL;
}

//  Destruktor
CNode::~CNode() {
    if (pcn_children != NULL) {
        delete[] pcn_children;
    }
}

//  --  Gettery --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --
std::string CNode::sGetValue() {
    return s_node_value;
}

CNode* CNode::pcnGetRightChild() {
    return cn_right_child;
}

CNode* CNode::pcnGetLeftChild() {
    return cn_left_child;
}

CNode** CNode::pcnGetChildren() {
    return pcn_children;
}

//  --  Settery --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --
void CNode::vSetValue(std::string sValue) {
    s_node_value = sValue;
}

void CNode::vSetLeftChild(CNode *cnLeftChild) {
    cn_right_child = cnLeftChild;
}

void CNode::vSetRightChild(CNode *cnRightChild) {
    cn_left_child = cnRightChild;
}

//  --  Pozostałe metody --  --  --  --  --  --  --  -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

void CNode::vAddChild(CNode *cnChild) {
    if (i_children_count < i_MAX_CHILDREN_COUNT) {
        CNode** pcn_new_children = new CNode*[i_children_count + 1];

        for (int i = 0; i < i_children_count; i++) {
            pcn_new_children[i] = pcn_children[i];
        }

        pcn_new_children[i_children_count] = cnChild;
        delete pcn_children;
        pcn_children = pcn_new_children;
        i_children_count++;
    }
}

//  --  Klasa CTree ----------------------------------------------------------------------------------------------------
