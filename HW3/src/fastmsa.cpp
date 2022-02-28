#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

unordered_map<char, int> base_map;

int score[5][5]; /* = {{5, -4, -4, -4, -8},
                   {-4, 5, -4, -4, -8},
                   {-4, -4, 5, -4, -8},
                   {-4, -4, -4, 5, -8},
                   {-8, -8, -8, -8, 0}};*/
    
//string num = "5";
//string input_file = "cpp_test"+num+".txt";
//string output_file = "fast_cpp_result"+num+".txt";
string x = "";//"GCTGATATAACT";
string y = "";//"GGGTGATTAGCT";
string z = "";//"AGCGGAACACCT";

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

int delta_direct(int i, int j, int k){
    return score[i][j] + score[j][k] + score[k][i];
}

void backtracer(int trace_matrix[], string * alignment, int start_x, int end_x, int start_y, int end_y, int start_z, int end_z, int n_, int p_){
    int i, j, k, ind;
    i = end_x - start_x;
    j = end_y - start_y;
    k = end_z - start_z;
    ind = (i*(n_)*(p_))+(j*(p_))+k;
    if(i == 0 && j == 0 && k == 0){
        return; //alignment;
    }
    if(i == 0 && j == 0){
        alignment[0] = alignment[0] + string(k, '-');
        alignment[1] = alignment[1] + string(k, '-');
        alignment[2] = alignment[2] + z.substr(start_z, k);
        return; //alignment;
    }
    if(j == 0 && k == 0){
        //cout<<"Here.... "<<start_x<<", "<<end_x<<", "<<alignment[0]<<", "<<x.substr(start_x, end_x)<<", ";
        alignment[0] = alignment[0] + x.substr(start_x, i);
        alignment[1] = alignment[1] + string(i, '-');
        alignment[2] = alignment[2] + string(i, '-');
        //cout<<alignment[0]<<endl;
        return; //alignment;
    }
    if(i == 0 && k == 0){
        alignment[0] = alignment[0] + string(j, '-');
        alignment[1] = alignment[1] + y.substr(start_y, j);
        alignment[2] = alignment[2] + string(j, '-');
        return; //alignment;
    }
    if(i==0){
        if(trace_matrix[ind] == 3){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y-1, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + z[end_z - 1];
        }
        else if(trace_matrix[ind] == 6){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y-1, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 7){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + z[end_z - 1];
        }
    }
    else if(j==0){
        if(trace_matrix[ind] == 4){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + x[end_x - 1];
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + z[end_z - 1];
        }
        else if(trace_matrix[ind] == 5){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + x[end_x-1];
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 7){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + z[end_z - 1];
        }
    }
    else if(k==0){
        if(trace_matrix[ind] == 2){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y-1, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + x[end_x - 1];
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 5){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + x[end_x-1];
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 6){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y-1, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + "-";
        }
    }
    else{
        if(trace_matrix[ind] == 1){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y-1, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + x[end_x - 1];
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + z[end_z - 1];
        }
        else if(trace_matrix[ind] == 2){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y-1, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + x[end_x - 1];
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 3){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y-1, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + z[end_z - 1];
        }
        else if(trace_matrix[ind] == 4){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + x[end_x - 1];
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + z[end_z - 1];
        }
        else if(trace_matrix[ind] == 5){
            backtracer(trace_matrix, alignment, start_x, end_x-1, start_y, end_y, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + x[end_x - 1];
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 6){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y-1, start_z, end_z, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + y[end_y - 1];
            alignment[2] = alignment[2] + "-";
        }
        else if(trace_matrix[ind] == 7){
            backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y, start_z, end_z-1, n_, p_);
            alignment[0] = alignment[0] + "-";
            alignment[1] = alignment[1] + "-";
            alignment[2] = alignment[2] + z[end_z - 1];
        }
    }
}


