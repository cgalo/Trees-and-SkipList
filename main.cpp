#include <iostream>
#include "BST.h"
int main() {
    BST* tree = new BST;
    tree->Insert("car");
    tree->Insert("ann");
    tree->Insert("bar");
    tree->Insert("segura");
    tree->Insert("segura");
    tree->print();
    tree->TreeHeight();
    return 0;
}
