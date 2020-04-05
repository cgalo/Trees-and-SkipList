//
// Created by Carlos Galo on 3/25/20.
//


#include "SkipList.h"       //Connect to the header file of the SkipList(SL)


#define NEG_INF "negInf"    //Used to create negative sentinels as node
#define POS_INF "posInf"    //Used to create positive sentinels as node


SkipList::SkipList()
{
    //Basic constructor for the SkipList(SL) with no parameter(s)

    //Head & Tail node
    this->head              = new Node(NEG_INF);    //Initialize the head as a negative sentinel
    this->tail              = new Node(POS_INF);    //Initialize the tail as a positive sentinel
    this->head->right       = tail;                 //Connect the head to the tail
    this->tail->left        = head;                 //Connect the tail to the head

    //Variables
    this->height            = 1;                    //We start the height of the SL of 1, for the slow-lane
    this->totKeyComparison  = 0;                    //Total key-comparisons done
    this->distinctWords     = 0;                    //Total nodes in the slow-lane
    this->totWords          = 0;                    //Total of the all the node's frequencies in the SL slow lane
    this->refChanges        = 0;                    //Total reference changes

    //For randomizing when to move to an upper lane
    this->coin              = std::mt19937(time(NULL)); //Seed PRNG
}   //End of constructor


SkipList::~SkipList()
{
    //Destructor for the SL object, for garbage collection (GC)

    Node* currHead = head;                      //We start from the head of SL's fastest lane
    for (int lvl = height; lvl == 0; lvl--)     //Traverse each lane in the SL and delete all nodes, start from fast-lane
    {
        Node* currentNode   = currHead;         //Save the current head of this lane
        currHead            = head->down;       //Remember the head of the lower lane before deleting then current lane
        while (currentNode != nullptr)          //Traverse until we have gone through all nodes in this lane
        {
            Node* deleteNode = currentNode;     //Remember the node we need to delete
            currentNode = currentNode->right;   //Move the currentNode pointer to the next node in the lane
            delete deleteNode;                  //Delete the current node and move to the next node
        }   //End of while-loop
    }   //End of for-loop
    //We get here after deleting all nodes, in all of the lanes, of the SkipList
    this->head              = nullptr;          //Reset the head node to nil
    this->tail              = nullptr;          //Reset the tail node to nil
    this->height            = 0;                //Reset the height back to 0
    this->totKeyComparison  = 0;                //Reset total key-comparisons done
    this->distinctWords     = 0;                //Reset total nodes in the slow-lane
    this->totWords          = 0;                //Reset total of the all the node's frequencies in the SL slow lane
    this->refChanges        = 0;                //Reset total reference changes
}   //End of destructor


