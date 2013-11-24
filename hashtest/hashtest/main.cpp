//
//  main.cpp
//  hashtest
//
//  Created by Dexter Parks on 11/24/13.
//  Copyright (c) 2013 Dexter Parks. All rights reserved.
//

#include <iostream>

template <class HashType>
class MyHash {
public:
    MyHash () {
        
    }
    
    size_t getHash(HashType preHash) {
        return std::hash<HashType>()(preHash);
    }
};

int main()
{
    MyHash<bool> hashObj = *new MyHash<bool>;

    std::cout << hashObj.getHash(true);
    return 0;
}

