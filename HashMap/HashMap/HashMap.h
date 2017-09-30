//
//  HashMap.h
//  HashMap
//
//  Created by Nathan Gupta on 9/30/17.
//  Copyright © 2017 Nathan Gupta. All rights reserved.
//


/*
 
 Using only primitive types, implement a fixed-size hash map that associates string keys with arbitrary
 data object references (you don't need to copy the object). Your data structure should be optimized for
 algorithmic runtime and memory usage. You should not import any external libraries, and may not
 use primitive hash map or dictionary types in languages like Python or Ruby.
 
 */

/*
 
 Plan:
 
 
 Implement four functions:
 
 - constructor(size): return an instance of the class with pre-allocated space for
 the given number of objects.
 
 - boolean set(key, value): stores the given key/value pair in the hash map. 
 Returns a boolean value indicating success / failure of the operation.
 
 - get(key): return the value associated with the given key, or null if no value is set.
 
 - delete(key): delete the value associated with the given key, 
 returning the value on success or null if the key has no value.
 
 - float load(): return a float value representing the load factor 
 (`(items in hash map)/(size of hash map)`) of the data structure. 
 Since the size of the data structure is fixed, this should never be greater than 1.
 
 */


#ifndef HashMap_h
#define HashMap_h

#include <stdio.h>
#include <string>

class HashMap {
    
    int hashmapSize;
    
    
public:
    
    HashMap(): hashmapSize(0){};
    
    HashMap(): {}
    
    bool set(std::string key_in, int val_in);
    
    int get(std::string key_in);
    
    int delete(std::string key_in);
    
    float load();
    
};

#endif /* HashMap_hpp */