Result * basic_3Dalignment(int start_x, int end_x, int start_y, int end_y, int start_z, int end_z){
    Result * result = new Result(); 
    int m, n, p;
    m = end_x - start_x;
    n = end_y - start_y;
    p = end_z - start_z;
    string x_ = x.substr(start_x, m);
    string y_ = y.substr(start_y, n);
    string z_ = z.substr(start_z, p);
    int score_matrix[m+1][n+1][p+1];
    //int trace_matrix[m+1][n+1][p+1];
    int flatten_trace[(m+1)*(n+1)*(p+1)];
    int cube_diag, face_ij, face_jk, face_ki, edge_i, edge_j, edge_k;
    score_matrix[0][0][0] = 0;
    //trace_matrix[0][0][0] = 0;
    flatten_trace[0] = 0;
    for(int i = 1; i <= m; i++){
        score_matrix[i][0][0] = score_matrix[i-1][0][0] + delta(x_[i-1], '-', '-');
        //trace_matrix[i][0][0] = 5;
        flatten_trace[i*(n+1)*(p+1)] = 5;
    }
    for(int j = 1; j <= n; j++){
        score_matrix[0][j][0] = score_matrix[0][j-1][0] + delta('-', y_[j-1], '-');
        //trace_matrix[0][j][0] = 6;
        flatten_trace[j*(p+1)] = 6;
    }
    for(int k = 1; k <= p; k++){
        score_matrix[0][0][k] = score_matrix[0][0][k-1] + delta('-', '-', z_[k-1]);
        //trace_matrix[0][0][k] = 7;
        flatten_trace[k] = 7;
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            face_ij = score_matrix[i-1][j-1][0] + delta(x_[i-1], y_[j-1], '-'); //2
            edge_i = score_matrix[i-1][j][0] + delta(x_[i-1], '-', '-'); //5
            edge_j = score_matrix[i][j-1][0] + delta('-', y_[j-1], '-'); //6
            if(face_ij >= edge_i && face_ij >= edge_j){
                score_matrix[i][j][0] = face_ij;
                //trace_matrix[i][j][0] = 2;
                flatten_trace[i*(n+1)*(p+1)+j*(p+1)] = 2;
            }
            else if(edge_i >= face_ij && edge_i >= edge_j){
                score_matrix[i][j][0] = edge_i;
                //trace_matrix[i][j][0] = 5;
                flatten_trace[i*(n+1)*(p+1)+j*(p+1)] = 5;
            }
            else if(edge_j >= face_ij && edge_j >= edge_i){
                score_matrix[i][j][0] = edge_j;
                //trace_matrix[i][j][0] = 6;
                flatten_trace[i*(n+1)*(p+1)+j*(p+1)] = 6;
            }
        }
    }
    for(int j = 1; j <= n; j++){
        for(int k = 1; k <= p; k++){
            face_jk = score_matrix[0][j-1][k-1] + delta('-', y_[j-1], z_[k-1]); //3
            edge_j = score_matrix[0][j-1][k] + delta('-', y_[j-1], '-'); //6
            edge_k = score_matrix[0][j][k-1] + delta('-', '-', z_[k-1]); //7
            if(face_jk >= edge_j && face_jk >= edge_k){
                score_matrix[0][j][k] = face_jk;
                //trace_matrix[0][j][k] = 3;
                flatten_trace[j*(p+1)+k] = 3;
            }
            else if(edge_j >= face_jk && edge_j >= edge_k){
                score_matrix[0][j][k] = edge_j;
                //trace_matrix[0][j][k] = 6;
                flatten_trace[j*(p+1)+k] = 6;
            }
            else if(edge_k >= face_jk && edge_k >= edge_j){
                score_matrix[0][j][k] = edge_k;
                //trace_matrix[0][j][k] = 7;
                flatten_trace[j*(p+1)+k] = 7;
            }
        }
    }
    for(int k = 1; k <= p; k++){
        for(int i = 1; i <= m; i++){
            face_ki = score_matrix[i-1][0][k-1] + delta(x_[i-1], '-', z_[k-1]); //4
            edge_i = score_matrix[i-1][0][k] + delta(x_[i-1], '-', '-'); //5
            edge_k = score_matrix[i][0][k-1] + delta('-', '-', z_[k-1]); //7
            if(face_ki >= edge_i && face_ki >= edge_k){
                score_matrix[i][0][k] = face_jk;
                //trace_matrix[i][0][k] = 4; 
                flatten_trace[i*(n+1)*(p+1)+k] = 4;
            }
            else if(edge_i >= face_ki && edge_i >= edge_k){
                score_matrix[i][0][k] = edge_i;
                //trace_matrix[i][0][k] = 5;
                flatten_trace[i*(n+1)*(p+1)+k] = 5;
            }
            else if(edge_k >= face_ki && edge_k >= edge_i){
                score_matrix[i][0][k] = edge_k;
                //trace_matrix[i][0][k] = 7;
                flatten_trace[i*(n+1)*(p+1)+k] = 7;
            }
        }
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= p; k++){
                cube_diag = score_matrix[i-1][j-1][k-1] + delta(x_[i-1], y_[j-1], z_[k-1]); //1
                face_ij = score_matrix[i-1][j-1][k] + delta(x_[i-1], y_[j-1], '-'); //2
                face_jk = score_matrix[i][j-1][k-1] + delta('-', y_[j-1], z_[k-1]); //3
                face_ki = score_matrix[i-1][j][k-1] + delta(x_[i-1], '-', z_[k-1]); //4
                edge_i = score_matrix[i-1][j][k] + delta(x_[i-1], '-', '-'); //5
                edge_j = score_matrix[i][j-1][k] + delta('-', y_[j-1], '-'); //6
                edge_k = score_matrix[i][j][k-1] + delta('-', '-', z_[k-1]); //7
                int ind = 0, cur_max = cube_diag;
                int temp[7] = {cube_diag, face_ij, face_jk, face_ki, edge_i, edge_j, edge_k};
                for(int l = 1; l < 7; l++){
                    if(temp[l] > cur_max){
                        ind = l;
                        cur_max = temp[l];
                    }
                }
                score_matrix[i][j][k] = cur_max;
                //trace_matrix[i][j][k] = ind + 1;
                flatten_trace[i*(n+1)*(p+1)+j*(p+1)+k] = ind + 1;
            }
        }
    }
    result->aln_score = score_matrix[m][n][p];
    backtracer(flatten_trace, result->alignment, start_x, end_x, start_y, end_y, start_z, end_z, n+1, p+1);
    return result;
}

