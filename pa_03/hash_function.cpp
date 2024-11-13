#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int HashFunction::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int *binary = new int[2 * key_size];
    for (int i = 0; i < 2 * key_size; i++) {
        binary[i] = 0;
    }

    DecimalToBinary(key * key, binary);

    int index_decimal = index(binary);
    delete[] binary;
    return index_decimal;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
void HashFunction::DecimalToBinary(int num, int binary[]) {
    int digit = 1;
    while (num != 0) {
        binary[digit - 1] = num % 2;
        num /= 2;
        digit++;
    }
}

int HashFunction::BinaryToDecimal(int binary[], int size) {
    int decimal = 0;
    int digit = 1;
    for (int i = 0; i < size; i++) {
        decimal += binary[i] * digit;
        digit *= 2;
    }
    return decimal;
}

int HashFunction::index(int binary[]) {
    int remove_range = (2 * key_size - index_size) / 2;
    int* index_binary = new int[index_size];
    for (int i = 0; i < index_size; i++) {
        index_binary[i] = 0;
    }

    for (int i = 0; i < index_size; i++) {
        index_binary[i] = binary[i + remove_range];
    }
    int index_decimal = BinaryToDecimal(index_binary, index_size);
    delete[] index_binary;
    return index_decimal;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
