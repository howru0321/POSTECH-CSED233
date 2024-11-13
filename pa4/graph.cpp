#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647 
using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

void Graph::count(string word, string source, string st) {
    int pos = find_node_visit(word);
    if (word == source) {
        string temp = source;
        temp += " ";
        temp += st;
        path_s[all_c] = temp;

        //cout << all_c << endl;
        //cout << temp << endl;
        all_c++;
        return;
    }
    string temp = word;
    temp += " ";
    temp += st;

    count(before[pos], source, temp);
    for (int i = 0; i < chu_size[pos] - 1; i++) {
        count(chu_before[pos][i], source, temp);
    }
}

string Graph::find_p(string word) {
    int pos = find_real_node(word);

    if (real_node[pos] == parent[pos]) {
        return word;
    }
    else {
        return find_p(parent[pos]);
    }
}

int Graph::find_real_node(string word) {
    int re = -1;
    for (int i = 0; i < node_size; i++) {
        if (real_node[i] == word) {
            re = i;
        }
    }
    return re;
}

void Graph::adjacency() {

    for (int i = 0; i < node_size; i++) {
        real_node[i] = node[i];
    }

    for (int i = 1; i < node_size; i++) {
        string temp = real_node[i];
        for (int j = i - 1; j >= 0; j--) {
            if (real_node[j].compare(temp) > 0) {
                real_node[j + 1] = real_node[j];
                real_node[j] = temp;
            }
        }
    }

    for (int i = 0; i < node_size; i++) {
        int pos = search(real_node[i]);
        if (pos == -1) {
            for (int j = 0; j < node_size; j++) {
                if (i == j) {
                    matrix[i][i] = 0;
                }
                else {
                    matrix[i][j] = INF;
                }
            }
        }
        else {

            for (int j = 0; j < node_size; j++) {
                if (i == j) {
                    matrix[i][i] = 0;
                }
                else {
                    matrix[i][j] = INF;
                }
            }

            for (int j = 1; j < pos_info[pos]; j++) {
                string temp = first_array[pos][j];
                int put = find_real_node(temp);
                matrix[i][put] = 1;
            }
        }
    }
}

void Graph::w_adjacency() {

    for (int i = 0; i < node_size; i++) {
        real_node[i] = node[i];
    }

    for (int i = 1; i < node_size; i++) {
        string temp = real_node[i];
        for (int j = i - 1; j >= 0; j--) {
            if (real_node[j].compare(temp) > 0) {
                real_node[j + 1] = real_node[j];
                real_node[j] = temp;
            }
        }
    }

    for (int i = 0; i < node_size; i++) {
        int pos = search(real_node[i]);
        if (pos == -1) {
            for (int j = 0; j < node_size; j++) {
                if (i == j) {
                    matrix[i][i] = 0;
                }
                else {
                    matrix[i][j] = INF;
                }
            }
        }
        else {

            for (int j = 0; j < node_size; j++) {
                if (i == j) {
                    matrix[i][i] = 0;
                }
                else {
                    matrix[i][j] = INF;
                }
            }

            for (int j = 1; j < pos_info[pos]; j++) {
                string temp = first_array[pos][j];
                int put = find_real_node(temp);
                matrix[i][put] = weight[pos][j - 1];
            }
        }
    }
}


