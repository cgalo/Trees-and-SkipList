//
// Created by Carlos Galo on 3/30/20.
//

#ifndef TREES___SKIPLIST_RBT_H
#define TREES___SKIPLIST_RBT_H

#include <iostream>

class RBT {
private:
    enum Color { black, red };              //For the two colors that a Node can have in a RBTree
    struct Node
    {
        char data [50] = {};                //Initialize empty char array as data
        int count;                          //Frequency the data appears
        Node* LCH, *RCH, *parent;           //Pointers to our children
        int color;
        Node()                              //Basic node constructor, no given parameter(s)
        {
            for (char & i : this->data)     //Initialize this node with an empty data array
                i = '\0';
            this->count = 0;                //Set count/frequency to 0
            LCH = RCH = parent = nullptr;   //Set children pointers & parent to nil
            this->color = red;              //Set the color to red
        }   //End of basic node constructor
        explicit Node (char data[])         //Explicit node constructor given a char array
        {
            strcpy(this->data, data);       //Copy the given array to the new node's data array
            this->count = 1;                //Set the frequency to 1
            LCH = RCH = parent = nullptr;   //Set all children pointers & parent to nil
            this->color = red;              //Set color to red
        }   //End of explicit Node constructor, given a char array
    };  //End of struct Node

    Node* root;                             //Top of the tree
    long totKeyComparison;                  //Keep track of the total key comparisons done in the search method
    long totWords;                          //Total nodes and count data in the tree
    long distinctWords;                     //Total of unique/distinct tree
    long refChanges;                        //Total reference changes
    long recolorTot;                        //Keep track of every time we recolor a node
    long leftRotTot;                        //Keep track of every time a left rotation is perform
    long rightRotTot;                       //Keep track of every time a right rotation is perform
    long totCaseOne;                        //Keep track of every time a Case 1 is performed
    long totCaseTwo;                        //Keep track of every time a Case 2 is performed
    long totCaseThree;                      //Keep track of every time a Case 3 is performed

    Node* search    (char word[]);          //Traverse the tree to find a node with the given <word>/data
    void InsertFixUp(Node* z);              //Helper method to maintain RBT rules after inserting a new node in the tree
    void LeftRotate (Node* X);              //Perform a left-rotation (LR) in the tree
    void RightRotate(Node* pt);             //Perform a right-rotate (RR) in the tree
    void inOrderTraversal(Node* node);      //Traverse the tree in order
    int calcHeight(Node* node);             //Recurse the tree and return the current height of the tree
    ////The following method should never be called besides by the destructor -> ~RBT()
    void treeDestructor (Node* currentNode);    //Traverses the tree to destroy every node in the tree

public:
    RBT();                                  //Basic constructor for the RBT class
    ~RBT();                                 //Destructor for the RBT class

    void Insert (char word[]);              //Basic insert function, either inserts or updates count of a node
    void displayStatistics();               //Display all metrics for RBTree

};


#endif //TREES___SKIPLIST_RBT_H
