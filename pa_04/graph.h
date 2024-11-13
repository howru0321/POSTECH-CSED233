#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647 
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() { };
    ~Graph() { };

    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    string DFS();
    int getTreeCount();
    string getStronglyConnectedComponent();
    string getDijkstraShortestPath(string source, string destination);
    string getFloydShortestPath(string source, string destination);
    int primMST(ofstream &, string startNode);
    int kruskalMST(ofstream &);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    string** first_array;
    int size;

    string** r_first_array;
    int r_size;

    int* pos_info;
    int* visit_info;

    int* r_pos_info;
    int* r_visit_info;

    string* SCC_info;
    int* number;

    string* node;
    int node_size;
    int* visit_node;

    void all_node(string word);
    int find_node_visit(string word);


    int SCC_size;
    int set;

    int DFS_size;

    void resize_first(string word);
    void resize_second(int pos, string word);
    int search(string word);

    void r_resize_first(string word);
    void r_resize_second(int pos, string word);
    int r_search(string word);

    void insertion_sort();

    void r_insertion_sort();

    string DFS(string word);

    string r_DFS(string word);

    int getTreeCount(string word);
    int dfs_num;

    string string_sort(string word);


    //4번
    int** weight;

    void resize_first(string word,int weight);
    void resize_second(int pos, string word,int weight);
    void w_insertion_sort();

    //string* candi;
    string find_candi(string now);
    int pos_course;

    //int find_length(string* candi, int candi_size, string word, int* length);

    ///
    int path(string destination, string* candi, int candi_size);

    int* path_length;
    string* before;

    string chu_before[102][102];
    int chu_size[102];

    //
    void count(string word, string destination, string st);
    int all_c;
    void s_path(string word);
    int s_path_size;
    string path_s[102];
    //

    int check_error;

    int b_find_node_visit(string word);

    string* all_path;//필요없을듯...?
    int all_path_size;//필요없을듯...?


    //real
    
    int matrix[102][102];

    int next[102][102];

    void adjacency();
    void w_adjacency();

    string real_node[102];

    int find_real_node(string word);


    //7qs--d
    string parent[102];

    string G1[102];
    string G2[102];
    int Gw[102];

    string T1[102];
    string T2[102];
    int Tw[102];

    int ma_size;
    int t_size;

    string find_p(string word);


    //3qjsddddddd
    //

    string before_s[102];
    string stack[102];
    int stack_size;

    void SCC_DFS(string word);
    void a_SCC_DFS(string word);

    string* SCC_real;
    int SCC_real_size;

    string realSCC;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
