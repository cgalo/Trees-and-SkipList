//
// Created by Carlos Galo on 4/1/20.
//

#ifndef TREES___SKIPLIST_AVL_H
#define TREES___SKIPLIST_AVL_H

#include <iostream>

class AVL {
private:
    struct Node
    {
        char data [50] = {};                //Char array as data of the node
        int count;                          //Frequency of data
        int BF;                             //Balance factor of the node
        Node *LCH, *RCH;                    //Node pointers to the children of the node
        Node()
        {
            for (char & i : this->data)     //Set the data of the node as an empty array
                i = '\0';
            this->count = 0;                //Set the count to 0
            this->BF    = 0;                //Set the BF to 0
            LCH = RCH = nullptr;            //Set the pointers to children node's as nil
        }   //End of basic constructor for the Node
        explicit Node(char data[])          //Explicit constructor given a char array
        {
            strcpy(this->data, data);       //Set the given char array as the data of the node
            this->count = 0;                //Set count to 1
            this->BF    = 0;                //Set the balance factor to 1
            LCH = RCH = nullptr;            //Set pointers to children to nil
        }   //End of explicit Node constructor given a char data in the parameter
    };  //End of struct Node

    Node* root;                             //The top of the tree
    int totKeyComparison;                   //Keep track of the total key comparisons done in the search method
    int totItems;                           //Total nodes and count data in the tree
    int distinctItems;                      //Total of unique/distinct tree

    ////The following method should never be called besides by the destructor -> ~BST()
    void treeDestructor (Node* currentNode);    //Traverses the tree to destroy every node in the tree
public:
    AVL();                                  //Basic constructor for the AVL class
    ~AVL();                                 //Destructor for the AVL class, for garbage collection

    void Insert (char X[]);              //Insert word into tree, or if word already exists then increase count


};


#endif //TREES___SKIPLIST_AVL_H
