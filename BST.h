//
// Created by Carlos Galo on 3/23/20.
//

#ifndef TREES___SKIPLIST_BST_H
#define TREES___SKIPLIST_BST_H

#include <iostream>

class BST {
private:
    struct Node
    {
        char data[50] = {};                         //Use a char array of length of 50 as data
        int count;                                  //Frequency of the occurrence of the word
        Node *leftChild, *rightChild;               //Pointers to the node's children
        Node ()
        {
            for (char & i : this->data) i = '\0';   //Leave the data array of this node empty
            this->count = 0;                        //Set the count/frequency to 0
            leftChild = rightChild = nullptr;       //Set all children pointers to null
        }   //End of constructor, no given parameter(s)

        explicit Node(char data[])                  //Constructor given a string
        {
            strcpy(this->data, data);               //Insert the given data into the new node data's
            this->count = 1;                        //Set frequency to 1
            leftChild = rightChild = nullptr;       //Set all pointers to null
        }   //End of Node constructor
    };  //End of struct Node

    Node* root;                                     //Top of the tree, first node in the tree
    long totKeyComparison;                          //Keep track of the total key comparisons done in the search method
    long totWords;                                  //Total addition of all the counts' of the nodes in the tree
    long distinctWords;                             //Total of nodes in the tree

    Node* search(char word[]);                      //Looks for node w/ word in the tree, returns node or parent node
    void inOrderPrint(Node* currentNode);           //Recurse, in order, the tree to calculate totWords & distinctWords
    int calcHeight(Node* node);                     //Recurse the tree and return the current height of it

    ////The following method should never be called besides by the destructor -> ~BST()
    void treeDestructor (Node* currentNode);        //Traverses the tree to destroy every node in the tree

public:
    BST();                                          //Basic constructor for the Binary Search Tree
    ~BST();                                         //Destructor for the tree for garbage collection

    void Insert(char word[]);                       //Basic insert function, either inserts or updates count of a node
    void printMetrics();                            //Display all the metrics for BSTree
};


#endif //TREES___SKIPLIST_BST_H