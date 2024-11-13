#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}


void sortAlg::selectionSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    for (int i = 0; i < arr_size - 1; i++) {
        int temp_arr = arr[i];
        int temp_j = 0;
        for (int j = i; j < arr_size; j++) {
            if (temp_arr > arr[j]) {
                temp_arr = arr[j];
                temp_j = j;
            }
        }
        if (temp_j != 0) {
            arr[temp_j] = arr[i];
            arr[i] = temp_arr;
        }

        printArray(fout); // DO NOT ERASE THIS LINE
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::merge(int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    /*for (int i = left; i < right; i++) {
        int temp_arr = arr[i];
        int temp_j = 0;
        for (int j = i; j <= right; j++) {
            if (temp_arr > arr[j]) {
                temp_arr = arr[j];
                temp_j = j;
            }
        }
        if (temp_j != 0) {
            arr[temp_j] = arr[i];
            arr[i] = temp_arr;
        }
    }*/

    int range = right - left + 1;
    int mid;

    if (range <= 2) {
        mid = 1;
    }
    else if (range > 2 && range <= 4) {
        mid = 2;
    }
    else if (range > 4 && range <= 8) {
        mid = 4;
    }
    else if (range > 8 && range <= 16) {
        mid = 8;
    }
    else {
        mid = 16;
    }

    int temp[20];
    int i = left;
    int j = left + mid;
    int k = 0;

    while (!(i >= left + mid || j > right)) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    if (i >= left + mid) {
        for (int l = j; l <= right; l++) {
            temp[k] = arr[l];
            k++;
        }
    }
    else {
        for (int l = i; l < left + mid; l++) {
            temp[k] = arr[l];
            k++;
        }
    }

    for (int l = 0; l < k; l++) {
        arr[l + left] = temp[l];
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (left < right) {
        int group_range = 2;
        int range = right - left + 1;
        int group_number = range / 2;
        int odd = range % 2;

        while (group_number != 0) {
            int range_left = left;
            int range_right = left;

            for (int i = 0; i < group_number; i++) {
                if (range_left + group_range > right)
                    range_right = right;
                else
                    range_right = range_left + group_range - 1;
                merge(range_left, range_right);
                printArray(fout);// DO NOT ERASE THIS LINE<--여기에
                range_left += group_range;
            }
            group_range *= 2;
            group_number += odd;
            odd = group_number % 2;
            group_number = group_number / 2;

        }

        //printArray(fout);// DO NOT ERASE THIS LINE <-임의로 만든 for 문안에 printArray()를 넣어도 되나요?

    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}
