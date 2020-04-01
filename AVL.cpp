//
// Created by Carlos Galo on 4/1/20.
//

#include "AVL.h"

AVL::AVL():root(nullptr),totKeyComparison(0), totItems(0), distinctItems(0){}

AVL::~AVL()
{
    int totKeyComparison    = 0;        //Keep track of the total key comparisons done in the search method
    int totItems            = 0;        //Total nodes and count data in the tree
    int distinctItems       = 0;        //Total of unique/distinct tree
    if (root != nullptr)                //If the tree is not empty
    {
        treeDestructor(root);           //Destroy all nodes in the tree
        root                = nullptr;  //Set the root to nil
    }   //End of if the tree is not empty
}   //End of destructor

void AVL::treeDestructor(AVL::Node *currentNode)
{
    /* treeDestructor private method, parameter(s): node pointer
     * Objective: recurse through the tree and delete all nodes in the tree
     * Warning: ONLY call this method from the destructor -> ~BST()
     */

    if (currentNode != nullptr)
    {
        treeDestructor(currentNode->LCH);
        treeDestructor(currentNode->RCH);
        delete currentNode;
    }   //End of if the currentNode is not NULL
}   //End of treeDestructor method

void AVL::Insert(char *word)
{

}   //End of insert method