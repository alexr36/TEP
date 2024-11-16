#include <iostream>
#include <ostream>

#include "CMenu.h"

int main() {
    CMenu menu;
    menu.run();

    /*
    COperatorNode *op_node = new COperatorNode("+", 4, 5);
    op_node->printNode();
    std::cout << "\n";

    CConstantNode *const_node = new CConstantNode(5);
    const_node->printNode();
    std::cout << "\n";

    CVariableNode *var_node = new CVariableNode("v");
    var_node->printNode();
    std::cout << "\n";

    std::cout << "\nKopie:\n";

    COperatorNode *op_copy = new COperatorNode(*op_node);
    op_copy->printNode();
    std::cout << "\n";

    CConstantNode *const_copy = new CConstantNode(*const_node);
    const_copy->printNode();
    std::cout << "\n";

    CVariableNode *var_copy = new CVariableNode(*var_node);
    var_copy->printNode();
    std::cout << "\n";

    delete op_node;
    delete const_node;
    delete var_node;
    delete op_copy;
    delete const_copy;
    delete var_copy;
    */

    return 0;
}
