#include "shift_register.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int ShiftRegister::getSeqNumber(int idx) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int power = 0;
    int tempM = M;
    while (tempM != 1) {
        tempM /= 2;
        power++;
    }

    int* binaryD = new int[power];
    for (int i = 0; i < power; i++)
        binaryD[i] = 0;
    int* binary_k = new int[power];
    for (int i = 0; i < power; i++)
        binary_k[i] = 0;

    DecimalToBinary(initial_seed, binaryD);
    DecimalToBinary(k, binary_k);

    for (int i = 0; i < idx - 1; i++) {
        int leading_number = binaryD[power - 1];

        for (int i = power; i > 1; i--) {
            binaryD[i - 1] = binaryD[i - 2];
        }
        binaryD[0] = 0;

        if (leading_number == 1) {
            for (int i = 0; i < power; i++) {
                if (binaryD[i] == binary_k[i])
                    binaryD[i] = 0;
                else
                    binaryD[i] = 1;
            }
        }
    }
    return BinaryToDecimal(binaryD, power);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
void ShiftRegister::DecimalToBinary(int num, int binary[]) {
    int digit = 1;
    while (num != 0) {
        binary[digit - 1] = num % 2;
        num /= 2;
        digit++;
    }
}

int ShiftRegister::BinaryToDecimal(int binary[], int size) {
    int decimal = 0;
    int digit = 1;
    for (int i = 0; i < size; i++) {
        decimal += binary[i] * digit;
        digit *= 2;
    }
    return decimal;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
