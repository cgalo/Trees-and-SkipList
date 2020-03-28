//
// Created by Carlos Galo on 3/25/20.
//

#ifndef TREES___SKIPLIST_SKIPLIST_H
#define TREES___SKIPLIST_SKIPLIST_H

#include <iostream>

class SkipList {
private:
    struct Node
    {
        char data[50] = {};      //Data max of 50 chars
        int count;          //Frequency of the occurrence of the Node's data
        Node *up, *down, *left, *right;    //Pointer to Nodes

        Node()
        {
            for (char & i : this->data)
                i = '\0';
            count = 0;
            up = down = left = right = nullptr;
        }   //End of Node constructor w/ no given parameter(s)
        explicit Node(char data[])    //Node constructor given char array
        {
            strcpy(this->data, data);   //Insert the given data into the new node data's
            count = 1;                  //Set the count/frequency to 1
            up = down = left = right = nullptr; //Set all Node pointers to null
        }   //End of Node constructor, with char array as parameter
    };  //End of struct Node

    //Variables
    Node *head, *tail;  //The start & ending of the SkipList (SL)
    int height;         //Keep track of the height of the SL
    int totKeyCompare;  //Keep track of every time a key-comparison occurs
    int totNodes;       //Keep track of total nodes in the slow lane of the SL
    int totFrequency;   //Keep track of total frequencies in the SL

    //Methods
    Node* find(char word[]);    //Search of node in the SL, return the node with the given parameter in the SkipList
    void createNewLevel();      //Create a new level/lane SkipList
    void printLevel(Node* headlvl);
public:
    SkipList();     //Constructor for our class
    ~SkipList();    //Destructor, for garbage collection

    //Start of the methods
    void Insert(char word[]);    //Insert method, inserts or increases count of node in the SkipList
    void print();               //Traverse to the slow-lane and print all the nodes there

};


#endif //TREES___SKIPLIST_SKIPLIST_H