SkipList::Node* SkipList::find(char *word)
{
    /* find private method, parameter(s): char array <word>
     * Objective: Returns a slow-lane pointer to either the node containing data <word> or the slow-lane node preceding
     *      where <word> would be in the list
     * */

    Node* currentNode = head;   //Get the pointer of the current head
    while (true)                //Keep looping until we find the node w/ the word or the location where we'll insert it
    {
        //Move current node until currentNode's right neighbor node contains a key value > given parameter(word)
        totKeyComparison += 2;  //Add +2 before the while-loop starts
        while ((strcmp(currentNode->right->data, POS_INF) != 0) && strcmp(currentNode->right->data, word) <= 0)
        {
            currentNode = currentNode->right;   //Move to the next node in the lane
            totKeyComparison += 2;              //Add +2 to key comparison as we had to check twice to get here

        }   //End of while-loop
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

    Node* findNode = find(word);                    //Use the find method
    totKeyComparison++;                             //Add +1 to the key comparison for using strcmp
    if (strcmp(findNode->data, word) == 0)          //If the word is already in the list
    {
        findNode->count++;                          //Increase the count of the node
        totWords++;                                 //Update for the total words
    }   //End of the word is already in the list
    else                                            //Else if the <word> was not in the SL
    {
        //We need to insert a new node using word
        Node* insertNode = new Node(word);          //Create a new node to insert in the SL
        totWords++;                                 //Update for the new node with frequency of 1
        distinctWords++;                            //Update total nodes in the slow lane of the SL

        //Now we insert the new node in front of the findNode
        insertNode->left        = findNode;         //Set the insertNode's left to the findNode
        insertNode->right       = findNode->right;  //Set the insertNode's right to the findNode's right
        findNode->right->left   = insertNode;
        findNode->right         = insertNode;       //Set the findNode's to the insertNode
        refChanges++;

        //Now we have to randomize if we are going to insert this new node <insertNode> into another lane/level
        int currentLvl = 1;                         //Track the current level, start from the slow-lane
        while (coin() & 1)                          //While we keep getting a coin flipped as heads
        {
            //We are here if we randomly number that counts as 'head' in a coin, so insert the node in an upper level
            if (currentLvl >= height)               //If we reached the top level of the SkipList
                createNewLevel();                   //Then we create a new top level in the SL
            //Now we need to traverse back until we find a node that has a node above it
            while (findNode->up == nullptr)
                findNode = findNode->left;          //Then move left
            //Here the findNode should have an up pointer or we are at negative sentinel of the lane
            findNode  = findNode->up;               //Move to to the upper lane

            Node* newInsertNode = new Node(word);   //Create new insert node to insert in the upper lane

            //Link the newInsertNode in the upper lane
            newInsertNode->left = findNode;
            newInsertNode->right = findNode->right;
            newInsertNode->down = insertNode;

            //Adjust the nodes in the upper lane to point to the newInsertNode
            findNode->right->left = newInsertNode;
            findNode->right = newInsertNode;
            insertNode->up = newInsertNode;

            insertNode = newInsertNode;             //Move the insertNode to the new insert node in the upper lane
            currentLvl ++;                          //Increase the current level by 1
        }   //End of while-loop
        //We get here if we flipped tails
    }   //End of else, if the <word> is not in the SL
}   //End of Insert method

void SkipList::printLanes()
{
     /* printLanes public method, parameter(s): None
      * Objective: Output total nodes in each lane of the SkipList, starting from the fastest to the slowest lane
      * */

    Node* currHead  = head;         //Start from the fast-lane
    int lvl         = 0;
    while (currHead != nullptr)     //Traverse until we've been through all lanes in the SL
    {
        lvl++;                      //Update the current level
        std::cout << "Nodes in Lane # " << lvl << ": " << nodesInLane(currHead) << std::endl;   //Output lane totNodes
        currHead = currHead->down;  //Move to the slower-lane
    }   //End of while-loop

}   //End of print method

void SkipList::displayStatistics()
{

    /* displayStatistics public method, parameter(s): None
     * Objective: Print the final results of the SkipList
     * Metrics:
     *  - Slow Lane Nodes
     *  - Fast Lane Nodes
     *  - Internal Height
     *  - Measured Height
     *  - Distinct Words
     *  - Total Words
     *  - Key Comparisons
     *  - Reference Changes
     *  - Total Nodes in each lane
     *  - Elapsed Time
     *  */

    //Display results
    std::cout << "\nSkipList Results"   << std::endl;
    std::cout << "Slow Lane nodes: "    << distinctWords    << std::endl;   //Total nodes in the slow-lane
    std::cout << "Fast Lane nodes: "    << nodesInLane(head)<< std::endl;   //Total nodes in the fast lane
    std::cout << "Internal Height: "    << height           << std::endl;   //Internal height
    std::cout << "Measured Height: "    << calcHeight()     << std::endl;   //Calculated height
    std::cout << "Distinct Words: "     << distinctWords    << std::endl;   //Distinct Words
    std::cout << "Total Words: "        << totWords         << std::endl;   //Total words
    std::cout << "Key Comparisons: "    << totKeyComparison << std::endl;   //Total key comparisons done
    std::cout << "Reference Changes: "  << refChanges       << std::endl;
    printLanes();                                                           //Print lane & nodes per lane
}   //End of print method

int SkipList::calcHeight()
{
    /* calcHeight private method, parameter(s): None
     * Objective: Calculate how many levels are currently in the SL
     * */

    int totLanes = 0;                       //We know there is at least one lane, we start from the current fastest lane
    Node* currentHead = head;               //Start from the current head of the SL
    while (currentHead != nullptr)          //Traverse until there are no more lanes
    {
        totLanes++;                         //Increase count of total lanes
        currentHead = currentHead->down;    //Move to the slower lane
    }   //End of while-loop
    //We get here after traversing all the lanes in the SL
    return totLanes;                        //Return the total lanes in the SL
}   //End of calcHeight method

int SkipList::nodesInLane(SkipList::Node *lvlHead)
{
    /* nodesInLane private method, parameter(s): Node <lvlHead> -> Should be the negative sentinel of the lvl
     * Objective: Traverse the current level and return how many, non-sentinel, nodes are in the lane
     * */

    int totNodes = 0;                       //This will be the variable we'll return to keep track of tot nodes in the lane
    Node* currentNode = lvlHead;
    while (currentNode != nullptr)          //Traverse until the end of the lane
    {
        totNodes++;                         //Increase the totNodes variable by 1
        currentNode = currentNode->right;   //Move to the next node in the lane
    }   //End of while-loop
    //We get here after after traversing the entire lane
    return totNodes - 2;                    //Return totNodes minus the two sentinel nodes in the lane
}   //End of nodesInLane method

