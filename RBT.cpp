/*
 * Created by Carlos Galo on 3/30/20.
 * */


#include "RBT.h"

RBT::RBT()
{
    this->root = nullptr;           //Set the root to nil
    this->totKeyComparison = 0;    //Initialize the total key comparisons
}   //End of constructor

RBT::~RBT()
{
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

    Node* currentNode = root;       //Start from the root of the tree and we work ourselves down
    Node* parentNode  = nullptr;    //This will be returned if we do not search the word in the tree
    while (currentNode != nullptr)  //Traverse until we hit a leaf in the tree
    {
        if (strcmp(currentNode->data, word) == 0)
        {
            totKeyComparison++; //Add +1 to the total key comparisons for comparing the values in both arrays
            return currentNode; //Return the node that contains the word we are looking for
        }   //End of if the current Node contains the word we are looking for
        else    //Else the node does not contain the word, we traverse either left or right
        {
            parentNode = currentNode;   //Save the parentNode before moving the currentNode reference
            totKeyComparison++;         //Update the total of key comparison done
            if (strcmp(currentNode->data, word) > 0)    //If the word is lesser than the currentNode's data
                currentNode = currentNode->LCH;   //We move to the left child
            else                                        //Else the word is greater than the currentNode's data
            {
                currentNode = currentNode->RCH;  //We move to the right child
            }   //End of else, if the word is greater than the currentNode's data
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

    if (root == nullptr)   //If the tree is empty, we insert node as root
    {
        root = new Node(word);      //Create a new node with given char array and set it as root of the tree
        root->color = black;        //The root always has to be black
    }   //End of if the tree is empty
    else                //Else the tree is not empty
    {
        Node* findNode = search(word);          //Call and save the result of the search method
        if (strcmp(findNode->data, word) == 0)  //If the findNode contains the word we are looking for, update count
        {
            findNode->count++;  //Update the count by adding 1
            totKeyComparison++; //Add +1 to the total key comparisons for comparing the values in both arrays
        }   //End of if the findNode contains the word
        else                            //Else the findNode is the parentNode we have to insert new child
        {
            Node* parentNode = findNode;            //Save the findNode as parentNode
            Node* insertNode = new Node(word);      //Create a new node to insert as a child, with color red
            totKeyComparison++;                     //Add +1 to tot comparison for the following array comparison
            if (strcmp(parentNode->data, word) > 0) //If the parentNode's data is greater than than the word
            {
                parentNode->LCH = insertNode; //Insert the new node as left child
            }   //End of if the word being inserted is less than the parentNode, insert left
            else                        //Else the word is greater than parentNode's data, insert right
            {
                parentNode->RCH = insertNode;//Insert new node as right child;
            }   //Else if the word is greater than parentNode, insert right
            insertNode->parent = parentNode;        //Set the parentNode as insertNode's parent
            InsertFixUp(insertNode);
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
       if (z->parent == z->parent->parent->LCH)
       {
           Node* y = z->parent->parent->RCH;    // let y be z's (right) uncle
           if (y != nullptr && y->color == red)
           {
               z->parent->color = black;        // Case 1 (re-color only)
               y->color = black; 		// Case 1
               z->parent->parent->color = red; 		// Case 1
               z = z->parent->parent;			// Case 1
           }    //End of if
           else if (z == z->parent->RCH)
           {
               z = z->parent;
               LeftRotate(z);
           }    //End of else-if

           z->parent->color = black;
           if (z->parent->parent != nullptr)
           {
               z->parent->parent->color = red;
               RightRotate(z->parent->parent);
           }
       }
       else
       {
           Node* parentNode = z->parent;                //Parent node
           Node* grandpaNode = parentNode->parent;      //Grandparent node
           Node* uncleNode = z->parent->parent->LCH;    //Uncle node
           //Case 1: Uncle of Z is also red, only recolor
           if (uncleNode != nullptr && uncleNode->color == red)
           {
               grandpaNode->color = red;
               parentNode->color = black;
               uncleNode->color = black;
               z = grandpaNode;
           }    //End of if the uncle is red
           else
           {    //Case 2: Z is a LCH, do a Right-Rotation
               if (z == parentNode->LCH)    //If z is a left-children to its parent
               {
                   RightRotate(parentNode); //Perform a right-rotation
                   z = parentNode;
                   parentNode = z->parent;
               }    //End of if z is a LCH
               //Case 3: z is LCH, perform a left-rotation
               LeftRotate(grandpaNode);
               //Swap colors between parent and grandpa node
               int temp = parentNode->color;
               parentNode->color = grandpaNode->color;
               grandpaNode->color = temp;
               //End of swap
               z = parentNode;
           }    //End of else
       }
   }    //End of while-loop
   root->color = black;

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
}   //End of LeftRotate method

void RBT::RightRotate(RBT::Node *pt)
{
    /* RightRotate private method, parameter(s): struct Node
     * Objective: Perform a Right-Rotation on the RBTree to maintain the tree 'balanced'
     * Notes:
     *  - Called in the InsertFixUp method
     *  - This assumes root's parent is nil & X' RCH != nil
     * */

    ////Review this code by comparing to the left rotation
    Node* pt_left = pt->LCH;
    pt->LCH = pt_left->RCH;

    if (pt->LCH != nullptr)
        pt->LCH->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;

    else if (pt == pt->parent->LCH)
        pt->parent->LCH = pt_left;
    else
        pt->parent->RCH = pt_left;

    pt_left->RCH = pt;
    pt->parent = pt_left;

}   //End of RightRotate method

void RBT::print()
{
    if (root == nullptr)    //If the tree is empty
        std::cout << "Tree is empty" << std::endl;
    else                    //Else the tree is not empty
        inOrderTraversal(root); //Traverse the tree in-order traversal
}   //End of print method

void RBT::inOrderTraversal(RBT::Node *node)
{
    /* inOrderTraversal private method, parameter(s): Node Pointer
     * Objective: Recurse through the tree and print nodes in-order
     * It is called by the printTree() public method
     */

    if (node == nullptr)    //If we reach a leaf
        return;                 //Exit
    inOrderTraversal(node->LCH);   //Traverse through the left side
    std::cout << node->data << ": " << node->count << std::endl;
    inOrderTraversal(node->RCH);  //Traverse through the right side
}   //End of inOrderTraversal method