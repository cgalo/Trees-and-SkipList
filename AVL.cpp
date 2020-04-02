//
// Created by Carlos Galo on 4/1/20.
//

#include "AVL.h"


AVL::AVL()
{
    //Constructor for AVL class

    root                = nullptr;      //Initiate the Node root pointer
    totKeyComparison    = 0;            //Keep track of the total key comparisons done in the Insert() method
    totWords            = 0;            //Total nodes and count data in the tree
    distinctWords       = 0;            //Total of unique/distinct tree nodes
    totBFChanges        = 0;            //Total BF changes completed in the Insert() method
    LLTot               = 0;            //Total Left-Left Rotations done in the Insert() method
    LRTot               = 0;            //Total Left-Right Rotations done in the Insert() method
    RRTot               = 0;            //Total Right-Right Rotations done in the Insert() method
    RLTot               = 0;            //Total Right-Left Rotations done in the Insert() method
    NoRotTot            = 0;            //Total of times Insert() method was called but no rotation was needed
}   //End of constructor

AVL::~AVL()
{
    //Destructor for the AVL class, for garbage collection (GC)

    totKeyComparison    = 0;            //Keep track of the total key comparisons done in the Insert() method
    totWords            = 0;            //Total nodes and count data in the tree
    distinctWords       = 0;            //Total of unique/distinct tree nodes
    totBFChanges        = 0;            //Total BF changes completed in the Insert() method
    LLTot               = 0;            //Total Left-Left Rotations done in the Insert() method
    LRTot               = 0;            //Total Left-Right Rotations done in the Insert() method
    RRTot               = 0;            //Total Right-Right Rotations done in the Insert() method
    RLTot               = 0;            //Total Right-Left Rotations done in the Insert() method
    NoRotTot            = 0;            //Total of times Insert() method was called but no rotation was needed
    if (root != nullptr)                //If the tree is not empty
    {
        treeDestructor(root);           //Destroy all nodes in the tree
        root                = nullptr;  //Set the root to nil
    }   //End of if the tree is not empty
}   //End of destructor

void AVL::treeDestructor(AVL::Node *currentNode)
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
}   //End of treeDestructor method

