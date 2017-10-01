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
    Node *down = nullptr;
    std::string key = "";
    TYPE *value = nullptr;
    
    ~Node(){
        delete next;
        next = nullptr;
        delete down;
        down = nullptr;
        delete value;
        value = nullptr;
        key = "";
    }
    
};


template<typename TYPE>
class HashMap {
    
private:

    Node<TYPE> *hashList;
    Node<TYPE> **hashTable;
    Node<TYPE> *nextFreeNode;
    Node<TYPE> *lastNode;
    
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
        
        currentSize = 0;        //structure starts empty
        nextFreeNode = &hashList[0];
        lastNode = &hashList[capacity_in-1];
        
        // all nodes should be empty at this point
        // need to create linked list
        for (int i = 0; i < capacity_in-1;){
            hashList[i]->next=hashList[++i];
        }
        
        // need to set hashTable to be empty
        for (auto tableElt : hashTable){
            tableElt = nullptr;
        }
    }
    
    ~HashMap();
    
    /*
     * set
     * stores the given key/value pair in the hash map.
     * @parameter: key_in, val_in for setting
     * @returns: boolean value indicating success / failure
     */
    bool set(const std::string key_in, TYPE val_in){
        // three cases:
        // already here, not here w/ capacity, not here w/ no capacity
        
        int loc = hashing(key_in);
        Node<TYPE>* currentNode = hashTable[loc];
        Node<TYPE>* prevNode = nullptr;
        
        // if here (use get function to see if here)
        if (get(key_in) != NULL){
            
            //check loc given by hashing
            while(currentNode->key != key_in){
                currentNode = currentNode->down;
            }
            
            currentNode->value = val_in;
            return true;
        }
        
        // at this point - 2 cases left
        if (currentSize == hashmapCapacity)     return false;
        
        
        while (currentNode != nullptr){
            prevNode = currentNode;
            currentNode = currentNode->down;
        }
        
        if (prevNode != nullptr)    prevNode->down = nextFreeNode;
        
        currentNode->key = key_in;
        currentNode->value = val_in;
        
        currentSize++;
        nextFreeNode = nextFreeNode->next;
        
        return true;
    }
    
    /*
     * get
     * @parameter: takes in key
     * @returns: the value associated with the given key, or null if no value is set.
     */
    TYPE get(const std::string key_in) const{
        // two cases: there or not there
        
        if (currentSize == 0)   return NULL;
        
        int loc = hashing(key_in);
        Node<TYPE>* currentNode = hashTable[loc];
        
        if (currentNode == nullptr) return NULL;
        
        while(currentNode->key != key_in){
            if (currentNode->down != nullptr)   currentNode = currentNode->down;
            else                                return NULL;
        }
        
        return currentNode->value;
    }
    
    
    /*
     * deletes
     * NOTE: NEED TO USE DIFFERENT FUNCTION NAME HERE
     * (delete is a C++ keyword)
     * deletes value associated with string key
     * @parameter: key_in, string key to search for object
     * @returns: T, value on success or nothing if empty
     */
    TYPE deletes(const std::string key_in){
        
        if (currentSize == 0)       return NULL;
        if (get(key_in) == NULL)    return NULL;
        
        int loc = hashing(key_in);
        Node<TYPE>* currentNode = hashTable[loc];
        Node<TYPE>* prevNode = nullptr;
        
        // three cases:
        // 1) only one in hashTable col
        // 2) middle of hashTable col
        // 3) end of hashTable col
        
        //to find prevNode
        while(currentNode->key != key_in){
            prevNode = currentNode;
            currentNode = currentNode->down;
        }
        
        // case 1
        if (prevNode == nullptr){
            hashTable[loc] = nullptr;
            TYPE temp = currentNode->value;
            currentNode->next = nullptr;
            delete currentNode;
            lastNode->next = currentNode;
            lastNode = currentNode;
            
            return temp;
        }
        
        // case 2
        if (currentNode->down != nullptr){
            
            prevNode->down = currentNode->down;
            TYPE temp = currentNode->value;
            currentNode->next = nullptr;
            currentNode->down = nullptr;
            delete currentNode;
            lastNode->next = currentNode;
            lastNode = currentNode;
            
            return temp;
            
        }else{
            
            prevNode->down = nullptr;
            TYPE temp = currentNode->value;
            currentNode->next = nullptr;
            delete currentNode;
            lastNode->next = currentNode;
            lastNode = currentNode;
            
            return temp;
            
        }
        
    }
    
    /*
     * @return: float value representing the load factor
     * (`(items in hash map)/(size of hash map)`)
     */
    float load(){
        return ((float)currentSize / hashmapCapacity);
    }
    
};

#endif /* HashMap_hpp */
