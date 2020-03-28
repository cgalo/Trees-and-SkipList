
//
// Created by Carlos Galo on 3/25/20.
//


#include "SkipList.h"       //Connect to the header file of the SkipList(SL)

#include <time.h>           //For srand(time())

#define NEG_INF "negInf"    //Used to create negative sentinels as node
#define POS_INF "posInf"    //Used to create positive sentinels as node

SkipList::SkipList()
{
    //Basic constructor for the SkipList(SL) with no parameter(s)

    //head = new Node ("");  //Create new negative sentinel
    //tail = new Node ("POS_INF");  //Create new positive sentinel
    head = new Node(NEG_INF);
    tail = new Node(POS_INF);
    head->right = tail;         //Connect the head to the tail
    tail->left  = head;         //Connect the tail to the head

    height          = 1;        //Height is set to 1 for the slow lane
    totKeyCompare   = 0;        //Total key-comparisons done
    totNodes        = 0;        //Total nodes in the SL
    totFrequency    = 0;        //Total count of all the nodes' count

    srand(time(nullptr));          //Makes sure to keep random numbers randomized
}   //End of constructor

////Still need to finish the destructor
SkipList::~SkipList()
{
    //Destructor for the SL object, called when 'delete' SkipList

    height          = 0;    //Height
    totKeyCompare   = 0;    //Total key-comparisons done
    totNodes        = 0;    //Total nodes in the SL
    totFrequency    = 0;    //Total count of all the nodes' count

    ////Now we need to traverse the SL and delete all the nodes
    ////

}   //End of destructor


SkipList::Node* SkipList::find(char *word)
{
    /* find private method, parameter(s): char array <word>
     * Objective: Returns a slow-lane pointer to either the node containing data <word>
     *            or the slow-lane node preceding where <word> would be in the list
     **/

    Node* currentNode = head;   //Get the pointer of the current head
    while (true)
    {
        //Move current node until currentNode's right neighbor node contains a key value > given parameter(word)
        while ((strcmp(currentNode->right->data, POS_INF) != 0) && strcmp(currentNode->right->data, word) <= 0)
            currentNode = currentNode->right;
        if (currentNode->down == nullptr)   //If there is now lower
            return currentNode;
        currentNode = currentNode->down;    //Move to a slower lane
    }   //End of while-loop
}   //End of find method

void SkipList::createNewLevel()
{
    /* CreateNewLevel private method, parameter(s): None
     * Objective: Create a new level, with new sentinels in the SkipList
     * Notes:
     *  - Called by the Insert method
     *  */

    Node* p = new Node (NEG_INF);   //New negative sentinel
    Node* q = new Node (POS_INF);   //New positive sentinel

    //Connect the new sentinels to each other and to the old ones
    p->down     = head; head->up    = p;
    q->down     = tail; tail->up    = q;
    p->right    = q;    q->left     = p;

    //Now make p the head and q the tail of the SL
    head = p; tail = q;

    height++;   //Update the max height of the SL
}   //End of createNewLevel method

void SkipList::Insert(char *word)
{
    /* Insert public method, parameter(s): char array <word>
     * Objective: Insert a node with the given <word>, if the word is in the SL already then increase the count of that
     *            node
     * */

    Node* findNode = find(word);             //Use the find method

    if (strcmp(findNode->data, word) == 0)      //If the word is already in the list
    {
        totKeyCompare++;                        //Add +1 to the key comparison for using strcmp
        findNode->count++;                      //Increase the count of the node
    }   //End of the word is already in the list
    else                                        //Else if the <word> was not in the SL
    {
        //We need to insert a new node using word
        Node* insertNode = new Node(word);  //Create a new node to insert in the SL
        //Now we insert the new node in front of the findNode
        insertNode->left        = findNode;         //Set the insertNode's left to the findNode
        insertNode->right       = findNode->right;  //Set the insertNode's right to the findNode's right
        findNode->right->left   = insertNode;
        findNode->right         = insertNode;       //Set the findNode's to the insertNode

        //Now we have to randomize if we are going to insert this new node <insertNode> into another lane/level
        int currentLvl = 1;                 //Keep track of the current level of the SkipList, starting from the slow-lane

        while (rand() & 1)                  //While we keep getting a coin flipped as heads
        {
            //We are here if we randomly number that counts as 'head' in a coin, so insert the node in an upper level
            if (currentLvl >= height)       //If we reached the top level of the SkipList
                createNewLevel();           //Then we create a new top level in the SL

            //Now we need to traverse back until we find a node that has a node above it
            while (findNode->up == nullptr)
                findNode = findNode->left;  //Then move left
            //Here the findNode should have an up pointer or we are at negative sentinel of the lane

            findNode  = findNode->up;    //Move to to the upper lane

            Node* newInsertNode = new Node(word);    //Create new insert node to insert in upper lane

            //Link the newInsertNode in the upper lane
            newInsertNode->left = findNode;
            newInsertNode->right = findNode->right;
            newInsertNode->down = insertNode;

            //Adjust the nodes in the upper lane to point to the newInsertNode
            findNode->right->left = newInsertNode;
            findNode->right = newInsertNode;
            insertNode->up = newInsertNode;

            insertNode = newInsertNode;     //Move the insertNode to the new insert node in the upper lane
            currentLvl ++;                  //Increase the current level by 1
        }   //End of while-loop
        //We get here if we flipped tails
    }   //End of else, if the <word> is not in the SL
}   //End of Insert method

void SkipList::print()
{
    /* print private method, parameter(s): None
     * Objective: Print value and count in all the lanes of the SkipList
     * */

    std::cout<<"\n*****Skip List*****"<<"\n";
    std::cout << "Total lanes: " << height << std::endl;
    int currentLevel = height;  //Save current height/lane we are in

    Node* currentHead = head;   //Start from the head
    while (currentHead != nullptr)
    {
        std::cout << "\tLevel: " << currentLevel << std::endl;  //Print level we are in
        printLevel(currentHead);
        currentHead = currentHead->down;
        currentLevel--; //Decrease the level
    }   //End of while-loop
}   //End of print method

void SkipList::printLevel(SkipList::Node *headlvl)
{
    Node* currentNode = headlvl->right;

    while (strcmp(currentNode->data, POS_INF) != 0)  //If the next node is not a sentinel
    {
        //Output current Node data
        std::cout << currentNode->data << ": " << currentNode->count << std::endl;
        currentNode = currentNode->right;   //Move to the next node
    }   //End of while-loop

}