int Graph::path(string destination, string* candi, int candi_size) {
    if (candi[0] == destination && candi_size == 1) {
        return 0;
    }

    bool first = false;

    for (int i = 0; i < candi_size; i++) {
        if (search(candi[i]) != -1) {
            first = true;
        }
    }

    if (first == false)
        return -1;


    int _short = INF;
    string _short_string;
    int pos_temp;
    string now_temp;
    int before_front;
    bool check_ma = false;
    for (int i = 0; i < candi_size; i++) {
        int front = search(candi[i]);
        if (front != -1) {
            for (int j = 1; j < pos_info[front]; j++) {
                int temp = find_node_visit(first_array[front][j]);
                int before_temp = find_node_visit(first_array[front][0]);
                int weight_temp = weight[front][j - 1] + path_length[before_temp];
                int check_temp = INF;
                if (path_length[temp] > weight_temp) {
                    path_length[temp] = weight_temp;
                    before[temp] = first_array[front][0];
                    //
                    chu_size[temp] = 1;

                    if (first_array[front][j] == destination) {
                        all_path_size = 1;
                        string* all_temp = new string[all_path_size];
                        for (int z = 0; z < all_path_size - 1; z++) {
                            all_temp[z] = all_path[z];
                        }
                        all_temp[all_path_size - 1] = first_array[front][0];
                        string* del_all = all_path;
                        all_path = all_temp;
                        delete[] del_all;
                    }

                    check_temp = weight_temp;
                }
                else if (path_length[temp] == weight_temp) {
                    if (first_array[front][j] == destination) {

                        bool chee = true;

                        for (int b = 0; b < all_path_size; b++) {
                            if (all_path[b] == first_array[front][0]) {
                                chee = false;
                            }
                        }

                        if (chee == true) {
                            all_path_size++;
                            string* all_temp = new string[all_path_size];
                            for (int z = 0; z < all_path_size - 1; z++) {
                                all_temp[z] = all_path[z];
                            }
                            all_temp[all_path_size - 1] = first_array[front][0];
                            string* del_all = all_path;
                            all_path = all_temp;
                            delete[] del_all;
                        }
                    }
                    //
                    else {
                        bool ccc = true;
                        for (int x = 0; x < chu_size[temp] - 1; x++) {
                            if (first_array[front][0] == chu_before[temp][x]) {
                                ccc = false;
                            }
                        }
                        if (ccc == true) {
                            chu_size[temp]++;
                            int v = chu_size[temp];
                            chu_before[temp][v - 2] = first_array[front][0];
                            //cout << first_array[front][0];
                        }
                    }
                }
                string string_temp = first_array[front][0];

                if (check_temp < _short) {
                    _short = check_temp;
                    _short_string = string_temp;
                    pos_temp = temp;

                    now_temp = first_array[front][0];

                    before_front = front;
                    check_ma = true;
                }
            }
        }
    }

    if (check_ma == false) {//한번도 최소경로가 안나왔다는 것은 지금 상태가 최소경로라는 뜻임
        return 0;
    }


    //path_length[pos_temp] = _short;
    //before[pos_temp] = _short_string;

    string* real_now_temp = new string[node_size];
    int real_now_temp_size = 0;

    for (int i = 0; i < node_size; i++) {
        if (path_length[i] == _short) {

            string tem = before[i];

            bool chh = true;
            for (int j = 0; j < real_now_temp_size; j++) {
                if (tem == real_now_temp[j]) {
                    chh = false;
                }
            }
            if (chh == true) {
                real_now_temp[real_now_temp_size] = before[i];
                real_now_temp_size++;
            }
            //
            if (chu_size[i] != 0) {
                for (int k = 0; k < chu_size[i] - 1; k++) {
                    string te = chu_before[i][k];

                    bool ch = true;
                    for (int j = 0; j < real_now_temp_size; j++) {
                        if (te == real_now_temp[j]) {
                            ch = false;
                        }
                    }
                    if (ch == true) {
                        real_now_temp[real_now_temp_size] = chu_before[i][k];
                        real_now_temp_size++;
                    }
                }
            }
        }
    }

    string* candi_temp = new string[node_size];
    int size_temp = 0;

    for (int i = 0; i < candi_size; i++) {
        bool ch = true;
        for (int j = 0; j < real_now_temp_size; j++) {
            if (candi[i] == real_now_temp[j]) {
                ch = false;
            }
        }
        if (ch == true) {
            candi_temp[size_temp] = candi[i];
            size_temp++;
        }
    }

    for (int i = 0; i < real_now_temp_size; i++) {
        int new_front = search(real_now_temp[i]);
        if (new_front != -1) {
            int new_candi = pos_info[new_front];

            for (int j = 1; j < new_candi; j++) {
                bool check = true;

                for (int z = 0; z < size_temp; z++) {
                    if (candi_temp[z] == first_array[new_front][j]) {
                        check = false;
                    }
                }

                if (check == true) {
                    candi_temp[size_temp] = first_array[new_front][j];
                    size_temp++;
                }
            }
        }
    }

    /*int new_front = search(now_temp);
    if (new_front != -1) {
        int new_candi = pos_info[new_front];

        for (int i = 1; i < new_candi; i++) {
            string temp = first_array[before_front][i];

            bool check = true;
            for (int j = 0; j < pos_temp; j++) {
                if (candi_temp[j] == temp) {
                    check = false;
                }
            }
            if (check == true) {
                candi_temp[size_temp] = temp;
                size_temp++;
            }
        }
    }*/
    delete[] candi;

    return path(destination, candi_temp, size_temp);
}

void Graph::all_node(string word) {
    if (find_node_visit(word) == -1) {
        node_size++;
        string* temp = new string[node_size];
        int* v_temp = new int[node_size] {};
        for (int i = 0; i < node_size - 1; i++) {
            temp[i] = node[i];
        }
        temp[node_size - 1] = word;
        string* delete_temp = node;
        node = temp;
        delete[] delete_temp;

        int* d_temp = visit_node;
        visit_node = v_temp;
        delete[] d_temp;
    }
}

