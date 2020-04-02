#include <iostream>
#include "BST.h"
#include "SkipList.h"   //Call the SkipList class
#include "RBT.h"
#include "AVL.h"
int main() {
    RBT* tree = new RBT;
    tree->Insert("MAR");
    tree->Insert("MAY");
    tree->Insert("NOV");
    tree->Insert("AUG");
    tree->Insert("APR");
    tree->Insert("JAN");
    tree->Insert("DEC");
    tree->Insert("JUL");
    tree->Insert("FEB");
    tree->Insert("JUN");
    tree->Insert("OCT");
    tree->Insert("SEP");

    //tree->print();

    return 0;
}
