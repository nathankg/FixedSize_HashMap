//
//  HashMap.cpp
//  HashMap
//
//  Created by Nathan Gupta on 9/30/17.
//  Copyright © 2017 Nathan Gupta. All rights reserved.
//

#include <iostream>
#include "HashMap.h"

using namespace std;

HashMap::HashMap(int capacity_in): hashmapCapacity(capacity_in) {

    if (hashmapCapacity <= 0){
        cerr << "Error: Invalid HashMap Capacity" << endl;
        exit(1);
    }
    
}




template <typename T>
float HashMap::load(){
    
    if (hashmapCapacity <= 0){
        cerr << "Error: Invalid HashMap Capacity" << endl;
        exit(1);
    }
    
    return ((float)currentSize / hashmapCapacity);
}


int HashMap::hashing(string key_in){
    
    hash<string> strHash;
    
    return (strHash(key_in)%hashmapCapacity);
    
}
