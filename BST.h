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
        char data[50];  //Use a char array of length of 50 as data
        int count;                                  //Frequency of the occurrence of the word
        Node *leftChild, *rightChild, *parentNode;  //Reference nodes, to the node's parent and children

        Node(char* data)  //Constructor given a string
        {
            strcpy(this->data, data);   //Insert the given data into the new node data's
            count = 1;                  //Set frequency to 1
            parentNode = leftChild = rightChild = nullptr;  //Set all pointers to null
        }   //End of Node constructor
    };          //End of struct Node
    Node* root;                 //Top of the tree, first node in the tree
    int totKeyComparison;       //Keep track of the total key comparisons done in the search method
    int totItems;               //Total nodes and count data in the tree
    int distinctItems;          //Total of unique/distinct tree

    Node* search(char* word);   //Looks for node w/ word in the tree, returns node or parent node
    void inOrderPrint(Node* currentNode);
    int height(Node* node);

    ////The following method should never be called besides by the destructor -> ~BST()
    void treeDestructor (Node* currentNode);    //Traverses the tree to destroy every node in the tree

public:
    BST();                  //Basic constructor for the Binary Search Tree
    ~BST();                 //Destructor for the tree for garbage collection

    void Insert(char* word);//Insert function, either updates count or insert new node with given word
    void TreeHeight();      //Get the tree height
    void print();
    void getDistinctItems();
    void getTotItems();



};


#endif //TREES___SKIPLIST_BST_H

/*
int height(Node * currentNode) //Calculate the height of the tree
{
    if( currentNode == nullptr) return 0;
    else
    {
        int l=height(root->left);
        int r=height(root->right);
        if(l>r)
            return l+1;
        else
            return r+1;
    }
}*/
