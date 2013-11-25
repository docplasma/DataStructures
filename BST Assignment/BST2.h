//
//  BST2.h
//  BST Assignment
//
//  Created by Dexter Parks on 11/23/13.
//  Copyright (c) 2013 Dexter Parks. All rights reserved.
//

#ifndef BST_Assignment_BST2_h
#define BST_Assignment_BST2_h
#include <functional>
//#include "BinNode.h"
#include <vector>

template <typename DataType, class KeyType>
class BST2
{
private:
    /***** Node structure *****/
    class BinNode {
    public:
        vector<DataType>data = vector<int>(5,0);
        //vector<int> pointer = vector<int>(5,0);
        size_t key;
        BinNode * left;
        BinNode *  right;
        
        // BinNode constructors
        // Default -- data part undefined; both links null
        BinNode()
        : left(0), right(0)
        {}
        
        // Explicit Value -- data part contains item; both links null
        BinNode(DataType item, size_t hashKey) : data(item), key(hashKey), left(0), right(0) {
        }
    };
    typedef BinNode * BinNodePointer;
    
    size_t hashKey(KeyType preHash) const {
        return std::hash<KeyType>()(preHash);
    }
    
public:
    /***** Function Members *****/
    BST2();
    /*------------------------------------------------------------------------
     Construct a BST2 object.
     
     Precondition:  None.
     Postcondition: An empty BST2 has been constructed.
     -----------------------------------------------------------------------*/
    
    bool empty() const;
    /*------------------------------------------------------------------------
     Check if BST2 is empty.
     
     Precondition: None.
     Postcondition: Returns true if BST2 is empty and false otherwise.
     -----------------------------------------------------------------------*/
    
    bool search(const DataType & item, const KeyType & key, vector<DataType> *& data) const;
    /*------------------------------------------------------------------------
     Search the BST2 for item.
     
     Precondition:  None.
     Postcondition: Returns true if item found, and false otherwise.
     -----------------------------------------------------------------------*/
    
    void insert(const DataType & item, const KeyType & key);
    /*------------------------------------------------------------------------
     Insert item into BST2.
     
     Precondition:  None.
     Postcondition: BST2 has been modified with item inserted at proper
     position to maintain BST2 property.
     ------------------------------------------------------------------------*/
    
    void remove(const DataType & item, const KeyType & key);
    /*------------------------------------------------------------------------
     Remove item from BST2.
     
     Precondition:  None.
     Postcondition: BST2 has been modified with item removed (if present);
     BST2 property is maintained.
     Note: remove uses auxiliary function search2() to locate the node
     containing item and its parent.
     ------------------------------------------------------------------------*/
    
    void inorder(ostream & out);
    /*------------------------------------------------------------------------
     Inorder traversal of BST2.
     
     Precondition:  ostream out is open.
     Postcondition: BST2 has been inorder traversed and values in nodes
     have been output to out.
     Note: inorder uses private auxiliary function inorderAux().
     ------------------------------------------------------------------------*/
    
private:
    /***** Private Function Members *****/
    void search2(const DataType & item, const KeyType & key, bool & found,
                 BinNodePointer & locptr, BinNodePointer & parent);
    /*------------------------------------------------------------------------
     Locate a node containing item and its parent.
     
     Precondition: None.
     Postcondition: locptr points to node containing item or is null if
     not found, and parent points to its parent
     ------------------------------------------------------------------------*/
    
    void inorderAux(ostream & out, BinNodePointer subtreePtr);
    /*------------------------------------------------------------------------
     Inorder traversal auxiliary function.
     
     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this BST2.
     Postcondition: Subtree of this BST2 with subtreePtr as root has been
     output to out.
     ------------------------------------------------------------------------*/
    
    void graphAux(ostream & out, int indent, BinNodePointer subtreeRoot);
    /*------------------------------------------------------------------------
     Graph auxiliary function.
     
     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this BST2.
     Postcondition: Graphical representation of subtree of this BST2 with
     subtreePtr as root has been output to out, indented indent spaces.
     ------------------------------------------------------------------------*/
    
    /***** Data Members *****/
    BinNodePointer myRoot;
    
}; // end of class template declaration

//--- Definition of constructor
template <typename DataType, class KeyType>
inline BST2<DataType, KeyType>::BST2()
: myRoot(0)
{}

//--- Definition of empty()
template <typename DataType, class KeyType>
inline bool BST2<DataType, KeyType>::empty() const
{ return myRoot == 0; }