int ** scoring_prefix(int start_x, int end_x, int start_y, int end_y, int start_z, int end_z, vector<int> x1, vector<int> y1, vector<int> z1){
    int m, n, p, cube_diag, face_ij, face_jk, face_ki, edge_i, edge_j, edge_k;
    m = end_x - start_x;
    n = end_y - start_y;
    p = end_z - start_z;
    int ** score_0;
    int ** score_1;
    score_0 = new int*[n+1];
    score_1 = new int*[n+1];
    for(int j = 0; j <= n; j++){
        score_0[j] = new int[p+1];
        score_1[j] = new int[p+1];
    }
    score_0[0][0] = 0;
    //score_1[0][0] = delta(x[start_x], '-', '-');
    for(int j = 1; j <= n; j++)
        score_0[j][0] = score_0[j-1][0] + delta_direct(4, y1[start_y + j - 1], 4);
    for(int k = 1; k <= p; k++)
        score_0[0][k] = score_0[0][k-1] + delta_direct(4, 4, z1[start_z + k - 1]);
    for(int j = 1; j <= n; j++){
        for(int k = 1; k <= p; k++){
            face_jk = score_0[j-1][k-1] + delta_direct(4, y1[start_y + j - 1], z1[start_z + k - 1]); //3
            edge_j = score_0[j-1][k] + delta_direct(4, y1[start_y + j - 1], 4); //6
            edge_k = score_0[j][k-1] + delta_direct(4, 4, z1[start_z + k - 1]); //7
            if(face_jk >= edge_j && face_jk >= edge_k){
                score_0[j][k] = face_jk;
            }
            else if(edge_j >= face_jk && edge_j >= edge_k){
                score_0[j][k] = edge_j;
            }
            else if(edge_k >= face_jk && edge_k >= edge_j){
                score_0[j][k] = edge_k;
            }
        }
    }
    for(int i = 1; i <= m; i++){
        score_1[0][0] = score_0[0][0] + delta_direct(x1[start_x + i - 1], 4, 4);
        for(int j = 1; j <= n; j++){
            face_ij = score_0[j-1][0] + delta_direct(x1[start_x + i - 1], y1[start_y + j - 1], 4);
            edge_i = score_0[j][0] + delta_direct(x1[start_x + i - 1], 4, 4);
            edge_j = score_1[j-1][0] + delta_direct(4, y1[start_y + j - 1], 4);
            if(face_ij >= edge_i && face_ij >= edge_j){
                score_1[j][0] = face_ij;
            }
            else if(edge_i >= face_ij && edge_i >= edge_j){
                score_1[j][0] = edge_i;
            }
            else if(edge_j >= face_ij && edge_j >= edge_i){
                score_1[j][0] = edge_j;
            }
        }
        for(int k = 1; k <= p; k++){
            face_ki = score_0[0][k-1] + delta_direct(x1[start_x + i - 1], 4, z1[start_z + k - 1]);
            edge_k = score_1[0][k-1] + delta_direct(4, 4, z1[start_z + k - 1]);
            edge_i = score_0[0][k] + delta_direct(x1[start_x + i - 1], 4, 4);
            if(face_ki >= edge_k && face_ki >= edge_i){
                score_1[0][k] = face_ki;
            }
            else if(edge_k >= face_ki && edge_k >= edge_i){
                score_1[0][k] = edge_k;
            }
            else if(edge_i >= face_ki && edge_i >= edge_k){
                score_1[0][k] = edge_i;
            }
        }
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= p; k++){
                cube_diag = score_0[j-1][k-1] + delta_direct(x1[start_x + i - 1], y1[start_y + j - 1], z1[start_z + k - 1]);
                face_ij = score_0[j-1][k] + delta_direct(x1[start_x + i - 1], y1[start_y + j - 1], 4);
                face_jk = score_1[j-1][k-1] + delta_direct(4, y1[start_y + j - 1], z1[start_z + k - 1]);
                face_ki = score_0[j][k-1] + delta_direct(x1[start_x + i - 1], 4, z1[start_z + k - 1]);
                edge_i = score_0[j][k] + delta_direct(x1[start_x + i - 1], 4, 4);
                edge_j = score_1[j-1][k] + delta_direct(4, y1[start_y + j - 1], 4);
                edge_k = score_1[j][k-1] + delta_direct(4, 4, z1[start_z + k - 1]);
                int cur_max = cube_diag;
                int temp[7] = {cube_diag, face_ij, face_jk, face_ki, edge_i, edge_j, edge_k};
                for(int l = 1; l < 7; l++){
                    if(temp[l] > cur_max){
                        cur_max = temp[l];
                    }
                }
                score_1[j][k] = cur_max;
            }
        }
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= p; k++)
                score_0[j][k] = score_1[j][k];
        }
    }
    return score_0;
}

