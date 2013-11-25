/*----- treetester.cpp ----------------------------
 Program for testing class template BST2.
 ------------------------------------------------*/
#include <iostream>
using namespace std;

#include "BST2.h"
//#include <vector>

int main()
{
    string key = "some key";
    //char key[] = "some key";
    //int key = 99999;
    // Testing Constructor and empty()
    BST2<int, string> intBST2;            // test the class constructor
    cout << "Constructing empty BST2\n";
    cout << "BST2 " << (intBST2.empty() ? "is" : "is not") << " empty\n";
    
    // Testing inorder
    cout << "Inorder Traversal of BST2: \n";
    intBST2.inorder(cout);
    
    // Testing insert
    cout << "\nNow insert a bunch of integers into the BST2."
    "\nTry items not in the BST2 and some that are in it:\n";
    int number;
    for (;;)
    {
        cout << "Item to insert (-999 to stop): \n";
        cin >> number;
        if (number == -999)
            break;
            intBST2.insert(number, key);
    }
    
    cout << "Inorder Traversal of BST2: \n";
    intBST2.inorder(cout);
    
    cout << endl;
    
    // Testing search()
    cout << "\n\nNow testing the search() operation."
    "\nTry both items in the BST2 and some not in it:\n";
    for (;;)
    {
        vector<int> * searchResults;
        cout << "Item to find (-999 to stop): \n";
        cin >> number;
        if (number == -999)
            break;
        //cout << (intBST2.search(number, key, searchResults) ? "Found" : "Not found") << endl;
        bool found = intBST2.search(number, key, searchResults);
        if (found) {
            cout << "Item found, contents:" << endl;
            for (int i = 0; i < searchResults->size(); i++) {
                cout << searchResults->at(i) << endl;
            }
            cout << endl;
        }
    }
    
    // Testing remove()
    cout << "\nNow testing the remove() operation."
    "\nTry both items in the BST2 and some not in it:\n";
    for (;;)
    {
        cout << "Item to remove (-999 to stop): ";
        cin >> number;
        if (number == -999)
            break;
        intBST2.remove(number, key);
    }
    cout << "\nInorder Traversal of BST2: \n";
    intBST2.inorder(cout);
    cout << endl;
}
