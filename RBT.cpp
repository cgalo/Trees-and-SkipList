/*
 * Created by Carlos Galo on 3/30/20.
 * */


#include "RBT.h"

RBT::RBT()
{
    this->root              = nullptr;  //Set the root to nil
    this->totKeyComparison  = 0;        //Keep track of the total key comparisons done in the Insert() method
    this->totWords          = 0;        //Total nodes and count data in the tree
    this->distinctWords     = 0;        //Total of unique/distinct tree nodes
    this->recolorTot        = 0;        //Keep track of every time we recolor a node
    this->leftRotTot        = 0;        //Keep track of every time a left rotation is perform
    this->rightRotTot       = 0;        //Keep track of every time a right rotation is perform
    this->totCaseOne        = 0;        //Keep track of every time a Case 1 is performed
    this->totCaseTwo        = 0;        //Keep track of every time a Case 2 is performed
    this->totCaseThree      = 0;        //Keep track of every time a Case 3 is performed
}   //End of constructor

RBT::~RBT()
{
    totKeyComparison    = 0;            //Keep track of the total key comparisons done in the Insert() method
    totWords            = 0;            //Total nodes and count data in the tree
    distinctWords       = 0;            //Total of unique/distinct tree nodes
    leftRotTot          = 0;            //Keep track of every time a left rotation is perform
    rightRotTot         = 0;            //Keep track of every time a right rotation is perform
    totCaseOne          = 0;            //Keep track of every time a Case 1 is performed
    totCaseTwo          = 0;            //Keep track of every time a Case 2 is performed
    totCaseThree        = 0;            //Keep track of every time a Case 3 is performed
    //Destructor for RBT class, for garbage collection (GC) purposes
    if (root != nullptr)        //If the tree is not empty
    {
        treeDestructor(root);   //Recurse through the tree to delete all nodes
        root = nullptr;         //Set the root back to nil
    }   //End of if the tree is not empty

}   //End of destructor

void RBT::treeDestructor(RBT::Node *currentNode)
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
}   //End of treeDestructor function

RBT::Node* RBT::search(char *word)
{
    ////ONLY call this function after checking if the root is not null
    /* search private method, parameter(s): string <word>
     * Objective: Return node with the given word
     * Cases:
     *  1. Traverse the tree, we found the word, return the node that has that word
     *  2. Word was not found in tree, return what would be the parent node of the word
     *  */

    Node* currentNode = root;                           //Start from the root of the tree and we work ourselves down
    Node* parentNode  = nullptr;                        //This will be returned if we do not search the word in the tree
    while (currentNode != nullptr)                      //Traverse until we hit a leaf in the tree
    {
        totKeyComparison++;                             //Increase the count of total key comparisons done
        if (strcmp(currentNode->data, word) == 0)       //If we found a node w/ the word we are looking for
            return currentNode;                         //Return the node that contains the word we are looking for
        else    //Else the node does not contain the word, we traverse either left or right
        {
            parentNode = currentNode;                   //Save the parentNode before moving the currentNode reference
            totKeyComparison++;                         //Update the total of key comparison done
            if (strcmp(currentNode->data, word) > 0)    //If the word is lesser than the currentNode's data
                currentNode = currentNode->LCH;         //We move to the left child
            else                                        //Else the word is greater than the currentNode's data
                currentNode = currentNode->RCH;         //We move to the right child
        }   //End of else, if the word was not in the currentNode
    }   //End of while-loop, we finished traversing the tree
    //We get here if we did not search the Node containing the word, we return the parentNode
    return parentNode;  //Return parentNode
}   //End of search function, returns struct Node

void RBT::Insert(char *word)
{
    /* Insert private function, parameter(s): string <word>
     * Objective: Insert node with given word in the tree, if the node exists then add +1 to the count of that node
     * Cases:
     *  1. Node w/ given word exists, we add +1 to the count and return it
     *  2. Node does not exist in the tree, insert the node in the tree
     *  */

    if (root == nullptr)                            //If the tree is empty, we insert node as root
    {
        root = new Node(word);                      //Create a new node with given char array and set it as root of the tree
        root->color = black;                        //The root always has to be black
    }   //End of if the tree is empty
    else                //Else the tree is not empty
    {
        Node* findNode = search(word);              //Call and save the result of the search method
        totKeyComparison++;                         //Increase the count of total key comparisons
        if (strcmp(findNode->data, word) == 0)      //If the findNode contains the word we are looking for, update count
            findNode->count++;                      //Update the count by adding 1
        else                                        //Else the findNode is the parentNode we have to insert new child
        {
            Node* parentNode = findNode;            //Save the findNode as parentNode
            Node* insertNode = new Node(word);      //Create a new node to insert as a child, with color red
            totKeyComparison++;                     //Add +1 to tot comparison for the following array comparison
            if (strcmp(parentNode->data, word) > 0) //If the parentNode's data is greater than than the word
                parentNode->LCH = insertNode;       //Insert the new node as left child
            else                                    //Else the word is greater than parentNode's data, insert right
                parentNode->RCH = insertNode;       //Insert new node as right child;
            insertNode->parent = parentNode;        //Set the parentNode as insertNode's parent
            InsertFixUp(insertNode);                //Call the InsertFixUp method by passing the insertNode
        }   //End of else, if the findNode is the parentNode
    }   //End of else, if the the tree is not empty
}   //End of Insert method

