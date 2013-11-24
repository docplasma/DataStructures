//
//  BinNode.h
//  BST Assignment
//
//  Created by Dexter Parks on 11/24/13.
//  Copyright (c) 2013 Dexter Parks. All rights reserved.
//

#ifndef BST_Assignment_BinNode_h
#define BST_Assignment_BinNode_h

template<typename DataType, class KeyType>
    class BinNode {
    public:
        DataType data;
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

#endif
