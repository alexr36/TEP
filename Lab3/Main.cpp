#include <iostream>
#include <ostream>

#include "CMenu.h"

void test() {
    std::cout << "Oryginaly:\n";

    COperatorNode *op_node = new COperatorNode("+", 0, 2);
    op_node->addChild(new CConstantNode(2));
    op_node->addChild(new CConstantNode(3));
    op_node->printPrefixNode();
    std::cout << "\n";

    CConstantNode *const_node = new CConstantNode(5);
    const_node->printPrefixNode();
    std::cout << "\n";

    CVariableNode *var_node = new CVariableNode("v");
    var_node->printPrefixNode();
    std::cout << "\n";

    COperatorNode *new_op_node = new COperatorNode("*", 0, 2);
    new_op_node->addChild(const_node);
    new_op_node->addChild(var_node);
    new_op_node->printPrefixNode();
    std::cout << "\n";

    std::cout << "\nKopie:\n";

    COperatorNode *op_copy = new COperatorNode(*op_node);
    op_copy->printPrefixNode();
    std::cout << "\n";

    CConstantNode *const_copy = new CConstantNode(*const_node);
    const_copy->printPrefixNode();
    std::cout << "\n";

    CVariableNode *var_copy = new CVariableNode(*var_node);
    var_copy->printPrefixNode();
    std::cout << "\n";

    COperatorNode *new_op_copy = new COperatorNode(*new_op_node);
    new_op_copy->printPrefixNode();
    std::cout << "\n";

    delete op_node;
    delete const_node;
    delete var_node;
    delete op_copy;
    delete const_copy;
    delete var_copy;

    std::cout << "\n";

    CTree tree = CTree();
    tree.enter("+ * 5 sin x * + a b 8");

    std::cout << "Oryginal:\n";

    std::cout << tree.convertTreeToString();

    std::cout << "\nKopie:\n";

    CTree copyTree = tree;
    std::cout << copyTree.convertTreeToString();

    CTree newTree = CTree(tree);
    std::cout << newTree.convertTreeToString();
}

int main() {
    CMenu menu;
    menu.run();

    //test();

    return 0;
}