void RBT::InsertFixUp(RBT::Node *z)
{
    /* InsertFixUp private method, parameter(s): Node pointer
     * Objective: Check and fix the rules for the RBTree after inserting the given node
     * Notes:
     * - Helper method called after inserting a node in the Insert method
     * */

    while (z->parent != nullptr && z->parent->color == red)
    {
        if (z->parent->parent != nullptr && z->parent == z->parent->parent->LCH) //If z's parent is a LCH of its parent?
        {
            Node* y = z->parent->parent->RCH;       //Let y be z's (right) uncle
            if (y != nullptr && y->color == red)    //Case 1, recolor only
            {
                z->parent->color = black;           //Set z's parent to black
                y->color = black;                   //Set y to black
                z->parent->parent->color = red;     //Set z's grandparent to red
                z = z->parent->parent;              //Move z pointer up to its grandparent
                recolorTot += 3;                    //Add +3 to recoloring for this case
                totCaseOne++;                       //Add +1 to case 1 completed
            }   //End of Case 1
            else
            {
                //Case 2
                if (z == z->parent->RCH)            //Z is a RCH to its parent
                {
                    z = z->parent;                  //Move z to its parent node
                    LeftRotate(z);                  //Perform a right-rotation
                    totCaseTwo++;                   //Add +1 to case 2 completed
                }   //End of case 2
                //Case 3
                z->parent->color = black;           //Change z's parent color to black
                z->parent->parent->color = red;     //Change z's grandparent color to red
                RightRotate(z->parent->parent);     //Perform a Right-Rotation
                recolorTot += 2;                    //Add +2 to recoloring for case 3
                totCaseThree++;                     //Add +1 to case 1 completed
            }   //End of else-if z is a RCH to its parent
        }   //End of if z's parent
        else    //Else the z's parent is a RCH of its grandparent
        {
            Node* y = z->parent->parent->LCH;       //Let y be z's (left) uncle
            if (y != nullptr && y->color == red)    //Case 1, recolor only
            {
                z->parent->color = black;           //Set z's parent to black
                y->color = black;                   //Set y to black
                z->parent->parent->color = red;     //Set z's grandparent to red
                z = z->parent->parent;              //Move z pointer up to its grandparent
                recolorTot += 2;                    //Add +2 to recoloring for case 1
                totCaseOne++;                       //Add +1 to case 1 completed
            }   //End of case 1
            else
            {
                //Case 2
                if (z == z->parent->LCH)            //Z is a LCH to its parent
                {
                    z = z->parent;                  //Move z to its parent node
                    RightRotate(z);                 //Perform a Right-Rotation
                    totCaseTwo++;                   //Add +1 to case 2 completed
                }   //End of case 2, if z is a LCH to its parent
                //Case 3
                z->parent->color = black;           //Change z's parent color to black
                z->parent->parent->color = red;     //Change z's grandparent color to red
                LeftRotate(z->parent->parent);      //Perform a Left-Rotation
                recolorTot += 2;                    //Add +2 to recoloring for case 3
                totCaseThree++;                     //Add +1 to case 1 completed
            }   //End of else, if Case 2 & 3
        }   //End of else, z's parent is a RCH of its grandparent
    }   //End of while-loop
    root->color = black;                            //Make sure the root is black
    recolorTot++;                                   //Add +1 for recoloring the root node
}   //End of InsertFixUp method