int ** scoring_suffix(int start_x, int end_x, int start_y, int end_y, int start_z, int end_z, vector<int> x1, vector<int> y1, vector<int> z1){
    int m, n, p, cube_diag, face_ij, face_jk, face_ki, edge_i, edge_j, edge_k;
    m = end_x - start_x;
    n = end_y - start_y;
    p = end_z - start_z;
    int ** score_0;
    int ** score_1;
    score_0 = new int*[n+1];
    score_1 = new int*[n+1];
    for(int j = 0; j <= n; j++){
        score_0[j] = new int[p+1];
        score_1[j] = new int[p+1];
    }
    score_0[0][0] = 0;
    //score_1[0][0] = delta(x[end_x - 1], '-', '-');
    for(int j = 1; j <= n; j++)
        score_0[j][0] = score_0[j-1][0] + delta_direct(4, y1[end_y - j], 4);
    for(int k = 1; k <= p; k++)
        score_0[0][k] = score_0[0][k-1] + delta_direct(4, 4, z1[end_z - k]);
    for(int j = 1; j <= n; j++){
        for(int k = 1; k <= p; k++){
            face_jk = score_0[j-1][k-1] + delta_direct(4, y1[end_y - j], z1[end_z - k]); //3
            edge_j = score_0[j-1][k] + delta_direct(4, y1[end_y - j], 4); //6
            edge_k = score_0[j][k-1] + delta_direct(4, 4, z1[end_z - k]); //7
            if(face_jk >= edge_j && face_jk >= edge_k){
                score_0[j][k] = face_jk;
            }
            else if(edge_j >= face_jk && edge_j >= edge_k){
                score_0[j][k] = edge_j;
            }
            else if(edge_k >= face_jk && edge_k >= edge_j){
                score_0[j][k] = edge_k;
            }
        }
    }
    for(int i = 1; i <= m; i++){
        score_1[0][0] = score_0[0][0] + delta_direct(x1[end_x - i], 4, 4);
        for(int j = 1; j <= n; j++){
            face_ij = score_0[j-1][0] + delta_direct(x1[end_x - i], y1[end_y - j], 4);
            edge_i = score_0[j][0] + delta_direct(x1[end_x - i], 4, 4);
            edge_j = score_1[j-1][0] + delta_direct(4, y1[end_y - j], 4);
            if(face_ij >= edge_i && face_ij >= edge_j){
                score_1[j][0] = face_ij;
            }
            else if(edge_i >= face_ij && edge_i >= edge_j){
                score_1[j][0] = edge_i;
            }
            else if(edge_j >= face_ij && edge_j >= edge_i){
                score_1[j][0] = edge_j;
            }
        }
        for(int k = 1; k <= p; k++){
            face_ki = score_0[0][k-1] + delta_direct(x1[end_x - i], 4, z1[end_z - k]);
            edge_k = score_1[0][k-1] + delta_direct(4, 4, z1[end_z - k]);
            edge_i = score_0[0][k] + delta_direct(x1[end_x - i], 4, 4);
            if(face_ki >= edge_k && face_ki >= edge_i){
                score_1[0][k] = face_ki;
            }
            else if(edge_k >= face_ki && edge_k >= edge_i){
                score_1[0][k] = edge_k;
            }
            else if(edge_i >= face_ki && edge_i >= edge_k){
                score_1[0][k] = edge_i;
            }
        }
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= p; k++){
                cube_diag = score_0[j-1][k-1] + delta_direct(x1[end_x - i], y1[end_y - j], z1[end_z - k]);
                face_ij = score_0[j-1][k] + delta_direct(x1[end_x - i], y1[end_y - j], 4);
                face_jk = score_1[j-1][k-1] + delta_direct(4, y1[end_y - j], z1[end_z - k]);
                face_ki = score_0[j][k-1] + delta_direct(x1[end_x - i], 4, z1[end_z - k]);
                edge_i = score_0[j][k] + delta_direct(x1[end_x - i], 4, 4);
                edge_j = score_1[j-1][k] + delta_direct(4, y1[end_y - j], 4);
                edge_k = score_1[j][k-1] + delta_direct(4, 4, z1[end_z - k]);
                int cur_max = cube_diag;
                int temp[7] = {cube_diag, face_ij, face_jk, face_ki, edge_i, edge_j, edge_k};
                for(int l = 1; l < 7; l++){
                    if(temp[l] > cur_max){
                        cur_max = temp[l];
                    }
                }
                score_1[j][k] = cur_max;
            }
        }
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= p; k++)
                score_0[j][k] = score_1[j][k];
        }
    }
    return score_0;
}

