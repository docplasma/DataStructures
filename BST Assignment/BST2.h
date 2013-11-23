//
//  BST2.h
//  BST Assignment
//
//  Created by Dexter Parks on 11/23/13.
//  Copyright (c) 2013 Dexter Parks. All rights reserved.
//

#ifndef BST_Assignment_BST2_h
#define BST_Assignment_BST2_h

template <typename DataType>
class BST2
{
private:
    /***** Node structure *****/
    class BinNode
    {
    public:
        DataType data;
        BinNode * left;
        BinNode *  right;
        
        // BinNode constructors
        // Default -- data part undefined; both links null
        BinNode()
        : left(0), right(0)
        {}
        
        // Explicit Value -- data part contains item; both links null
        BinNode(DataType item)
        : data(item), left(0), right(0)
        {}
    };
    
    typedef BinNode * BinNodePointer;
    
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
    
    bool search(const DataType & item) const;
    /*------------------------------------------------------------------------
     Search the BST2 for item.
     
     Precondition:  None.
     Postcondition: Returns true if item found, and false otherwise.
     -----------------------------------------------------------------------*/
    
    void insert(const DataType & item);
    /*------------------------------------------------------------------------
     Insert item into BST2.
     
     Precondition:  None.
     Postcondition: BST2 has been modified with item inserted at proper
     position to maintain BST2 property.
     ------------------------------------------------------------------------*/
    
    void remove(const DataType & item);
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
    void search2(const DataType & item, bool & found,
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
template <typename DataType>
inline BST2<DataType>::BST2()
: myRoot(0)
{}

//--- Definition of empty()
template <typename DataType>
inline bool BST2<DataType>::empty() const
{ return myRoot == 0; }

//--- Definition of search()
template <typename DataType>
bool BST2<DataType>::search(const DataType & item) const
{
    BST2<DataType>::BinNodePointer locptr = myRoot;
    bool found = false;
    for (;;)
    {
        if (found || locptr == 0) break;
        if (item < locptr->data)       // descend left
            locptr = locptr->left;
        else if (locptr->data < item)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    return found;
}

//--- Definition of insert()
template <class DataType>
inline void BST2<DataType>::insert(const DataType & item)
{
    BST2<DataType>::BinNodePointer
    locptr = myRoot,   // search pointer
    parent = 0;        // pointer to parent of current node
    bool found = false;     // indicates if item already in BST2
    while (!found && locptr != 0)
    {
        parent = locptr;
        if (item < locptr->data)       // descend left
            locptr = locptr->left;
        else if (locptr->data < item)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    if (!found)
    {                                 // construct node containing item
        locptr = new BST2<DataType>::BinNode(item);
        if (parent == 0)               // empty tree
            myRoot = locptr;
        else if (item < parent->data )  // insert to left of parent
            parent->left = locptr;
        else                           // insert to right of parent
            parent->right = locptr;
    }
    else
        cout << "Item already in the tree\n";
}

//--- Definition of remove()
template <class DataType>
void BST2<DataType>::remove(const DataType & item)
{
    bool found;                      // signals if item is found
    BST2<DataType>::BinNodePointer
    x,                            // points to node containing
    parent;                       //    "    " parent of x and xSucc
    search2(item, found, x, parent);
    
    if (!found)
    {
        cout << "Item not in the BST2\n";
        return;
    }
    //else
    if (x->left != 0 && x->right != 0)
    {                                // node has 2 children
        // Find x's inorder successor and its parent
        BST2<DataType>::BinNodePointer xSucc = x->right;
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
    BST2<DataType>::BinNodePointer
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
template <class DataType>
inline void BST2<DataType>::inorder(ostream & out)
{
    inorderAux(out, myRoot);
}


//--- Definition of search2()
template <class DataType>
void BST2<DataType>::search2(const DataType & item, bool & found,
                            BST2<DataType>::BinNodePointer & locptr,
                            BST2<DataType>::BinNodePointer & parent)
{
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // descend left
        {
            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->data < item)  // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else                           // item found
            found = true;
    }
}

//--- Definition of inorderAux()
template <class DataType>
void BST2<DataType>::inorderAux(ostream & out,
                               BST2<DataType>::BinNodePointer subtreeRoot)
{
    if (subtreeRoot != 0)
    {
        inorderAux(out, subtreeRoot->left);    // L operation
        out << subtreeRoot->data << "  ";      // V operation
        inorderAux(out, subtreeRoot->right);   // R operation
    }
}
#endif
