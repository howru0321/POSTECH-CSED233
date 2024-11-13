#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string temp = "";
    BinaryTree templeft;//preOrder 함수를 재귀적으로 사용하기 위해서 임시 tree class를 만든다
    BinaryTree tempright;

    templeft._root = _root->left;//초기화
    tempright._root = _root->right;

    temp += _root->value;
    temp += " ";
    if (_root->left != NULL)//이 경우는 왼쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        temp += templeft.preOrder();
        temp += " ";
    }
    if (_root->right != NULL)//이 경우는 오른쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        temp += tempright.preOrder();
        temp += " ";
    }

    temp.pop_back();//마지막 띄어쓰기 제거

    return temp;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string temp = "";
    BinaryTree templeft;//postOrder 함수를 재귀적으로 사용하기 위해서 임시 tree class를 만든다
    BinaryTree tempright;

    templeft._root = _root->left;//초기화
    tempright._root = _root->right;

    if (_root->left != NULL)//이 경우는 왼쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        temp += templeft.postOrder();
        temp += " ";
    }
    if (_root->right != NULL)//이 경우는 오른쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        temp += tempright.postOrder();
        temp += " ";
    }
    temp += _root->value;
    temp += " ";

    temp.pop_back();//마지막 띄어쓰기 제거

    return temp;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string temp = "";
    BinaryTree templeft;//inOrder 함수를 재귀적으로 사용하기 위해서 임시 tree class를 만든다
    BinaryTree tempright;

    templeft._root = _root->left;//초기화
    tempright._root = _root->right;

    if (_root->left != NULL)//이 경우는 왼쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        temp += templeft.inOrder();
        temp += " ";
    }
    temp += _root->value;
    temp += " ";
    if (_root->right != NULL)//이 경우는 오른쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        temp += tempright.inOrder();
        temp += " ";
    }

    temp.pop_back();//마지막 띄어쓰기 제거

    return temp;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    int temp = 0;
    int left = 0;
    int right = 0;

    BinaryTree templeft;//getDepth 함수를 재귀적으로 사용하기 위해서 임시 tree class를 만든다
    BinaryTree tempright;

    templeft._root = _root->left;//초기화
    templeft.checkposition = 1;
    tempright._root = _root->right;
    tempright.checkposition = 1;

    int num = _root->value - '0';
    if (num == node_value)//원하는 값을 찾은 경우 temp를 1로 바꾼다
    {
        temp = 1;
    }


    if (_root->left != NULL)//이 경우는 왼쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        left=templeft.getDepth(node_value);
    }
    if (_root->right != NULL)//이 경우는 오른쪽 값이 없다는 뜻이므로, 재귀를 더이상 진행하지 않는다
    {
        right = tempright.getDepth(node_value);
    }
    if (left + right != 0)//left right children 이 둘다 0이 아니면서 value가 원하는 값이 나오는경우는 없다. 원하는 값은 하나이기 때문이다. 그래이 만약 left+right!=인 경우는 temp=0이므로 left+right+1값을 받으면 된다.
    {
        temp = (left + right + 1);
    }
    
    if (this->checkposition == 0 && temp == 0)//Traversal을 완료했음에도 temp가 0이라면, 찾는 값은 없으므로 -1을 리턴한다
    {
        return -1;
    }
    else if (this->checkposition == 0 && temp != 0)//Traversal 완료하고 원하는 값을 찾은 경우. 이 경우는 처음 temp 시작을 1로 했으므로, 최종적으로 root에 도달했을때 temp는 depth보다 1이 클 것이다.(root의 depth는 1이 아니라 0이기때문) 따라서 이 경우에는 tmep-1을 리턴해야한다
    {
        return temp - 1;
    }
    else//Traversal 를 완료하지 못한 경우
    {
        return temp;
    }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isProper() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    bool temp;
    bool left;
    bool right;
    
    BinaryTree templeft;//isProper 함수를 재귀적으로 사용하기 위해서 임시 tree class를 만든다
    BinaryTree tempright;

    templeft._root = _root->left;//초기화
    tempright._root = _root->right;

    if (_root->left != NULL)
    {
        left = templeft.isProper();
    }
    else
    {
        left = false;
    }

    if (_root->right != NULL)
    {
        right = tempright.isProper();
    }
    else
    {
        right = false;
    }

    if (left == right)
    {
        return true;
    }
    else
    {
        return false;
    }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////