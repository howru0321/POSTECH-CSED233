#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
int AVLTree::BF(Node* root) {
    int left_height;
    int right_height;

    if (root->left == NULL)
        left_height = 0;
    else
        left_height = root->left->height;
    if (root->right == NULL)
        right_height = 0;
    else
        right_height = root->right->height;

    return (left_height - right_height);
}

Node* AVLTree::RR(Node* A) {
    Node* B = A->right;

    A->right = B->left;
    B->left = A;

    return B;
}

Node* AVLTree::LL(Node* A) {
    Node* B = A->left;

    A->left = B->right;
    B->right = A;

    return B;
}
Node* AVLTree::LR(Node* A) {
    Node* B = A->left;

    A->left = RR(B);

    return LL(A);
}

Node* AVLTree::RL(Node* A) {
    Node* B = A->right;

    A->right = LL(B);

    return RR(A);
}

Node* AVLTree::Balance(Node* root) {
    int bf = BF(root);
    if (bf > 1) {
        if (BF(root->left) > 0) {
            root = LL(root);
        }
        else {
            root = LR(root);
        }
   }
    else if (bf < -1) {
        if (BF(root->right) > 0) {
            root = RL(root);
        }
        else {
            root = RR(root);
        }
    }
    return root;
}

/*Node* AVLTree::Balance(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    root->left = Balance(root->left);
    root->right = Balance(root->right);
    int bf = BF(root);

    if (bf >= -1 && bf <= 1) {
        return root;
    }
    else if (bf > 1) {
        if (BF(root->left) > 0)
            root = LL(root);
        else
            root = LR(root);
        return root;
    }
    else {
        if (BF(root->right) < 0)
            root = RR(root);
        else
            root = RL(root);
    }
}*/


int AVLTree::avl_height(Node* root) {
    int h = 0;
    int maxh = 0;

    if (root != NULL) {
        int left_height = avl_height(root->left);
        int right_height = avl_height(root->right);

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


int AVLTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    /*int re;
    re = BinarySearchTree::insertion(key);
    _root = Balance(_root);
    return re;*/
    Node* temp_root = _root;
    int re = 0;

    while (1) {
        if (temp_root == NULL) {
            break;
        }
        else if (temp_root->key == key) {
            re = -1;
            break;
        }
        else if (temp_root->key > key) {
            if (temp_root->left == NULL) {
                break;
            }
            temp_root = temp_root->left;
        }
        else if (temp_root->key < key) {
            if (temp_root->right == NULL) {
                break;
            }
            temp_root = temp_root->right;
        }
    }
    if (re == 0)
        _root = insertion(_root, key);
    return re;
    
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::deletion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    /*int re;
    re = BinarySearchTree::deletion(key);
    _root = Balance(_root);
    return re;*/
    Node* temp_root = _root;
    Node* parent = NULL;
    bool left_true;

    int re = 0;

    while (1) {
        if (temp_root == NULL) {
            re = -1;
            break;
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
            break;
        }
    }
    if (re == 0)
        _root = deletion(_root, key);
    return re;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

Node* AVLTree::insertion(Node* root, int key) {
    if (root == NULL) {
        root = new Node(key);
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (root->key > key) {
        root->left = insertion(root->left, key);
        avl_height(_root);
        root = Balance(root);
        avl_height(_root);
    }
    else {
        root->right = insertion(root->right, key);
        avl_height(_root);
        root = Balance(root);
        avl_height(_root);
    }
    return root;
}

Node* AVLTree::deletion(Node* root, int key) {
    if ((root == _root)&&(root->left == NULL && root->right == NULL)) {
        delete root;
        return NULL;
    }
    if (root->key == key) {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* temp = root->right;
            Node* temp_parent = root->right;

            while (temp->left != NULL) {
                if (temp != temp_parent)
                    temp_parent = temp_parent->left;
                temp = temp->left;
            }
            if (temp == temp_parent) {
                root->right = temp->right;
            }
            else {
                temp_parent->left = temp->right;
            }
            root->key = temp->key;
            delete temp;
            return root;
        }
    }
    else if (root->key > key) {
        root->left = deletion(root->left, key);
        avl_height(_root);
        root->left = Balance(root->left);
        avl_height(_root);
    }
    else {
        root->right = deletion(root->right, key);
        avl_height(_root);
        root->left = Balance(root->left);
        avl_height(_root);
    }
    root = Balance(root);
    avl_height(_root);
    return root;
}
