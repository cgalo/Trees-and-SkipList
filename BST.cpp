//
// Created by Carlos Galo on 3/23/20.
//

#include "BST.h"

BST::BST()
{
    /* BST public constructor, parameter(s): none
     * */

    this->root              = nullptr;  //Set the root of the tree to initialize as NULL
    this->totKeyComparison  = 0;        //Set the total key comparison of the tree to 0
    this->totWords          = 0;        //Set the total number of items in the tree to 0
    this->distinctWords     = 0;        //Set the total distinct nodes in the tree to 0
}   //End of constructor

BST::~BST()
{
    /* ~BST public destructor, parameter(s): None
     * */

    totKeyComparison    = 0;       //Set the total key comparison of the tree to 0
    totWords            = 0;       //Set the total number of items in the tree to 0
    distinctWords       = 0;       //Set the total distinct nodes in the tree to 0
    if (root != nullptr)        //If the tree is not empty
    {
        treeDestructor(root);   //Traverse and destroy
        this->root = nullptr;   //Set the root pointer to NULL
    }   //End of if tree is not empty
}   //End of destructor function

void BST::treeDestructor(BST::Node *currentNode)
{
    /* treeDestructor private method, parameter(s): node pointer
     * Objective: recurse through the tree and delete all nodes in the tree
     * Warning: ONLY call this method from the destructor -> ~BST()
     */

    if (currentNode != nullptr)
    {
        treeDestructor(currentNode->leftChild);
        treeDestructor(currentNode->rightChild);
        delete currentNode;
    }   //End of if the currentNode is not NULL
}   //End of treeDestructor function

BST::Node* BST::search(char *word)
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
        totKeyComparison++;                             //Add +1 to total key comparisons completed
        if (strcmp(currentNode->data, word) == 0)       //If the current node has the word we are looking for
            return currentNode;                         //Return the node that contains the word we are looking for
        else                                            //Else the node does not contain the word
        {
            parentNode = currentNode;                   //Save the parentNode before moving the currentNode reference
            totKeyComparison++;                         //Update the total of key comparison done
            if (strcmp(currentNode->data, word) > 0)    //If the word is lesser than the currentNode's data
                currentNode = currentNode->leftChild;   //We move to the left child
            else                                        //Else the word is greater than the currentNode's data
                currentNode = currentNode->rightChild;  //We move to the right child
        }   //End of else, if the word was not in the currentNode
    }   //End of while-loop, we finished traversing the tree
    //We get here if we did not search the Node containing the word, we return the parentNode
    return parentNode;  //Return parentNode
}   //End of search function, returns struct Node

void BST::Insert(char *word)
{
    /* Insert private function, parameter(s): string <word>
     * Objective: Insert node with given word in the tree, if the node exists then add +1 to the count of that node
     * Cases:
     *  1. Node w/ given word exists, we add +1 to the count and return it
     *  2. Node does not exist in the tree, insert the node in the tree
     *  */

    if (root == nullptr)                            //If the tree is empty, we insert node as root
        root = new Node(word);                      //Insert a new node, w/ the given word as data, as the new root
    else                //Else the tree is not empty
    {
        Node* findNode = search(word);              //Call and save the result of the search method
        totKeyComparison++;                         //Increase total key comparison variable
        if (strcmp(findNode->data, word) == 0)      //If the findNode contains the word we are looking for, update count
            findNode->count++;                      //Update the count by adding 1
        else                                        //Else the findNode is the parentNode we have to insert new child
        {
            Node* parentNode = findNode;            //Save the findNode as parentNode
            Node* insertNode = new Node(word);      //Create a new node to insert as a child
            totKeyComparison++;                     //Add +1 to tot comparison for the following array comparison
            if (strcmp(parentNode->data, word) > 0) //If the parentNode's data is greater than than the word
                parentNode->leftChild = insertNode; //Insert the new node as left child
            else                                    //Else the word is greater than parentNode's data, insert right
                parentNode->rightChild = insertNode;//Insert new node as right child;
        }   //End of else, if the findNode is the parentNode
    }   //End of else, if the the tree is not empty
}   //End of Insert method

int BST::calcHeight(BST::Node *node)
{
    /* Height private recursive method, parameter(s): Node pointer
     * Objective: Recurse through the tree to calculate the height of it
     * */

    if (node == nullptr)   return 0;                //If we hit a leaf exit

    int leftH = calcHeight(node->leftChild);        //Recurse and calculate the left height of the tree
    int rightH = calcHeight(node->rightChild);      //Recurse and calculate the right side of the tree

    if (leftH > rightH) return leftH + 1;           //Add to the left height
    else                return rightH + 1;          //Add to the right height
}   //End of height method

void BST::inOrderTraversal(BST::Node *currentNode)
{
    /* inOrderTraversal private method, parameter(s): Node Pointer
     * Objective: Recurse through the tree and print nodes in-order
     * It is called by the printTree() public method
     */

    if (currentNode == nullptr)                 //If we reach a leaf
        return;                                 //Exit
    inOrderTraversal(currentNode->leftChild);       //Traverse through the left side
    totWords += currentNode->count;             //Add the count of the node to totItems
    distinctWords++;                            //Add +1 to total nodes in the tree
    inOrderTraversal(currentNode->rightChild);      //Traverse through the right side
}   //End of inOrderPrint method


void BST::displayStatistics()
{

    /* displayStatistics public method, parameter(s): None
     * Objective: Print the final results of the tree
     * Metrics:
     *  - Distinct Words
     *  - Total Words
     *  - Height
     *  - Reference Changes
     *  - Key Comparisons
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
    std::cout << "Elapsed Time: "       << std::endl;   //Elapsed Time
}   //End of print method