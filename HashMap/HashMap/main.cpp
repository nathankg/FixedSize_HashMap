//
//  main.cpp
//  HashMap
//
//  Created by Nathan Gupta on 9/30/17.
//  Copyright © 2017 Nathan Gupta. All rights reserved.
//



#include <iostream>
#include <string>
#include <cassert>
#include "HashMap.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    cout << "TESTING:\n" << endl;
    
    cout << "---BASIC TESTS---" << endl;
    
    cout << "Testing 1 - Checking instantiation" << endl;
    HashMap<int> hashTable(3);
    cout << "Test 1 Passes!" << endl;
    
    cout << "Testing 2 - Checking Set(Nathan, 2)" << endl;
    hashTable.set("Nathan", 2);
    cout << "Test 2 Passes!" << endl;
    
    cout << "Testing 3 - Checking Get(Nathan)" << endl;
    int ans = hashTable.get("Nathan");
    assert(ans == 2);
    cout << "Test 3 Passes!" << endl;
    
    cout << "Testing 4 - Checking Deletes(Nathan)" << endl;
    ans = hashTable.deletes("Nathan");
    assert(ans == 2);           //NOT SURE WHY DELETE IS NOT WORKING
    cout << "Test 4 Passes!" << endl;

    
    return 0;
}
