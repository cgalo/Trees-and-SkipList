//
// Created by Carlos Galo on 3/25/20.
//

#ifndef TREES___SKIPLIST_SKIPLIST_H
#define TREES___SKIPLIST_SKIPLIST_H


class SkipList {
    struct Node
    {
        char data[50];      //Data max of 50 chars
        int count;          //Frequency of the occurrence of the Node's data
        Node *up, *down, *left, *right;    //
        // Assumes we will never actually attempt to insert either of
        const char NEG_INF [10] = "negInfx";    //These strings
        const char POS_INF [10] = "posInf";     //Into the list


    };  //End of struct Node
    Node* head, tail;   //The start & ending of the SkipList (SL)
    int height;         //Keep track of the height of the SL
    int totNodes;       //Keep track of total nodes in the SL
    int totFrequency;   //Keep track of total frequencies in the SL

};


#endif //TREES___SKIPLIST_SKIPLIST_H
