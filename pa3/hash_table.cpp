#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "shift_register.h"
#include "hash_table.h"

using namespace std;


HashTable::HashTable(int table_size, HashFunction *hf, ShiftRegister *sr) : table_size(table_size) {
    this->hf = hf;
    this->sr = sr;
    this->table = new int[this->table_size];
    this->states = new TableState[this->table_size];

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    for (int i = 0; i < this->table_size; i++) {
        this->states[i] = EMPTY;
    }
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

HashTable::~HashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void HashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == EMPTY)
            out << "empty" << endl;
        else if (this->states[i] == DELETED)
            out << "deleted" << endl;
        else if (this->states[i] == OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "unknown state" << endl;
    }
}

void HashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int add = hf->hashing(key);
    int add_temp = add;
    int collnum = 1;
    while (states[add_temp] != EMPTY) {
        add_temp = add + sr->getSeqNumber(collnum);
        add_temp %= table_size;
        collnum++;
    }
    table[add_temp] = key;
    states[add_temp] = OCCUPIED;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void HashTable::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int add = hf->hashing(key);
    int add_temp = add;
    int collnum = 1;
    while (!(table[add_temp] == key && states[add_temp] == OCCUPIED)) {
        add_temp = add + sr->getSeqNumber(collnum);
        add_temp %= table_size;
        collnum++;
    }
    states[add_temp] = DELETED;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