int Graph::find_node_visit(string word) {
    int re = -1;
    for (int i = 0; i < node_size; i++) {
        if (node[i] == word) {
            re = i;
        }
    }
    return re;
}

int Graph::b_find_node_visit(string word) {
    int re = -1;
    for (int i = 0; i < node_size; i++) {
        if (before[i] == word) {
            re = i;
        }
    }
    return re;
}

void Graph::resize_first(string word) {
    size++;
    string** new_first_array = new string * [size] {};
    int* new_pos_info = new int[size] {};
    int* new_visit_info = new int [size] {};

    all_node(word);

    for (int i = 0; i < size - 1; i++) {
        new_first_array[i] = first_array[i];
        new_pos_info[i] = pos_info[i];
        new_visit_info[i] = visit_info[i];
    }
    new_first_array[size - 1] = new string[1]{};
    new_first_array[size - 1][0] = word;

    string** temp_first_array = first_array;
    first_array = new_first_array;
    delete[] temp_first_array;

    int* temp_pos_info = pos_info;
    pos_info = new_pos_info;
    delete[] temp_pos_info;

    int* temp_visit_info = visit_info;
    visit_info = new_visit_info;
    delete[] temp_visit_info;
}

void Graph::resize_first(string word,int _weight) {
    size++;
    string** new_first_array = new string * [size] {};
    int* new_pos_info = new int[size] {};
    int* new_visit_info = new int [size] {};

    int** new_weight = new int* [size] {};

    all_node(word);

    for (int i = 0; i < size - 1; i++) {
        new_first_array[i] = first_array[i];
        new_pos_info[i] = pos_info[i];
        new_visit_info[i] = visit_info[i];

        new_weight[i] = weight[i];
    }
    new_first_array[size - 1] = new string[1]{};
    new_first_array[size - 1][0] = word;

    new_weight[size - 1] = new int[1]{};
    new_weight[size - 1][0] = _weight;

    string** temp_first_array = first_array;
    first_array = new_first_array;
    delete[] temp_first_array;

    int* temp_pos_info = pos_info;
    pos_info = new_pos_info;
    delete[] temp_pos_info;

    int* temp_visit_info = visit_info;
    visit_info = new_visit_info;
    delete[] temp_visit_info;

    int** temp_weight = weight;
    weight = new_weight;
    delete[] temp_weight;
}

void Graph::r_resize_first(string word) {
    r_size++;
    string** r_new_first_array = new string * [r_size] {};
    int* r_new_pos_info = new int[r_size] {};
    int* r_new_visit_info = new int [r_size] {};

    for (int i = 0; i < r_size - 1; i++) {
        r_new_first_array[i] = r_first_array[i];
        r_new_pos_info[i] = r_pos_info[i];
        r_new_visit_info[i] = r_visit_info[i];
    }
    r_new_first_array[r_size - 1] = new string[1]{};
    r_new_first_array[r_size - 1][0] = word;

    string** r_temp_first_array = r_first_array;
    r_first_array = r_new_first_array;
    delete[] r_temp_first_array;

    int* r_temp_pos_info = r_pos_info;
    r_pos_info = r_new_pos_info;
    delete[] r_temp_pos_info;

    int* r_temp_visit_info = r_visit_info;
    r_visit_info = r_new_visit_info;
    delete[] r_temp_visit_info;
}

void Graph::resize_second(int pos, string word) {

    all_node(word);

    for (int i = 0; i < pos_info[pos]; i++) {
        if (first_array[pos][i] == word) {
            return;
        }
    }

    if (pos_info[pos] == 0)
        pos_info[pos] = 2;
    else
        pos_info[pos]++;

    string* new_temp = new string[pos_info[pos]]{};

    for (int i = 0; i < pos_info[pos] - 1; i++) {
        new_temp[i] = first_array[pos][i];
    }
    new_temp[pos_info[pos] - 1] = word;

    string* temp = first_array[pos];
    first_array[pos] = new_temp;
    delete[] temp;
}

