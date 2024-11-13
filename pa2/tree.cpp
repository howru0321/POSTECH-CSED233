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
    BinaryTree templeft;//preOrder �Լ��� ��������� ����ϱ� ���ؼ� �ӽ� tree class�� �����
    BinaryTree tempright;

    templeft._root = _root->left;//�ʱ�ȭ
    tempright._root = _root->right;

    temp += _root->value;
    temp += " ";
    if (_root->left != NULL)//�� ���� ���� ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        temp += templeft.preOrder();
        temp += " ";
    }
    if (_root->right != NULL)//�� ���� ������ ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        temp += tempright.preOrder();
        temp += " ";
    }

    temp.pop_back();//������ ���� ����

    return temp;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string temp = "";
    BinaryTree templeft;//postOrder �Լ��� ��������� ����ϱ� ���ؼ� �ӽ� tree class�� �����
    BinaryTree tempright;

    templeft._root = _root->left;//�ʱ�ȭ
    tempright._root = _root->right;

    if (_root->left != NULL)//�� ���� ���� ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        temp += templeft.postOrder();
        temp += " ";
    }
    if (_root->right != NULL)//�� ���� ������ ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        temp += tempright.postOrder();
        temp += " ";
    }
    temp += _root->value;
    temp += " ";

    temp.pop_back();//������ ���� ����

    return temp;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string temp = "";
    BinaryTree templeft;//inOrder �Լ��� ��������� ����ϱ� ���ؼ� �ӽ� tree class�� �����
    BinaryTree tempright;

    templeft._root = _root->left;//�ʱ�ȭ
    tempright._root = _root->right;

    if (_root->left != NULL)//�� ���� ���� ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        temp += templeft.inOrder();
        temp += " ";
    }
    temp += _root->value;
    temp += " ";
    if (_root->right != NULL)//�� ���� ������ ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        temp += tempright.inOrder();
        temp += " ";
    }

    temp.pop_back();//������ ���� ����

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

    BinaryTree templeft;//getDepth �Լ��� ��������� ����ϱ� ���ؼ� �ӽ� tree class�� �����
    BinaryTree tempright;

    templeft._root = _root->left;//�ʱ�ȭ
    templeft.checkposition = 1;
    tempright._root = _root->right;
    tempright.checkposition = 1;

    int num = _root->value - '0';
    if (num == node_value)//���ϴ� ���� ã�� ��� temp�� 1�� �ٲ۴�
    {
        temp = 1;
    }


    if (_root->left != NULL)//�� ���� ���� ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        left=templeft.getDepth(node_value);
    }
    if (_root->right != NULL)//�� ���� ������ ���� ���ٴ� ���̹Ƿ�, ��͸� ���̻� �������� �ʴ´�
    {
        right = tempright.getDepth(node_value);
    }
    if (left + right != 0)//left right children �� �Ѵ� 0�� �ƴϸ鼭 value�� ���ϴ� ���� �����°��� ����. ���ϴ� ���� �ϳ��̱� �����̴�. �׷��� ���� left+right!=�� ���� temp=0�̹Ƿ� left+right+1���� ������ �ȴ�.
    {
        temp = (left + right + 1);
    }
    
    if (this->checkposition == 0 && temp == 0)//Traversal�� �Ϸ��������� temp�� 0�̶��, ã�� ���� �����Ƿ� -1�� �����Ѵ�
    {
        return -1;
    }
    else if (this->checkposition == 0 && temp != 0)//Traversal �Ϸ��ϰ� ���ϴ� ���� ã�� ���. �� ���� ó�� temp ������ 1�� �����Ƿ�, ���������� root�� ���������� temp�� depth���� 1�� Ŭ ���̴�.(root�� depth�� 1�� �ƴ϶� 0�̱⶧��) ���� �� ��쿡�� tmep-1�� �����ؾ��Ѵ�
    {
        return temp - 1;
    }
    else//Traversal �� �Ϸ����� ���� ���
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
    
    BinaryTree templeft;//isProper �Լ��� ��������� ����ϱ� ���ؼ� �ӽ� tree class�� �����
    BinaryTree tempright;

    templeft._root = _root->left;//�ʱ�ȭ
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