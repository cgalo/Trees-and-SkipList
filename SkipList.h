//
// Created by Carlos Galo on 3/25/20.
//

#ifndef TREES___SKIPLIST_SKIPLIST_H
#define TREES___SKIPLIST_SKIPLIST_H

#include <iostream>

class SkipList {
private:
    struct Node                                     //Start of struct Node
    {
        char data[50] = {};                         //Data max of 50 chars
        int count;                                  //Frequency of the occurrence of the Node's data
        Node *up, *down, *left, *right;             //Pointer to nodes left, next, up & down

        Node()                                      //Basic constructor for node
        {
            for (char & i : this->data)             //Let the data array to be an empty char array
                i = '\0';
            count = 0;                              //Set count/frequency to 0
            up = down = left = right = nullptr;     //Set all node pointers to nil
        }   //End of Node constructor w/ no given parameter(s)
        explicit Node(char data[])                  //Node constructor given char array
        {
            strcpy(this->data, data);               //Insert the given data into the new node data's
            count = 1;                              //Set the count/frequency to 1
            up = down = left = right = nullptr;     //Set all Node pointers to null
        }   //End of Node explicit constructor, with char array as parameter
    };  //End of struct Node

    //Variables
    Node *head, *tail;              //The start & ending of the SkipList (SL) fastest lane, also our sentinels
    int height;                     //Keep track of the height of the SL, this will be the fastest-lane in the SL
    int totKeyComparison;           //Keep track of every time a key-comparison occurs
    int distinctWords;              //Total nodes in the slow-lane
    int totWords;                   //Total of the all the node's frequencies in the slow lane of the SL

    //Methods needed for SL
    Node* find(char word[]);        //Search of node in the SL, return the node with the given parameter in the SkipList
    void createNewLevel();          //Create a new level/lane SkipList

    //Methods to calculate metrics
    int calcHeight();               //Calculate how many levels we have in the SkipList by traversing down the lanes
    int nodesInLane(Node* lvlHead); //Traverse the current head of the



public:
    SkipList();                     //Constructor to initialize the class/object
    ~SkipList();                    //Destructor, for garbage collection (GC)

    //Methods
    void Insert(char word[]);       //Insert method, inserts or increases count of node in the SkipList
    void printLanes();              //Print total nodes in each lane, starting from the fastest lane to the slowest lane
    void displayStatistics();       //Display all the metrics for BSTree

};
#endif //TREES___SKIPLIST_SKIPLIST_H