void Graph::resize_second(int pos, string word,int _weight) {

    all_node(word);

    for (int i = 0; i < pos_info[pos]; i++) {
        if (first_array[pos][i] == word) {
            return;
        }
    }

    if (pos_info[pos] == 0)
        pos_info[pos] = 2;
    else
        pos_info[pos]++;

    string* new_temp = new string[pos_info[pos]]{};
    int* new_temp_weight = new int[pos_info[pos] - 1]{};

    for (int i = 0; i < pos_info[pos] - 1; i++) {
        new_temp[i] = first_array[pos][i];
    }
    for (int i = 0; i < pos_info[pos] - 2; i++) {
        new_temp_weight[i] = weight[pos][i];
    }
    new_temp[pos_info[pos] - 1] = word;
    new_temp_weight[pos_info[pos] - 2] = _weight;

    string* temp = first_array[pos];
    first_array[pos] = new_temp;
    delete[] temp;

    int* temp_weight = weight[pos];
    weight[pos] = new_temp_weight;
    delete[] temp_weight;//여기서 오류남
}

void Graph::r_resize_second(int pos, string word) {
    for (int i = 0; i < r_pos_info[pos]; i++) {
        if (r_first_array[pos][i] == word) {
            return;
        }
    }

    if (r_pos_info[pos] == 0)
        r_pos_info[pos] = 2;
    else
        r_pos_info[pos]++;

    string* r_new_temp = new string[r_pos_info[pos]]{};

    for (int i = 0; i < r_pos_info[pos] - 1; i++) {
        r_new_temp[i] = r_first_array[pos][i];
    }
    r_new_temp[r_pos_info[pos] - 1] = word;

    string* r_temp = r_first_array[pos];
    r_first_array[pos] = r_new_temp;
    delete[] r_temp;
}

int Graph::search(string word) {
    for (int i = 0; i < size; i++) {
        if (first_array[i][0] == word)
            return i;
    }
    return -1;
}

int Graph::r_search(string word) {
    for (int i = 0; i < r_size; i++) {
        if (r_first_array[i][0] == word)
            return i;
    }
    return -1;
}