void RBT::LeftRotate(RBT::Node *X)
{
    /* LeftRotate private method, parameter(s): struct Node
     * Objective: Perform a Left-Rotation on the RBTree to maintain the tree 'balanced'
     * Notes:
     *  - Called in the InsertFixUp method
     *  - This assumes root's parent is nil & X' RCH != nil
     * */

    Node* Y = X->RCH;                   //Y is the X's right (non-nil) child
    X->RCH  = Y->LCH;                   //Move y's left subtree into
    if (Y->LCH != nullptr)              //X's right subtree
        Y->LCH->parent = X;
    Y->parent = X->parent;              //Link x's parent to Y
    if (X->parent == nullptr)           //If x has no parent, x was the root
        root = Y;                       //Make Y the new root
    else if (X == X->parent->LCH)       //Otherwise X has a parent
        X->parent->LCH = Y;             //Spot X used to occupy now
    else X->parent->RCH = Y;            //gets taken by Y
    Y->LCH = X;                         //Put X on Y's left, which...
    X->parent = Y;                      //....makes X's parent be Y
    leftRotTot++;                       //Update total left rotations performed
}   //End of LeftRotate method

void RBT::RightRotate(RBT::Node *X)
{
    /* RightRotate private method, parameter(s): struct Node
     * Objective: Perform a Right-Rotation on the RBTree to maintain the tree 'balanced'
     * Notes:
     *  - The opposite of the LeftRotate method
     *  - Called in the InsertFixUp method
     *  - This assumes root's parent is nil & X' RCH != nil
     * */

    Node* Y = X->LCH;
    X->LCH = Y->RCH;

    if (X->LCH != nullptr)
        X->LCH->parent = X;

    Y->parent = X->parent;

    if (X->parent == nullptr)
        root = Y;

    else if (X == X->parent->LCH)
        X->parent->LCH = Y;
    else
        X->parent->RCH = Y;

    Y->RCH = X;
    X->parent = Y;

    rightRotTot++;                      //Update total right rotations performed

}   //End of RightRotate method

void RBT::displayStatistics()
{

    /* displayStatistics public method, parameter(s): None
     * Objective: Print the final results of the tree
     * Metrics:
     *  - Distinct Words
     *  - Total Words
     *  - Height
     *  - Key Comparisons
     *  - Reference Changes
     *  - Recoloring
     *  - Left Rotations
     *  - Right Rotations
     *  - Case 1 Problems
     *  - Case 2 Problems
     *  - Case 3 Problems
     *  - Elapsed Time
     *  */

    int height = calcHeight(root);  //Recurse the tree to get the height of it
    inOrderTraversal(root);         //This helps to calculate total words and distinct words

    //Display results
    std::cout << "Distinct Words: "     << distinctWords    << std::endl;   //Distinct Words
    std::cout << "Total Words: "        << totWords         << std::endl;   //Total words
    std::cout << "Height: "             << height           << std::endl;   //Height of the tree
    std::cout << "Key Comparisons: "    << totKeyComparison << std::endl;   //Total key comparisons done
    std::cout << "Reference Changes: "  << std::endl;
    std::cout << "Recoloring: "         << recolorTot       << std::endl;   //Total recoloring done
    std::cout << "Left Rotations: "     << leftRotTot       << std::endl;   //Left rotations completed
    std::cout << "Right Rotations: "    << rightRotTot      << std::endl;   //Right rotations completed
    std::cout << "Case 1 Problems: "    << totCaseOne       << std::endl;   //Total case 1 completed
    std::cout << "Case 2 Problems: "    << totCaseTwo       << std::endl;   //Total case 2 completed
    std::cout << "Case 3 Problems: "    << totCaseThree     << std::endl;   //Total case 3 completed
    std::cout << "Elapsed Time: "       << std::endl;   //Elapsed Time
}   //End of print method

void RBT::inOrderTraversal(RBT::Node *node)
{
    /* inOrderTraversal private method, parameter(s): Node Pointer
     * Objective: Recurse through the tree and print nodes in-order
     * It is called by the printTree() public method
     */

    if (node == nullptr)            //If we reach a leaf
        return;                     //Exit
    inOrderTraversal(node->LCH);    //Traverse through the left side
    totWords += node->count;        //Add the count of the node to totWords variable
    distinctWords++;                //Increase distinctWords for every node in the tree
    inOrderTraversal(node->RCH);    //Traverse through the right side
}   //End of inOrderTraversal method


int RBT::calcHeight(RBT::Node *node)
{
    /* calcHeight private recursive method, parameter(s): Node pointer
     * Objective: Recurse through the tree to calculate the height of the tree
     * */

    if (node == nullptr)   return 0;        //If we hit a leaf exit

    int leftH   = calcHeight(node->LCH);    //Recurse and calculate the left height of the tree
    int rightH  = calcHeight(node->RCH);    //Recurse and calculate the right side of the tree

    if (leftH > rightH) return leftH + 1;   //Add to the left height
    else                return rightH + 1;  //Add to the right height
}   //End of calcHeight