Result * optimalAlignment3D(int start_x, int end_x, int start_y, int end_y, int start_z, int end_z, vector<int> x1, vector<int> y1, vector<int> z1){
    int m, n, p;
    m = end_x - start_x;
    n = end_y - start_y;
    p = end_z - start_z;
    cout<<start_x<<", "<<end_x<<", "<<start_y<<", "<<end_y<<", "<<start_z<<", "<<end_z<<endl;
    if(m == 1)
        return basic_3Dalignment(start_x, end_x, start_y, end_y, start_z, end_z);
    Result *res1_, *res2_, *res;
    int ** pre = scoring_prefix(start_x, start_x + int(m / 2), start_y, end_y, start_z, end_z, x1, y1, z1);
    int ** suf = scoring_suffix(start_x + int(m / 2), end_x, start_y, end_y, start_z, end_z, x1, y1, z1);
    int max_j = -1, max_k = -1, cur_max = -99999999;
    int temp;
    for(int j = 0; j <= n; j++){
        for(int k = 0; k <= p; k++){
            temp = pre[j][k] + suf[n-j][p-k];
            if(temp > cur_max){
                cur_max = temp;
                max_j = j;
                max_k = k;
            }
        }
    }
    int y_section = start_y + max_j;
    int z_section = start_z + max_k;
    res1_ = optimalAlignment3D(start_x, start_x + int(m / 2), start_y, y_section, start_z, z_section, x1, y1, z1);
    res2_ = optimalAlignment3D(start_x + int(m / 2), end_x, y_section, end_y, z_section, end_z, x1, y1, z1);
    res = new Result();
    res->aln_score = res1_->aln_score + res2_->aln_score;
    res->alignment[0] = res1_->alignment[0] + res2_->alignment[0];
    res->alignment[1] = res1_->alignment[1] + res2_->alignment[1];
    res->alignment[2] = res1_->alignment[2] + res2_->alignment[2];
    return res;
}

