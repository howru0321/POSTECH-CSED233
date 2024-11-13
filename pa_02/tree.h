#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder();
  string postOrder();
  string inOrder();
  int getDepth(int node_value);
  bool isProper();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  int checkposition = 0;//재귀함수를 쓸때 위치를 확인하기 위한 변수. _root->value가 실제 root값이면 0, 밑의 작은 tree에서는 1로 설정했다.
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};