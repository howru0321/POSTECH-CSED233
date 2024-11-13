#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* temp_root = _root;
    
    while (1) {
        if (temp_root == NULL) {
            Node* newNode = new Node(key);
            _root = newNode;
            break;
        }
        else if (temp_root->key == key) {
            return -1;
        }
        else if (temp_root->key > key) {
            if (temp_root->left == NULL) {
                Node* newNode = new Node(key);
                temp_root->left = newNode;
                break;
            }
            temp_root = temp_root->left;
        }
        else if (temp_root->key < key) {
            if (temp_root->right == NULL) {
                Node* newNode = new Node(key);
                temp_root->right = newNode;
                break;
            }
            temp_root = temp_root->right;
        }
    }
    height(_root);
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* temp_root = _root;
    Node* parent = NULL;
    bool left_true;

    while (1) {
        if (temp_root == NULL) {
            return -1;
        }
        else if (temp_root->key > key) {
            parent = temp_root;
            temp_root = temp_root->left;
            left_true = true;
        }
        else if (temp_root->key < key) {
            parent = temp_root;
            temp_root = temp_root->right;
            left_true = false;
        }
        else if (temp_root->key == key) {
            if ((temp_root == _root)&&(temp_root->left == NULL && temp_root->right == NULL)) {
                _root = NULL;
                delete temp_root;
            }
            else if (temp_root->left == NULL && temp_root->right == NULL) {
                if (left_true == true)
                    parent->left = NULL;
                else
                    parent->right = NULL;
                delete temp_root;
            }
            else if (temp_root->left == NULL) {
                if (left_true == true)
                    parent->left = temp_root->right;
                else
                    parent->right = temp_root->right;
                delete temp_root;
            }
            else if (temp_root->right == NULL) {
                if (left_true == true)
                    parent->left = temp_root->left;
                else
                    parent->right = temp_root->left;
                delete temp_root;
            }
            else {
                Node* temp = temp_root->right;
                Node* temp_parent = temp_root->right;

                while (temp->left != NULL) {
                    if (temp != temp_parent)
                        temp_parent = temp_parent->left;
                    temp = temp->left;
                }
                if (temp == temp_parent) {
                    temp_root->right = temp->right;
                }
                else {
                    temp_parent->left = temp->right;
                }
                temp_root->key = temp->key;
                delete temp;
            }
            break;
        }
    }
    height(_root);
    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int BinarySearchTree::height(Node* root) {
    int h = 0;
    int maxh = 0;

    if (root != NULL) {
        int left_height = height(root->left);
        int right_height = height(root->right);

        if (left_height > right_height)
            maxh = left_height;
        else
            maxh = right_height;

        h = maxh + 1;
        root->height = h;
    }
    return h;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