int main(int argc, char *argv[]){
    base_map['A'] = 0;
    base_map['C'] = 1;
    base_map['G'] = 2;
    base_map['T'] = 3;
    base_map['-'] = 4;

    /*Result * res1 = basic_3Dalignment(0, x.length(), 0, y.length(), 0, z.length());
    cout<<res1->aln_score<<endl;
    cout<<res1->alignment[0]<<endl;
    cout<<res1->alignment[1]<<endl;
    cout<<res1->alignment[2]<<endl;*/

    //string seq[3] = {"", "", ""};
    ifstream infile(argv[1]);
    if(infile.is_open()){
        string line;
        getline(infile, line);
        x = line;
        getline(infile, line);
        y = line;
        getline(infile, line);
        z = line;
        infile.close();
    }
    cout<<"Strings: "<<x.length()<<", "<<y.length()<<", "<<z.length()<<endl;
    vector<int> x1(x.length());
    vector<int> y1(y.length());
    vector<int> z1(z.length());
    // encoding string of A,C,G,T to vector of 0,1,2,3
    for(int i = 0; i < x.length(); i++)
        x1[i] = base_map[x[i]];
    for(int i = 0; i < y.length(); i++)
        y1[i] = base_map[y[i]];
    for(int i = 0; i < z.length(); i++)
        z1[i] = base_map[z[i]];
    cout<<"Vectors: "<<x1.size()<<", "<<y1.size()<<", "<<z1.size()<<endl;

    ifstream scorefile(argv[3]);
    if(scorefile.is_open()){
        string line, val;
        int i = 0;
        while(getline(scorefile, line)){
            stringstream str(line);
            int j = 0;
            while(getline(str, val, ',')){
                score[i][j] = stoi(val);
                j++;
            }
            i++;
        }
    }
    scorefile.close();

    clock_t start = clock();
    Result * res2 = optimalAlignment3D(0, x.length(), 0, y.length(), 0, z.length(), x1, y1, z1);
    clock_t end = clock();
    cout<<"Optimal alignment score: "<<res2->aln_score<<endl;
    for(int h = 0; h < 3; h++){
        cout<<"Length: "<<res2->alignment[h].length()<<" -> "<<res2->alignment[h].substr(0, 10)<<"...\n";
    }
    int aln_length = res2->alignment[0].length();
    int match = 0;
    for(int h = 0; h < aln_length; h++){
        if(res2->alignment[0][h] == res2->alignment[1][h] && res2->alignment[0][h] == res2->alignment[2][h])
            match++;
    }
    cout<<"Perfectly matched nucleotides: "<<match<<endl;
    double run_time = (1.0*(end - start)/CLOCKS_PER_SEC);
    cout<<"Runtime (seconds): "<<run_time<<endl;
    ofstream outfile(argv[2]);
    outfile<<"Optimal alignment score: "<<res2->aln_score<<endl;
    outfile<<"Length of the alignment: "<<aln_length<<endl;
    outfile<<"Perfectly matched nucleotides: "<<match<<endl;
    outfile<<"Runtime (seconds): "<<run_time<<endl;
    outfile<<"Actual aligned sequences:\n";
    for(int h = 0; h < 3; h++){
        outfile<<res2->alignment[h]<<endl;
    }
    outfile.close();
}