void AVL::Insert(char *X)
{
    Node *Y;            // The new node we insert (z in the previous code)
    Node *A, *B, *F;    // see below...
    Node *P, *Q;        // ...
    Node *C, *CL, *CR;  // ... for description
    int  d;             // displacement; Used to adjust BFs

    if (root == nullptr)   // Empty tree? Make a root node and exit!
    {
        NoRotTot++;         //No rotation was required
        root = new Node(X);    // make and fill a node
        return;          // This was the trivial case
    }

    /* Locate insertion point for X.
     * P scans through the tree until it falls off bottom (x previously)
     * Q is P’s parent (Q lags one step behind P) (y previously)
     * The new Node Y will be added as either the Left or Right child of Q
     * A is the last parent above Y with a BF of ±1 (before the insert)
     * F is A’s parent (F lags one step behind A)
     * */

    F = Q = nullptr; // F and Q lag, so they start NULL
    A = P = root; // A and P start at the root

    while (P != nullptr) // search tree for insertion point
    {
        totKeyComparison++; //Increase key comparison for report
        if (strcmp(X, P->data) == 0)
        {
            NoRotTot++; //No rotation was required
            P->count++; //Increase the count/frequency of the node
            return;     // ALREADY HERE!
        }
        if (P->BF !=0)   // remember the last place we saw
        {A=P; F=Q;}  // a non-zero BF (and its parent)
        Q = P;                               // Bring Q up to where P is
        P = (strcmp(X, P->data) < 0) ? P->LCH : P->RCH; // and then advance P
        totKeyComparison++; //Increase key comparison for report
    }
    /* At this point, P is NULL, but Q points at the last node where X
     * belongs (either as Q’s LCH or RCH, and Q points at an existing leaf)
     * */

    Y = new Node(X);   // Make a new node with it's data equal to the X parameter




    totKeyComparison++; //Increase key comparison for report
    if (strcmp(X, Q->data) < 0) Q->LCH = Y; // Will Y be Q's new left or right child?
    else           Q->RCH = Y;


     /* So far, except for keeping track of F and A, we have done exactly
      * the same “dumb” BST insert we’ve seen before.  Now, it’s time to do
      * the AVL-specific stuff: detect (and fix, if we have) an imbalance
      *
      * Adjust BFs from A to Q.
      * A was the LAST ancestor with a BF of ± 1, (or is still the root,
      * because we never FOUND a BF of ± 1), so ALL nodes BETWEEN A and Q
      * must have a BF of 0, and will, therefore, BECOME ± 1.
      *
      * If X is inserted in the LEFT subtree of A, then d = +1 (d = -1 means
      * we inserted X in the RIGHT subtree of A.
      * */

    totKeyComparison++; //Increase key comparison for report
    if (strcmp(X, A->data) > 0)
    {   // Which way is the displacement (d)
        B=P=A->RCH;
        d=-1;
    }
    else
    {
        B = P = A->LCH;
        d=+1;
    } // B is identified as A’s child

    while (P != Y)  // P is now one node below A.  Adjust from here to the
    {               // insertion point.  Don’t do anything to new node (Y)
        totKeyComparison++; //Increase key comparison for report
        if (strcmp(X, P->data) > 0)
        {
            P->BF =-1;
            P=P->RCH;
            totBFChanges++; //Increase for BF change
        } // adjust BF and move forward
        else
        {
            P->BF=+1;
            P=P->LCH;
            totBFChanges++; //Increase for BF change
        }
    }

    // Now we check the BF at A and see if we just pushed the tree INTO
    // BALANCE, into an “unacceptable IMBALANCE”, or if it is still
    // “BALANCED ENOUGH”.

    if (A->BF==0) // Tree WAS completely balanced before the insert.
    {             // The insert pushed it to slight (acceptable) imbalance
        A->BF=d;    // Set the BF to +/- 1 (displacement tells direction)
        NoRotTot++;     //No rotation was required
        totBFChanges++; //Increase for BF change
        return;     // This is close enough to live with, so exit now
    }

    if (A->BF== -d) // If the tree had a slight imbalance the OTHER way,
    {               // then did the insertion throw the tree INTO complete
        A->BF = 0;   // balance? If so, set the BF to zero and we’re done
        totBFChanges++; //Increase for BF change
        NoRotTot++;     //No rotation was required
        return;     //Exit Insert method
    }

    // If we took neither of the two returns just above, then the tree WAS
    // acceptably imbalanced, and is now UNACCEPTABLY IMBALANCED. Which
    // rotation type do we need to apply?

    if (d==1)  // this is a left imbalance (left subtree too tall).
    {           // Is it LL or LR?
        if (B->BF==1) // LL rotation
        {
            LLTot++;    //Increase count of rotations
            // Change the child pointers at A and B to reflect the rotation
            // Adjust the BFs at A & B
            // <<< LEFT FOR YOU TO WRITE (3-4 LOC) >>>
            // See Schematic (1)
            A->LCH  = B->RCH;   //Make A's RCH be B's RCH
            B->RCH  = A;        //B's new RCH is node A
            A->BF   = 0;        //Set A's BF to 0
            B->BF   = 0;        //Set B's BF to 0
            totBFChanges += 2; //Increase for two BF changes
        }   //End of LL rotation
        else  // LR Rotation: three cases (structurally the same; BFs vary)
        {
            /* Adjust the child pointers of nodes A, B, & C to reflect
             * the new post-rotation structure
             * */

            LRTot++;    //Increase count of rotations
            C  = B->RCH; // C is B's right child
            CL = C->LCH; // CL and CR are C's left and right children
            CR = C->RCH; // See Schematic (2) and (3)
            switch (C->BF)
            {
                /* Set the new BF’s at A and B, based on the BF at C.
                 * Note: There are 3 sub-cases
                 * */

                //Case A
                case 0:
                    C->LCH   = B;    //Make C's RCH node B
                    C->RCH   = A;    //Make C's LCH node A
                    A->BF    = 0;    //Set A's BF to 0
                    B->BF    = 0;    //Set B's BF to 0
                    totBFChanges += 2; //Increase for three BF change
                    break;              //End of case C's BF == 0

                //Case B
                case +1:
                    C->LCH  = B;    //Set C's LCH to B
                    C->RCH  = A;    //Set C's RCH to A
                    B->RCH  = CL;   //Set B's LCH to C's old LCH
                    A->LCH  = CR;   //Set A's LCH to C's old RCH
                    A->BF   = -1;   //Set A's BF to -1
                    B->BF   = 0;    //Set B's BF to 0
                    totBFChanges += 2; //Increase for two BF change
                    break;              //End of case C's BF  == +1

                case -1:
                    C->LCH   = B;    //Set C's LCH to B
                    C->RCH   = A;    //Set C's RCH to A
                    B->RCH   = CL;   //Set B's LCH to C's old LCH
                    A->LCH   = CR;   //Set A's LCH to C's old RCH
                    A->BF    = 0;    //Set A's BF to 0
                    B->BF    = 1;   //Set B's BF to +1
                    totBFChanges += 2; //Increase for two BF change
                    break;           //End of case C's BF  == -1
            }   //End of switch & Left-Right Rotation

            C->BF = 0; // Regardless, C is now balanced
            B = C;     // B is the root of the now-rebalanced subtree (recycle)
            totBFChanges++; //Increase for BF change
        } // end of else (LR Rotation)
    } // end of “if (d = +1)”
    else // d=-1.  This is a right imbalance
    {
        //RR or RL Rotations occurs here
        if (B->BF == -1) //RR rotation
        {
            RRTot++;    //Increase count of rotations
            A->RCH      = B->LCH;   //Change A's RCH to B's LCH
            B->LCH      = A;        //B's new LCH is A
            A->BF    = 0;        //Set A's BF to 0
            B->BF    = 0;        //Set B's BF to 0
            totBFChanges += 2; //Increase for two BF change
        }   //End of RR rotation
        else            //RL Rotation: three cases (structurally the same; BFs vary)
        {
            /* Adjust the child pointers of nodes A, B, & C to reflect
             * the new post-rotation structure
             * */
            RLTot++;    //Increase count of this rotation
            C  = B->LCH; // C is B's left child
            CL = C->LCH; // CL and CR are C's left and right children
            CR = C->RCH; // See Schematic (2) and (3)
            switch (C->BF)
            {
                /* Set the new BF’s at A and B, based on the BF at C.
                 * Note: There are 3 sub-cases
                 * <<< LEFT FOR YOU TO WRITE (3 LOC/CASE) >>>
                 */
                //Case A
                case 0:
                    C->LCH   = B;    //Make C's RCH node B
                    C->RCH   = A;    //Make C's LCH node A
                    A->BF    = 0;    //Set A's BF to 0
                    B->BF    = 0;    //Set B's BF to 0
                    totBFChanges += 2; //Increase for two BF change
                    break;           //End of case C's BF == 0

                //Case B
                case 1:
                    C->LCH  = A;   //Set C's LCH to B
                    C->RCH  = B;   //Set C's RCH to A
                    B->LCH  = CR;  //Set B's LCH to C's old LCH
                    A->RCH  = CL;  //Set A's LCH to C's old RCH
                    A->BF   = 0;   //Set A's BF to 0
                    B->BF   = 1;   //Set B's BF to 1
                    totBFChanges += 2; //Increase for two BF change
                    break;          //End of case C's BF  == 1

                //Case C
                case -1:
                    C->LCH   = A;   //Set C's LCH to B
                    C->RCH   = B;   //Set C's RCH to A
                    B->LCH   = CR;  //Set B's LCH to C's old LCH
                    A->RCH   = CL;  //Set A's LCH to C's old RCH
                    A->BF    = 1;   //Set A's BF to 0
                    B->BF    = 0;   //Set B's BF to +1
                    totBFChanges += 2; //Increase for two BF change
                    break;          //End of case C's BF  == -1
            }   //End of switch, and all cases for RL
            C->BF = 0; // Regardless, C is now balanced
            totBFChanges++; //Increase for BF change
            B = C;     // B is the root of the now-rebalanced subtree (recycle)
        }   //End of RL rotation
    }   //End of Right-Rotation (RR)
    // Finish up:
    // Regardless, the subtree rooted at B has been rebalanced, and needs to
    // be the new child of F.  The original subtree of F had root A.

    // did we rebalance the whole tree’s root?
    if (F == nullptr) {root=B; return;} // B is the tree’s new root - done

    // The root of what we rebalanced WAS A; now it’s B.  If the subtree we
    // rebalanced was LEFT of F, then B needs to be left of F;
    // if A was RIGHT of F, then B now needs to be right of F.
    //
    if (A == F->LCH) {F->LCH=B; return;}
    if (A == F->RCH) {F->RCH=B; return;}
    std::cout << "We should never be here\n";


}   //End of insert method

