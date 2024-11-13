#pragma once
#include <iostream>
#include <string>
using namespace std;

class ShiftRegister {

public:
    ShiftRegister(int m, int k, int d) : M(m), k(k), initial_seed(d) { };

    int getSeqNumber(int idx); // idx starts from 1

private:
    int M;
    int k;
    int initial_seed;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    void DecimalToBinary(int num, int binary[]);
    int BinaryToDecimal(int binary[], int size);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

