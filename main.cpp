#include <iostream>
#include <fstream>      //To read files
//The following are for the Trees & SkipList classes
#include "BST.h"        //Binary Search Tree
#include "SkipList.h"   //SkipList class
#include "RBT.h"        //Red-Black Tree
#include "AVL.h"        //AVL Tree

using namespace std;

int main()
{
    char c;
    RBT*      RBT_T = new RBT();        //Initiate each of the tree
    AVL*      AVL_T = new AVL();        //
    BST*      BST_T = new BST();        //
    SkipList* SL    = new SkipList();   // and the skip list


    char chari[50]; //assumes no word is longer than 49 characters
    memset(chari, 0 , 50);  //zero the word buffer
    int iPtr;
    ifstream inFile;

    for (int pass = 0; pass < 6; pass++) {
        bool IsDelimiter = false, WasDelimiter = false;
        inFile.open("/Users/cgalo/CLionProjects/Trees-and-SkipList/Testing Files/Shakespeare.txt", ios::binary);
        if (inFile.fail()) {
            cout << "Unable to open input file \n\n"
                 << "Program Exiting\nPress ENTER to exit\n";
            cin.get(c);
            exit(1);
        }
        iPtr = 0;
        inFile.get(c);  // priming read
        while (!inFile.eof()) {
            IsDelimiter = (c == ' ' || c == 10 || c == 13 || c == ',' || c == '.' || c == '\'' ||
                           c == ':' || c == ';' || c == '"' || c == '?' || c == '!' || c == '-' ||
                           c == '(' || c == ')' || c == '[' || c == ']' || c == '_' || c == '*' || c == 9);
            if (IsDelimiter && !WasDelimiter)   // if THIS character IS a delimiter, and the
                                                //last one WASN'T, it's the end of a word
            {
                WasDelimiter = true;
                if (pass == 2) RBT_T->Insert(chari);   //insert this word in the RBT
                else if (pass == 3) AVL_T->Insert(chari);   //insert it in the AVL tree
                else if (pass == 4) BST_T->Insert(chari);   //insert it in the BST
                else if (pass == 5) SL->Insert(chari);   //insert it in the skipList
                memset(chari, 0, 50);   //zero the word buffer
                iPtr = 0;
            }
            else if (!IsDelimiter) chari[iPtr++] = c;  //if this isn't a delimiter, keep going

            WasDelimiter = IsDelimiter; //for the NEXT iteration
            inFile.get(c);
        }   //End of while-loop
        inFile.close();
        // If the file doesn't end with a delimiter, it will leave the last word unprocessed.
        // Insert once more, and display the statistics for this structure...
        //

        if (pass == 2) {if (strlen(chari))      RBT_T->Insert(chari);   RBT_T->displayStatistics();}    // RBT
        else if (pass == 3) {if (strlen(chari)) AVL_T->Insert(chari);   AVL_T->displayStatistics();}    // AVL
        else if (pass == 4) {if (strlen(chari)) BST_T->Insert(chari);   BST_T->displayStatistics();}    // BST
        else if (pass == 5) {if (strlen(chari)) SL->Insert(chari);           SL->displayStatistics();}       // skip list
    }
    return 0;
}   //End of main function
