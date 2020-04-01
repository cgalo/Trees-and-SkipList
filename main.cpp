#include <iostream>
#include "BST.h"
#include "SkipList.h"   //Call the SkipList class
#include "RBT.h"
int main() {
    RBT* tree = new RBT;
    tree->Insert("car");
    tree->Insert("ann");
    tree->Insert("bar");
    tree->Insert("segura");
    tree->Insert("rob");
    tree->Insert("boston");

    tree->print();

    return 0;
}
