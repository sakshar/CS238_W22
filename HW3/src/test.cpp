/*#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

int main(){
    int score;
    vector<int> temp_vec;
    int a = 45, b = 69, c = 87, d = 693, e = -34, f = 6, g = 59;
    clock_t start1 = clock();*/
/*  int cur_max = a;
    int temp[7] = {a, b, c, d, e, f, g};
    for(int l = 1; l < 7; l++){
        if(temp[l] > cur_max){
            cur_max = temp[l];
        }
    }
    score = cur_max;*/
 /* if(a >= b && a>= c) score = a;
    else if(b >= a && b >= c) score = b;
    else if(c >= a && c >= b) score = c;
    clock_t end1 = clock();
    cout<<"if-else: "<<score<<endl;
    clock_t start2 = clock();
    temp_vec.push_back(a);
    temp_vec.push_back(b);
    temp_vec.push_back(c);*/
    /*temp_vec.push_back(d);
    temp_vec.push_back(e);
    temp_vec.push_back(f);
    temp_vec.push_back(g);*/
 /* score = (int) *max_element(temp_vec.begin(), temp_vec.end());
    clock_t end2 = clock();
    cout<<"Vector: "<<score<<endl;
    cout<<"if-else: "<<end1-start1<<endl;
    cout<<"Vector: "<<end2-start2<<endl;
    cout<<"Ratio: if-else/vector: "<<1.0*(end1-start1)/(end2-start2)<<endl;
}*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

unordered_map<char, int> base_map;

int score[5][5] = {{5, -4, -4, -4, -8},
                   {-4, 5, -4, -4, -8},
                   {-4, -4, 5, -4, -8},
                   {-4, -4, -4, 5, -8},
                   {-8, -8, -8, -8, 0}};
    
string num = "4";
string input_file = "cpp_test"+num+".txt";
string output_file = "cpp_result"+num+".txt";
string x = "GCTGATATAACT";
string y = "GGGTGATTAGCT";
string z = "AGCGGAACACCT";

class Result{
    public:
    int aln_score;
    string alignment[3] = {"", "", ""};
};

int delta(char a, char b, char c){
    int i, j, k;
    i = base_map[a];
    j = base_map[b];
    k = base_map[c];
    return score[i][j] + score[j][k] + score[k][i];
}

int delta2(int i, int j, int k){
    return score[i][j] + score[j][k] + score[k][i];
}

int main(){
    base_map['A'] = 0;
    base_map['C'] = 1;
    base_map['G'] = 2;
    base_map['T'] = 3;
    base_map['-'] = 4;

    /*clock_t start1 = clock();
    cout<<"map: "<<delta('A', 'C', '-')<<endl;
    clock_t end1 = clock();
    clock_t start2 = clock();
    cout<<"direct: "<<delta2(0, 1, 4)<<endl;
    clock_t end2 = clock();
    cout<<"Map: "<<end1-start1<<endl;
    cout<<"Direct: "<<end2-start2<<endl;
    cout<<"Ratio: map/direct: "<<1.0*(end1-start1)/(end2-start2)<<endl;*/
    vector<int> x1, y1, z1;
    for(int i = 0; i < x.length(); i++)
        x1.push_back(base_map[x[i]]);
    for(int i = 0; i < y.length(); i++)
        y1.push_back(base_map[y[i]]);
    for(int i = 0; i < z.length(); i++)
        z1.push_back(base_map[z[i]]);
    
    cout<<x<<" -> "<<x.length()<<endl;
    for(int i = 0; i < x1.size(); i++)
        cout<<x1.at(i)<<",";
    cout<<endl;
    cout<<y<<" -> "<<y.length()<<endl;
    for(int i = 0; i < y1.size(); i++)
        cout<<y1.at(i)<<",";
    cout<<endl;
    cout<<z<<" -> "<<z.length()<<endl;
    for(int i = 0; i < z1.size(); i++)
        cout<<z1.at(i)<<",";
    cout<<endl;
}