void AVL::printMetrics()
{
    /* printMetrics public method, parameter(s): None
     * Objective: Print the final results of the tree
     * Metrics:
     *  - Distinct Words
     *  - Total Words
     *  - Height
     *  - Reference Changes
     *  - BF changes
     *  - A to Y BF Changes
     *  - A to Y Passes
     *  - Key Comparisons
     *  - LL Rotations
     *  - LR Rotations
     *  - RR Rotations
     *  - RL Rotations
     *  - No Rotations needed
     *  - Elapsed Time
     *  */

    int height = calcHeight(root);  //Recurse the tree to get the height of it
    inOrderTraversal(root);         //This helps to calculate total words and distinct words
    std::cout << "Distinct Words: "     << distinctWords    << std::endl;   //Distinct Words
    std::cout << "Total Words: "        << totWords         << std::endl;   //Total words
    std::cout << "Height: "             << height           << std::endl;   //Height of the tree

    std::cout << "Reference Changes: "  << std::endl;

    std::cout << "BF Changes: "         << totBFChanges     << std::endl;   //Total changes in BF through the Insert()



    std::cout << "Key Comparisons: "    << totKeyComparison << std::endl;   //Total key comparisons done
    std::cout << "LL Rotations: "       << LLTot            << std::endl;   //Total Left-Left rotations done
    std::cout << "LR Rotations: "       << LRTot            << std::endl;   //Total Left-Right rotations done
    std::cout << "RR Rotations: "       << RRTot            << std::endl;   //Total Right-Right rotations done
    std::cout << "RL Rotations: "       << RLTot            << std::endl;   //Total Right-Left rotations done
    std::cout << "No rotation needed: " << NoRotTot         << std::endl;   //Total times Insert was called with no rotation


}   //End of printMetrics method

void AVL::inOrderTraversal(AVL::Node *node)
{
    /* inOrderTraversal private method, parameter(s): Node Pointer
     * Objective: Recurse through the tree and print nodes in-order
     * It is called by the printTree() public method
     */

    if (node == nullptr)            //If we reach a leaf
        return;                     //Exit
    inOrderTraversal(node->LCH);    //Traverse through the left side
    totWords += node->count;
    distinctWords++;
    inOrderTraversal(node->RCH);    //Traverse through the right side
}   //End of inOrderTraversal method

int AVL::calcHeight(AVL::Node *node)
{
    /* calcHeight private recursive method, parameter(s): Node pointer
     * Objective: Recurse through the tree to calculate the height of it
     * */

    if (node == nullptr)   return 0;           //If we hit a leaf exit

    int leftH   = calcHeight(node->LCH);    //Recurse and calculate the left height of the tree
    int rightH  = calcHeight(node->RCH);    //Recurse and calculate the right side of the tree

    if (leftH > rightH) return leftH + 1;   //Add to the left height
    else                return rightH + 1;  //Add to the right height
}   //End of calcHeight