#include "heap.h"
#include <iostream>
#include <string>

using namespace std;


MaxHeap::MaxHeap() {
    heap_size = 0;
    heap_arr = new int[100]; // Default array of size 100
}

string MaxHeap::printHeap(){
    string answer;
    for (int i = 0; i < heap_size; i++)
        answer += to_string(heap_arr[i]) + " ";
    return answer;
}

void MaxHeap::insertKey(int k) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    heap_arr[heap_size] = k;//값 대입

    heap_size++;
    
    int checkpoint1 = heap_size;
    int checkpoint2 = heap_size / 2;

    while (checkpoint2 != 0)//끝날때 까지 parent와 children 대소비교한다
    {
        if (heap_arr[checkpoint2 - 1] < heap_arr[checkpoint1 - 1])//재배열
        {
            int temp;
            temp = heap_arr[checkpoint2 - 1];
            heap_arr[checkpoint2 - 1] = heap_arr[checkpoint1 - 1];
            heap_arr[checkpoint1 - 1] = temp;//swap
        }

        checkpoint1 = checkpoint1 / 2;
        checkpoint2 = checkpoint2 / 2;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MaxHeap::deleteMax() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    heap_size--;

    int temp = heap_arr[heap_size];
    heap_arr[heap_size] = heap_arr[0];
    heap_arr[0] = temp;//끝 값 첫 값(최댓값)swap

    int checkpoint = 1;//비교할 parent의 위치. 2*checkpoint, 2*checkpoint+1 중 큰 children과 비교한다.
    while (checkpoint * 2 <= heap_size)
    {
        int* maxchildren;
        
        if (checkpoint * 2 == heap_size)//이 경우는 children이 하나밖에 없다.
        {
            maxchildren = &heap_arr[checkpoint * 2 - 1];
        }
        else//이 외의경우에는 항상 children이 2개이므로 대소비교를 해 주어야한다
        {
            if (heap_arr[checkpoint * 2 - 1] >= heap_arr[checkpoint * 2])//비교할 children중 max값을 찾는다
            {
                maxchildren = &heap_arr[checkpoint * 2 - 1];
            }
            else
            {
                maxchildren = &heap_arr[checkpoint * 2];
            }
        }

        if (heap_arr[checkpoint - 1] >= *maxchildren)//더이상 할 필요가 없다
        {
            break;
        }
        else
        {
            int swap = *maxchildren;
            *maxchildren = heap_arr[checkpoint - 1];
            heap_arr[checkpoint - 1] = swap;//swap
        }
        checkpoint *= 2;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MaxHeap::maxHeapProp(int i) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}