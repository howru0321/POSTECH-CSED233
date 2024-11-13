#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"

using namespace std;


/* 
    [Task 1] Choose the TIGHT bound of the following maxProduct function
    
    *maxProduct*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n >= 1 integers
        - int* B: an array storing n >= 1 integers
        Output
        - int: The maximum product of elements from each A and B
        int maxProduct(int n, int* A, int* B) { 
            int currMax = 0; 
            for (int i = 1; i < n; i++) 
                for (int j = 1; j < n; j++) 
                    if (currMax < A[i]*B[j]) 
                        currMax = A[i]*B[j]; 
            return currMax; 
        } 

    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
    int answer = 4;  // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the TIGHT bound of the following medianSearch function

    *medianSearch*
        Input
        - int n: the length of the input array (n >=2)
        - double* A: an ascending sorted array with n >=2 integers
        Output
        - double*: An array B which contains n-th, n/2-th, n/4-th, .. elements of A
        double* medianSearch(int n, double* A) { 
            double *B = new double[n]; 
            //B is allocated as same size as A  
            int j = 0; 
            for (int i = n; i >= 1; i = i/2) { 
                B[j] = A[i-1]; 
                j++; 
            } 
            return B; 
        } 

    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n )
        4: O( n^2 )
*/
void task_2(ofstream &fout) {
    int answer = 1;  // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the ascending order “sorted” list. 
        An user can delete a specified smallest element. 
        If the specified element is out of range of the given list, print “error” 
 
        Tips: Please do not try to implement sorting algorithm for this task

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,integer): insert integer into the appropriate position in the sorted list.  
        - (‘delete_at’,i): delete an item that is i-th smallest element in the list. i indicates zero-based index. 

    Output: 
        - An array after insertion/deletion in a string separated with the spacebar 
        - “error” if the index is out of range
*/

void task_3(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    instr_seq = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    int* a = (int*)malloc(sizeof(int));
    int cnt3 = 0;


    for (int i=0; i<instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("insert") == 0) {
            /* TODO: Implement */
            cnt3++;
            int cp = -1;
            a = (int*)realloc(a, sizeof(int) * cnt3);
            if (cnt3 == 1)
            {
                a[0] = instr_seq->instructions[i].value;
            }
            else
            {
                for (int h = 0; h < cnt3 - 1; h++)
                {
                    if (a[h] >= instr_seq->instructions[i].value)
                    {
                        cp = h;
                    }
                }
                if (cp == -1)
                {
                    a[cnt3 - 1] = instr_seq->instructions[i].value;
                }
                else
                {
                    for (int hh = cnt3 - 1; hh > cp; hh--)
                    {
                        a[hh] = a[hh - 1];
                    }
                    a[cp] = instr_seq->instructions[i].value;
                }
            }


        } else if(command.compare("delete_at") == 0) {
            /* TODO: Implement */
            if (instr_seq->instructions[i].value >= cnt3)
            {
                answer = "error";
            }
            else
            {
                for (int o = instr_seq->instructions[i].value; o < cnt3 - 1; o++)
                {
                    a[o] = a[o + 1];
                }
                cnt3--;
                a = (int*)realloc(a, sizeof(int) * cnt3);
            }


        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
    if (answer != "error")
    {
        answer = "";
        answer += (to_string(a[0]));
        for (int q = 01; q < cnt3; q++)
        {
            answer += " ";
            answer += (to_string(a[q]));
        }
    }
    free(a);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    fout << "[Task 3]" << endl;
    fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top” operation is called after the sequence of “push” or “pop” operations. 
        If the stack is empty, and the “top” operation is called, then print “-1”, If “pop” operation from the empty stack then print “error” 

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack (integer is always positive) 
        - (‘pop’,NULL): pop the top value of the current stack (this operation will print nothing) 
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if the current stack is empty) 

    Output:
        - Expected printed values after processing the whole sequence, in a string separated with the spacebar 
        - “error” if the pop operation is executed on an empty stack 
*/

void task_4(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;
    
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    
    instr_seq = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    int* a = (int*)malloc(sizeof(int));
    int cnt4 = 0;
    int cp = 0;
    int cp1 = 0;


    for (int i=0; i<instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("push") == 0) {
            /* TODO: Implement */
            cnt4++;
            a = (int*)realloc(a, sizeof(int) * cnt4);
            a[cnt4 - 1] = instr_seq->instructions[i].value;

        } else if (command.compare("pop") == 0 ){
            /* TODO: Implement */
            cnt4--;
            if (cnt4 == -1)
            {
                cp1 = -2;
                break;
            }
            else
            {
                a = (int*)realloc(a, sizeof(int) * cnt4);
            }


        } else if ( command.compare("top") == 0 ){
            /* TODO: Implement */
            if (cnt4 == 0)
            {
                if (cp != 0)
                {
                    answer += " ";
                }
                answer += "-1";
                cp++;
            }
            else if (cp == 0)
            {
                answer += (to_string(a[cnt4 - 1]));
                cp++;
            }
            else
            {
                answer += " ";
                answer += (to_string(a[cnt4 - 1]));
                cp++;
            }


        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

  
    if (cp1 == -2)
    {
        answer = "error";
    }
    free(a);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 4]" << endl;
    fout << answer << endl;
}

/*
    [Task 5] Queue

    Description:
        - Implement a function which shows the value in the queue from the head to tail.

    Input:
        Sequence of commands, which is one of the following,
        -(‘enqueue’,integer): enqueue integer into the current queue

    Output: 
        - Values in the queue from the head to the tail, in a string separated with the spacebar 
        
*/
void task_5(ofstream &fout, InstructionSequence* instr_seq) {
    string answer; 

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    instr_seq = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);


    for (int i=0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("enqueue") == 0) {
            /* TODO: Implement */
            if (i == 0)
            {
                answer = (to_string(instr_seq->instructions[i].value));
            }
            else
            {
                answer += " ";
                answer += (to_string(instr_seq->instructions[i].value));
            }


        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 5]" << endl;
    fout << answer << endl;
    
}