void Graph::insertion_sort() {
    for (int i = 1; i < size; i++) {
        string* temp = first_array[i];
        int temp_pos_info = pos_info[i];
        for (int j = i - 1; j >= 0; j--) {
            if (first_array[j][0].compare(temp[0]) > 0) {
                first_array[j + 1] = first_array[j];
                first_array[j] = temp;

                pos_info[j + 1] = pos_info[j];
                pos_info[j] = temp_pos_info;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 2; i < pos_info[k]; i++) {
            string temp = first_array[k][i];
            for (int j = i - 1; j > 0; j--) {
                if (first_array[k][j].compare(temp) > 0) {
                    first_array[k][j + 1] = first_array[k][j];
                    first_array[k][j] = temp;
                }
            }
        }
    }
}

void Graph::w_insertion_sort() {
    for (int i = 1; i < size; i++) {
        string* temp = first_array[i];
        int temp_pos_info = pos_info[i];

        int* temp_weight = weight[i];
        for (int j = i - 1; j >= 0; j--) {
            if (first_array[j][0].compare(temp[0]) > 0) {
                first_array[j + 1] = first_array[j];
                first_array[j] = temp;

                pos_info[j + 1] = pos_info[j];
                pos_info[j] = temp_pos_info;

                weight[j + 1] = weight[j];
                weight[j] = temp_weight;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 2; i < pos_info[k]; i++) {
            string temp = first_array[k][i];

            int temp_weight = weight[k][i-1];
            for (int j = i - 1; j > 0; j--) {
                if (first_array[k][j].compare(temp) > 0) {
                    first_array[k][j + 1] = first_array[k][j];
                    first_array[k][j] = temp;

                    weight[k][j] = weight[k][j-1];
                    weight[k][j] = temp_weight;
                }
            }
        }
    }
}

void Graph::r_insertion_sort() {
    for (int i = 1; i < r_size; i++) {
        string* r_temp = r_first_array[i];
        int r_temp_pos_info = r_pos_info[i];
        for (int j = i - 1; j >= 0; j--) {
            if (r_first_array[j][0].compare(r_temp[0]) > 0) {
                r_first_array[j + 1] = r_first_array[j];
                r_first_array[j] = r_temp;

                r_pos_info[j + 1] = r_pos_info[j];
                r_pos_info[j] = r_temp_pos_info;
            }
        }
    }

    for (int k = 0; k < r_size; k++) {
        for (int i = 2; i < r_pos_info[k]; i++) {
            string r_temp = r_first_array[k][i];
            for (int j = i - 1; j > 0; j--) {
                if (r_first_array[k][j].compare(r_temp) > 0) {
                    r_first_array[k][j + 1] = r_first_array[k][j];
                    r_first_array[k][j] = r_temp;
                }
            }
        }
    }
}

string Graph::DFS(string word) {
    string return_string = word;
    return_string += " ";

    if (visit_info[search(word)] == 1) {
        return "";
    }
    else if (visit_node[find_node_visit(word)] == 1) {
        return "";
    }
    else{
        visit_info[search(word)] = 1;
        visit_node[find_node_visit(word)] = 1;
        for (int i = 1; i < pos_info[search(word)]; i++) {
            string temp = DFS(first_array[search(word)][i]);
            return_string += temp;
        }
    }
    return return_string;
}

void Graph::SCC_DFS(string word) {

    visit_node[find_node_visit(word)] = 1;

    if (search(word) == -1) {
        stack[stack_size] = word;
        stack_size++;
        //
        //cout << word;
        //
        return;
    }
    else {
        bool ch = false;
        for (int i = 1; i < pos_info[search(word)]; i++) {
            int p = find_node_visit(first_array[search(word)][i]);
            if (visit_node[p] != 1) {
                ch = true;
                SCC_DFS(first_array[search(word)][i]);
            }
        }

        if (ch == false) {
            stack[stack_size] = word;
            stack_size++;
            //
            //cout << word;
            //
            return;
        }

        stack[stack_size] = word;
        stack_size++;
        //
        //cout << word;
        //
    }
    return;
}

void Graph::a_SCC_DFS(string word) {
    visit_node[find_node_visit(word)] = 1;

    SCC_real_size++;
    string* real_temp = new string[SCC_real_size];
    for (int i = 0; i < SCC_real_size - 1; i++) {
        real_temp[i] = SCC_real[i];
    }
    real_temp[SCC_real_size - 1] = word;

    string* d = SCC_real;
    SCC_real = real_temp;
    if (SCC_real_size != 1) {
        delete[] d;
    }

    string re_te = "";

    int pos1 = r_search(word);

    if (pos1 == -1) {
        if (SCC_real_size == 1) {
            re_te += SCC_real[0];
            re_te += " ";

            if (re_te.length() > realSCC.length()) {
                realSCC = re_te;
            }
            else if (re_te.length() == realSCC.length()) {
                if (re_te.compare(realSCC) < 0) {
                    realSCC = re_te;
                }
            }
            delete[] SCC_real;
            SCC_real_size = 0;
        }
        return;
    }
    else {
        bool c = false;
        for (int i = 1; i < r_pos_info[pos1]; i++) {
            int p = find_node_visit(r_first_array[pos1][i]);
            if (visit_node[p] == 0) {
                c = true;
                a_SCC_DFS(r_first_array[pos1][i]);
            }
        }

        if (c == false) {
            bool cc = false;
            for (int i = 1; i < r_pos_info[pos1]; i++) {
                int p = find_node_visit(r_first_array[pos1][i]);
                string te = r_first_array[pos1][i];
                if (visit_node[p] != 0) {
                    for (int j = 0; j < SCC_real_size; j++) {
                        if (te == SCC_real[j]) {
                            cc = true;
                            for (int i = 1; i < SCC_real_size; i++) {//sort
                                string temp = SCC_real[i];
                                for (int j = i - 1; j >= 0; j--) {
                                    if (temp.compare(SCC_real[j]) < 0) {
                                        SCC_real[j + 1] = SCC_real[j];
                                        SCC_real[j] = temp;
                                    }
                                }
                            }

                            for (int i = 0; i < SCC_real_size; i++) {
                                re_te += SCC_real[i];
                                re_te += " ";
                            }
                            if (re_te.length() > realSCC.length()) {
                                realSCC = re_te;
                            }
                            else if (re_te.length() == realSCC.length()) {
                                if (re_te.compare(realSCC) < 0) {
                                    realSCC = re_te;
                                }
                            }
                            delete[] SCC_real;
                            SCC_real_size = 0;
                            return;

                        }
                    }
                }
            }
            if (cc == false || SCC_real_size == 1) {
                for (int i = 1; i < SCC_real_size; i++) {//sort
                    string temp = SCC_real[i];
                    for (int j = i - 1; j >= 0; j--) {
                        if (temp.compare(SCC_real[j]) < 0) {
                            SCC_real[j + 1] = SCC_real[j];
                            SCC_real[j] = temp;
                        }
                    }
                }

                for (int i = 0; i < SCC_real_size; i++) {
                    re_te += SCC_real[i];
                    re_te += " ";
                }
                if (re_te.length() > realSCC.length()) {
                    realSCC = re_te;
                }
                else if (re_te.length() == realSCC.length()) {
                    if (re_te.compare(realSCC) < 0) {
                        realSCC = re_te;
                    }
                }
                delete[] SCC_real;
                SCC_real_size = 0;
                return;
            }
        }
    }

    /*if (r_search(word) == -1) {
        re_te = word;

        if (re_te.length() > realSCC.length()) {
            realSCC = re_te;
        }
        else if (re_te.length() == realSCC.length()) {
            if (re_te.compare(realSCC) < 0) {
                realSCC = re_te;
            }
        }
        return;
    }
    else {
        bool c = true;
        for (int i = 0; i < SCC_real_size; i++) {
            if (SCC_real[i] == word) {
                c = false;
            }
        }

        if (c == false) {
            for (int i = 1; i < SCC_real_size; i++) {
                string temp = SCC_real[i];
                for (int j = i - 1; j >= 0; j--) {
                    if (temp.compare(SCC_real[j]) < 0) {
                        SCC_real[j + 1] = SCC_real[j];
                        SCC_real[j] = temp;
                    }
                }
            }

            for (int i = 0; i < SCC_real_size; i++) {
                re_te += SCC_real[i];
                re_te += " ";
            }
            if (re_te.length() > realSCC.length()) {
                realSCC = re_te;
            }
            else if (re_te.length() == realSCC.length()) {
                if (re_te.compare(realSCC) < 0) {
                    realSCC = re_te;
                }
            }
            delete[] SCC_real;
            SCC_real_size = 0;
            return;
        }


        bool cc = false;

        for (int i = 0; i < r_pos_info[r_search(word)]; i++) {
            if (visit_node[i] == 0) {
                cc = true;
            }
        }

        if (cc == false) {



            re_te = word;

            if (re_te.length() > realSCC.length()) {
                realSCC = re_te;
            }
            else if (re_te.length() == realSCC.length()) {
                if (re_te.compare(realSCC) < 0) {
                    realSCC = re_te;
                }
            }
            return;
        }
        else {
            for (int i = 0; i < r_pos_info[r_search(word)]; i++) {
                if (visit_node[i] == 1) {
                    
                }
            }
        }
    }*/
}

string Graph::r_DFS(string word) {
    string r_return_string = word;
    r_return_string += " ";

    if (r_visit_info[search(word)] == 1) {
        return "";
    }
    else if (visit_node[find_node_visit(word)] == 1) {
        return "";
    }
    else {
        r_visit_info[search(word)] = 1;
        visit_node[find_node_visit(word)] = 1;
        for (int i = 1; i < r_pos_info[search(word)]; i++) {
            string r_temp = r_DFS(r_first_array[search(word)][i]);
            r_return_string += r_temp;
        }
    }
    return r_return_string;
}

int Graph::getTreeCount(string word) {
    int edge = 0;
    if (visit_info[search(word)] == 1) {
        return -1;
    }
    else {
        visit_info[search(word)] = 1;
        for (int i = 1; i < pos_info[search(word)]; i++) {
            int temp = getTreeCount(first_array[search(word)][i]);
            if (temp == -1) {
                edge++;
            }
            else {
                edge += (temp + 1);
            }
        }
    }
    return edge;
}

string Graph::string_sort(string word) {
    char* temp = new char[word.length()];
    int pos = 0;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] != ' ') {
            temp[pos] = word[i];
            pos++;
        }
    }
    for (int i = 1; i < pos; i++) {
        char a = temp[i];
        for (int j = i - 1; j >= 0; j--) {
            if (temp[j] > temp[i]) {
                temp[j + 1] = temp[j];

                temp[j] = a;
            }
        }
    }
    string re = "";
    for (int i = 0; i < pos; i++) {
        re += temp[i];
        re += " ";
    }

    return re;
}

