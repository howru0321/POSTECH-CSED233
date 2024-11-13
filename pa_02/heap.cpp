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
    heap_arr[heap_size] = k;//�� ����

    heap_size++;
    
    int checkpoint1 = heap_size;
    int checkpoint2 = heap_size / 2;

    while (checkpoint2 != 0)//������ ���� parent�� children ��Һ��Ѵ�
    {
        if (heap_arr[checkpoint2 - 1] < heap_arr[checkpoint1 - 1])//��迭
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
    heap_arr[0] = temp;//�� �� ù ��(�ִ�)swap

    int checkpoint = 1;//���� parent�� ��ġ. 2*checkpoint, 2*checkpoint+1 �� ū children�� ���Ѵ�.
    while (checkpoint * 2 <= heap_size)
    {
        int* maxchildren;
        
        if (checkpoint * 2 == heap_size)//�� ���� children�� �ϳ��ۿ� ����.
        {
            maxchildren = &heap_arr[checkpoint * 2 - 1];
        }
        else//�� ���ǰ�쿡�� �׻� children�� 2���̹Ƿ� ��Һ񱳸� �� �־���Ѵ�
        {
            if (heap_arr[checkpoint * 2 - 1] >= heap_arr[checkpoint * 2])//���� children�� max���� ã�´�
            {
                maxchildren = &heap_arr[checkpoint * 2 - 1];
            }
            else
            {
                maxchildren = &heap_arr[checkpoint * 2];
            }
        }

        if (heap_arr[checkpoint - 1] >= *maxchildren)//���̻� �� �ʿ䰡 ����
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