//--- Definition of search()
template <typename DataType, class KeyType>
bool BST2<DataType, KeyType>::search(const DataType & item, const KeyType & key, vector<DataType> *& dataPointer) const
{
    BST2<DataType, KeyType>::BinNodePointer locptr = myRoot;
    size_t hashedKey = hashKey(key); //Hashes the given key
    bool found = false;
    for (;;)
    {
        if (found || locptr == 0) break;
        if (hashedKey < locptr->key)       // descend left
            locptr = locptr->left;
        else if (locptr->key< hashedKey)  // descend right
            locptr = locptr->right;
        else {                          // item found
            found = true;
            cout << "\ndata location: " << &locptr->data <<endl;
            dataPointer = &locptr->data;
        }
        
    }
    return found;
}

//--- Definition of insert()

template <class DataType, class KeyType>
inline void BST2<DataType, KeyType>::insert(const DataType & item, const KeyType & key)
{
    BST2<DataType, KeyType>::BinNodePointer
    locptr = myRoot,   // search pointer
    parent = 0;        // pointer to parent of current node
    size_t hashedKey = hashKey(key); //Hashes the given key
    bool found = false;     // indicates if item already in BST2
    
    while (!found && locptr != 0)
    {
        parent = locptr;
        if (hashedKey < locptr->key)       // descend left
            locptr = locptr->left;
        else if (locptr->key < hashedKey)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    if (!found) {                                 // construct node containing item
        locptr = new BinNode(item, hashedKey);
        if (parent == 0)               // empty tree
            myRoot = locptr;
        else if (hashedKey < parent->key )  // insert to left of parent
            parent->left = locptr;
        else                           // insert to right of parent
            parent->right = locptr;
        //int index = locptr->data.size();
        locptr->data.insert(locptr->data.begin(), item);
    }
    else {
        int index = locptr->data.size();
        locptr->data[index] = item;
        //locptr->data[locptr->data.size()] = item;
    }
}

//--- Definition of remove()
template <class DataType, class KeyType>
void BST2<DataType, KeyType>::remove(const DataType & item, const KeyType & key)
{
    bool found;                      // signals if item is found
    BST2<DataType, KeyType>::BinNodePointer
    x,                            // points to node containing
    parent;                       //    "    " parent of x and xSucc
    search2(item, key, found, x, parent);
    
    if (!found)
    {
        cout << "Item not in the BST2\n";
        return;
    }
    //else
    if (x->left != 0 && x->right != 0)
    {                                // node has 2 children
        // Find x's inorder successor and its parent
        BST2<DataType, KeyType>::BinNodePointer xSucc = x->right;
        parent = x;
        while (xSucc->left != 0)       // descend left
        {
            parent = xSucc;
            xSucc = xSucc->left;
        }
        
        // Move contents of xSucc to x and change x
        // to point to successor, which will be removed.
        x->data = xSucc->data;
        x = xSucc;
    } // end if node has 2 children
    
    // Now proceed with case where node has 0 or 2 child
    BST2<DataType, KeyType>::BinNodePointer
    subtree = x->left;             // pointer to a subtree of x
    if (subtree == 0)
        subtree = x->right;
    if (parent == 0)                  // root being removed
        myRoot = subtree;
    else if (parent->left == x)       // left child of parent
        parent->left = subtree;
    else                              // right child of parent
        parent->right = subtree;
    delete x;
}

//--- Definition of inorder()
template <class DataType, class KeyType>
inline void BST2<DataType, KeyType>::inorder(ostream & out)
{
    inorderAux(out, myRoot);
}


//--- Definition of search2()
template <class DataType, class KeyType>
void BST2<DataType, KeyType>::search2(const DataType & item, const KeyType & key, bool & found,
                            BST2<DataType, KeyType>::BinNodePointer & locptr,
                            BST2<DataType, KeyType>::BinNodePointer & parent)
{
    size_t hashedKey = hashKey(key); //Hashes the given key
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if ( hashedKey < locptr->key)       // descend left
        {
            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->key < hashedKey)  // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else                           // item found
            found = true;
    }
}

//--- Definition of inorderAux()
template <class DataType, class KeyType>
void BST2<DataType, KeyType>::inorderAux(ostream & out, BST2<DataType, KeyType>::BinNodePointer subtreeRoot)
{
    if (subtreeRoot != 0)
    {
        inorderAux(out, subtreeRoot->left);    // L operation
        out << "Node members: ";
        for (int i=0;i<subtreeRoot->data.size();i++) {
            if (i > 0 && subtreeRoot->data[i] == 0) { //Breaks out of the printing if the rest of the container is empty
                break;
            }
            out << subtreeRoot->data[i] << " ";
        }
        out << endl;
        inorderAux(out, subtreeRoot->right);   // R operation
    }
}
#endif
