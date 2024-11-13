#pragma once
#include "bst.h"

using namespace std;

class AVLTree: public BinarySearchTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    int insertion(int key);
    int deletion(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int avl_height(Node* node);
    int BF(Node* node);

    Node* RR(Node* A);
    Node* LL(Node* A);
    Node* LR(Node* A);
    Node* RL(Node* A);

    Node* Balance(Node* node);

    Node* insertion(Node* node, int key);
    Node* deletion(Node* node, int key);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};