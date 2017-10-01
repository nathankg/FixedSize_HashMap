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
 
 PLAN:
 
 Key thoughts:
 - fixed-size: max num of elts that can be added is fixed by constructor
 - no resizing
 
 we'll use one hashtable with two representations
 one representation will be in the list form for a linear search, in order of created
 the second representation will be more like a table reliant on hashkeys & indexable
 
 
 Implement following functions:
 
 - get(key): return the value associated with the given key, or null if no value is set.
 
 - delete(key): delete the value associated with the given key, 
 returning the value on success or null if the key has no value.
 
 */


#ifndef HashMap_h
#define HashMap_h

#include <stdio.h>
#include <string>

// Node
// represents the inividual "storage space" for each string key to data object reference
template<typename TYPE>
struct Node {
    Node *next = nullptr;
    std::string key = "";
    TYPE *value = nullptr;
};


template<typename TYPE>
class HashMap {
    
private:

    Node<TYPE> *hashList;
    Node<TYPE> **hashTable;
    
    int hashmapCapacity;
    int currentSize;
    
    // hashing
    // @parameter: key_in, takes in key string
    // @returns: returns location
    int hashing(std::string key_in){
        std::hash<std::string> strHash;
        return (strHash(key_in)%hashmapCapacity);
    }
    
public:
    
    // default constructor - not needed
    // HashMap(): hashmapCapacity(0){};
    
    /*
     * custom constructor
     * @parameter: size_in, size of space for pre-allocation
     */
    HashMap(int capacity_in): hashmapCapacity(capacity_in) {
        if (hashmapCapacity <= 0){
            std::cerr << "Error: Invalid HashMap Capacity" << std::endl;
            exit(1);
        }
        
        // create array of Nodes based on max cap.
        hashList = new Node<TYPE>[hashmapCapacity];
        
        // create array of pointers to nodes based on max cap.
        hashTable = new Node<TYPE>*[hashmapCapacity];
        
        currentSize = 0;                 //structure starts empty
        
        // all nodes should be empty at this point
        
    }
    
    ~HashMap();
    
    /*
     * set
     * stores the given key/value pair in the hash map.
     * @parameter: key_in, val_in for setting
     * @returns: boolean value indicating success / failure
     */
    bool set(std::string key_in, TYPE val_in){
        
        // three cases:
        // already here, not here w/ capacity, not here w/ no capacity
        
        int loc = hashing(key_in);
        Node<TYPE>* currentNode = hashTable[loc];
        
        // if here (use get function to see if here)
        if (get(key_in) != NULL){
            
            //check loc given by hashing
            while(currentNode->key != key_in){
                currentNode = currentNode->next;
            }
            
            currentNode->value = val_in;
            return true;
        }
        
        // at this point - 2 cases left
        if (currentSize == hashmapCapacity)     return false;
        
        while (currentNode == nullptr){
            currentNode = currentNode->next;
        }
        
        currentNode->next = &hashList[currentSize++];
        currentNode->key = key_in;
        currentNode->value = val_in;
        
        return true;
        
    }
    
    TYPE get(std::string key_in);
    
    
    /*
     * deletes
     * NOTE: NEED TO USE DIFFERENT FUNCTION NAME HERE
     * (delete is a C++ keyword)
     * deletes value associated with string key
     * @parameter: key_in, string key to search for object
     * @returns: T, value on success or nothing if empty
     */
    TYPE deletes(std::string key_in);
    
    /*
     * @return: float value representing the load factor
     * (`(items in hash map)/(size of hash map)`)
     */
    float load(){
        return ((float)currentSize / hashmapCapacity);
    }
    
};

#endif /* HashMap_hpp */