/*
    [Task 6] Queue

    Description: 
        Implement a function which shows the value of a queue after the sequence of arbitrary queue operation. 
        If the queue after the operations is empty, print “empty”. 
        If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue 

    Output
        - Values in the queue from the head to the tail, in a string separated with spacebar 
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on an empty queue
*/
void task_6(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;
    
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    instr_seq = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    int* a = (int*)malloc(sizeof(int));
    int cnt6 = 0;
    int cp = 1;


    for (int i=0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("enqueue") == 0) {
            /* TODO: Implement */
            cnt6++;
            a = (int*)realloc(a, sizeof(int) * cnt6);
            a[cnt6 - 1] = instr_seq->instructions[i].value;


        } else if (command.compare("dequeue") == 0) {
            /* TODO: Implement */
            cnt6--;
            if (cnt6 == 0)
            {
                cp = 0;
                answer = "empty";
            }
            else if (cnt6 == -1)
            {
                cp = -1;
                answer = "error";
                break;
            }
            else
            {
                for (int v = 0; v < cnt6; v++)
                {
                    a[v] = a[v + 1];
                }
                a = (int*)realloc(a, sizeof(int) * cnt6);
            }


        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
    if (cp == 1)
    {
        answer = (to_string(a[0]));
        for (int v = 1; v < cnt6; v++)
        {
            answer += " ";
            answer += (to_string(a[v]));
        }
    }
    free(a);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 6]" << endl;
    fout << answer << endl;
}


int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence* instr_seq;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        try {
            instr_seq = ParseInstructions(argv[2]);
        }
        catch (const char* e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout);
            break;
        case 2:
            task_2(fout);
            break;
        case 3:
            task_3(fout, instr_seq);
            break;
        case 4:
            task_4(fout, instr_seq);
            break;
        case 5:
            task_5(fout, instr_seq);
            break;
        case 6:
            task_6(fout, instr_seq);
            break;
        case 0:
            task_1(fout);
            task_2(fout);

            InstructionSequence* instr_seq_3;
            instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq_3);
            
            InstructionSequence* instr_seq_4;
            instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq_4);
            
            InstructionSequence* instr_seq_5;
            instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq_5);
            
            InstructionSequence* instr_seq_6;
            instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq_6);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}