string Graph::find_candi(string now) {
    int pos_node = search(now);
    int temp = 0;
    int pos = -1;
    for (int i = 1; i < pos_info[pos_node]; i++) {
        if (visit_info[search(first_array[pos_node][i])] != 1) {
            int a = weight[pos_node][i];
            if (temp < a) {
                pos = i;
            }
        }
    }
    if (pos == -1) {
        return "\0";
    }
    return first_array[pos_node][pos];
}



///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (search(nodeA) == -1) {
        resize_first(nodeA);
        resize_second(size - 1, nodeB);
    }
    else {
        resize_second(search(nodeA), nodeB);
    }

    if (r_search(nodeB) == -1) {
        r_resize_first(nodeB);
        r_resize_second(r_size - 1, nodeA);
    }
    else {
        r_resize_second(r_search(nodeB), nodeA);
    }

    insertion_sort();
    r_insertion_sort();

    //adjacency();

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (search(nodeA) == -1) {
        resize_first(nodeA,weight);
        resize_second(size - 1, nodeB,weight);
    }
    else {
        resize_second(search(nodeA), nodeB,weight);
    }
    //w_insertion_sort();

    //w_adjacency();

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (search(nodeA) == -1) {
        resize_first(nodeA);
        resize_second(size - 1, nodeB);
    }
    else {
        resize_second(search(nodeA), nodeB);
    }

    if (search(nodeB) == -1) {
        resize_first(nodeB);
        resize_second(size - 1, nodeA);
    }
    else {
        resize_second(search(nodeB), nodeA);
    }

    insertion_sort();

    //adjacency();

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (search(nodeA) == -1) {
        resize_first(nodeA,weight);
        resize_second(size - 1, nodeB,weight);
    }
    else {
        resize_second(search(nodeA), nodeB,weight);
    }

    if (search(nodeB) == -1) {
        resize_first(nodeB,weight);
        resize_second(size - 1, nodeA,weight);
    }
    else {
        resize_second(search(nodeB), nodeA,weight);
    }

    w_insertion_sort();


    if (nodeA.compare(nodeB) < 0) {
        G1[ma_size] = nodeA;
        G2[ma_size] = nodeB;
    }
    else {
        G1[ma_size] = nodeB;
        G2[ma_size] = nodeA;
    }
    Gw[ma_size] = weight;
    ma_size++;

    for (int i = 1; i < ma_size; i++) {
        int temp = Gw[i];
        string temp1 = G1[i];
        string temp2 = G2[i];
        for (int j = i - 1; j >= 0; j--) {
            if (G1[j].compare(temp1) > 0) {
                Gw[j + 1] = Gw[j];
                Gw[j] = temp;

                G1[j + 1] = G1[j];
                G1[j] = temp1;

                G2[j + 1] = G2[j];
                G2[j] = temp2;
            }
        }
    }

    for (int i = 1; i < ma_size; i++) {
        int temp = Gw[i];
        string temp1 = G1[i];
        string temp2 = G2[i];
        for (int j = i - 1; j >= 0; j--) {
            if (Gw[j] > temp) {
                Gw[j + 1] = Gw[j];
                Gw[j] = temp;

                G1[j + 1] = G1[j];
                G1[j] = temp1;

                G2[j + 1] = G2[j];
                G2[j] = temp2;
            }
        }
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::DFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string temp = DFS(first_array[0][0]);
    if (temp[temp.length() - 1] == ' ')
        temp.pop_back();

    for (int i = 0; i < size; i++) {
        if (visit_info[i] != 1) {
            temp += "\n";
            temp += DFS(first_array[i][0]);
        }
            if (temp[temp.length() - 1] == ' ')
                temp.pop_back();
    }

    return temp;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::getTreeCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int tree = 0;

    int edge = getTreeCount(first_array[0][0]);
    int node = 0;
    for (int i = 0; i < size; i++)
        node += visit_info[i];

    if ((edge/2) + 1 == node)
        tree++;

    int temp_node = node;
    for (int i = 0; i < size; i++) {
        if (visit_info[i] != 1) {
            edge = getTreeCount(first_array[i][0]);
            node = 0;
            for (int j = 0; j < size; j++)
                node += visit_info[j];

            int temp_temp_node = temp_node;
            temp_node = node;
            node -= temp_temp_node;
            
            if ((edge/2) + 1 == node)
                tree++;
        }
    }
    
    return tree;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getStronglyConnectedComponent() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    for (int i = 1; i < node_size; i++) {
        string temp = node[i];
        for (int j = i - 1; j >= 0; j--) {
            if (node[j].compare(temp) > 0) {
                node[j + 1] = node[j];
                node[j] = temp;
            }
        }
    }
    for (int i = 0; i < node_size; i++) {
        if (visit_node[i] != 1) {
            SCC_DFS(node[i]);
        }
    }

    for (int i = 0; i < node_size; i++) {
        visit_node[i] = 0;
    }
    

    int now;

    for (int i = 0; i < stack_size; i++) {
        now = stack_size - 1 - i;
        int c = find_node_visit(stack[now]);
        if (visit_node[c] == 0) {
            a_SCC_DFS(stack[now]);
        }
    }

    if (realSCC[realSCC.length() - 1] == ' ')
        realSCC.pop_back();

    return realSCC;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getDijkstraShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    string* candi = new string[node_size]{};
    path_length = new int[node_size] {};
    for (int i = 0; i < node_size; i++) {
        path_length[i] = INF;
    }

    int posi = find_node_visit(source);
    path_length[posi] = 0;
    before = new string[node_size]{};

    candi[0] = source;
    int candi_size = 1;

    

    int ree = path(destination, candi, candi_size);

    if (ree == -1) {
        return "error";
   }


    for (int i = 0; i < all_path_size; i++) {
        count(all_path[i], source, destination);
    }

    for (int i = 1; i < all_c; i++) {
        string tempp = path_s[i];
        for (int j = i - 1; j >= 0; j--) {
            if (tempp.compare(path_s[j]) < 0) {
                path_s[j + 1] = path_s[j];
                path_s[j] = tempp;
            }
        }
    }

    string return_string_ = "";

    for (int i = 0; i < all_c; i++) {
        if (i != 0) {
            return_string_ += "\n";
        }
        return_string_ += path_s[i];
        return_string_ += " ";
        return_string_ += to_string(path_length[find_node_visit(destination)]);
    }

    /*for (int i = 0; i < all_path_size; i++) {
        if (i != 0) {
            return_string_ += "\n";
        }

        string return_string = "";
        return_string += destination;

        string _node = all_path[i];
        while (_node != source) {
            int temp = find_node_visit(_node);
            string _temp = _node;
            _temp += " ";
            _temp += return_string;
            return_string = _temp;
            _node = before[temp];
        }
        string __temp = source;
        __temp += " ";
        __temp += return_string;
        return_string = __temp;
        return_string += " ";
        return_string += to_string(path_length[find_node_visit(destination)]);
        return_string_ += return_string;
    }*/

    return return_string_;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getFloydShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    w_adjacency();

    for (int i = 0; i < node_size; i++) {
        for (int j = 0; j < node_size; j++) {
            if (matrix[i][j] == INF) {
                next[i][j] = -1;
            }
            else {
                next[i][j] = j;
            }
        }
    }

    for (int k = 0; k < node_size; k++) {
        for (int i = 0; i < node_size; i++) {
            for (int j = 0; j < node_size; j++) {
                int temp1;
                if (matrix[i][k] == INF || matrix[k][j] == INF) {
                    temp1 = INF;
                }
                else {
                    temp1 = matrix[i][k] + matrix[k][j];
                }

                if (temp1 < matrix[i][j]) {
                    matrix[i][j] = temp1;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    string re_temp = source;

    int start = find_real_node(source);
    int end = find_real_node(destination);

    int st = start;

    while (st != end) {
        st = next[st][end];

        re_temp += " ";
        re_temp += real_node[st];
    }

    re_temp += " ";

    re_temp += to_string(matrix[start][end]);

    return re_temp;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    w_adjacency();
    int edge = 0;

    bool sel[102];

    for (int i = 0; i < node_size; i++) {
        sel[i] = false;
    }

    int p = find_real_node(startNode);
    sel[p] = true;

    int x;
    int y;

    string re_temp = "";
    int total = 0;

    while (edge < node_size - 1) {


        int m = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < node_size; i++) {
            if (sel[i]) {
                for (int j = 0; j < node_size; j++) {
                    int temp = matrix[i][j];
                    if (temp == INF)
                        temp = 0;
                    if (!sel[j] && temp) {
                        if (m > matrix[i][j]) {
                            m = matrix[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        
        //re_temp += real_node[x];
        //re_temp += " ";
        //re_temp += real_node[y];
        //re_temp += " ";
        //re_temp += to_string(matrix[x][y]);

        fout << real_node[x];
        fout << " ";
        fout << real_node[y];
        fout << " ";
        fout << matrix[x][y];
        fout << "\n";

        total += matrix[x][y];

        sel[y] = true;
        edge++;
    }

    return total;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    w_adjacency();

    for (int i = 0; i < node_size; i++) {
        parent[i] = real_node[i];
    }

    string tempA;
    string tempB;

    int re_int = 0;
    for (int i = 0; i < ma_size; i++) {
        tempA = find_p(G1[i]);
        tempB = find_p(G2[i]);

        if (tempA != tempB) {
            int posA = find_real_node(tempA);
            int posB = find_real_node(tempB);

            T1[t_size] = G1[i];
            T2[t_size] = G2[i];
            Tw[t_size] = Gw[i];

            re_int += Tw[t_size];

            t_size++;

            int a = find_real_node(tempA);
            int b = find_real_node(tempB);

            parent[a] = parent[b];

        }
    }

    for (int i = 0; i < t_size; i++) {
        fout << T1[i];
        fout << " ";
        fout << T2[i];
        fout << " ";
        fout << Tw[i];
        fout << "\n";
    }

    return re_int;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}