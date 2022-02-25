#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream infile("fast_cpp_result5.txt");
    string x, y, z;
    if(infile.is_open()){
        string line;
        for(int i = 0; i < 6; i++)
            getline(infile, line);
        getline(infile, x);
        getline(infile, y);
        getline(infile, z);
        infile.close();
    }
    int len = x.length();
    bool flag = false;
    vector <int> pos;
    string conserve = "";
    for(int i  = 0; i < len; i++){
        if(x[i] == y[i] && x[i] == z[i]){
            conserve += "*";
            if(!flag){
                pos.push_back(i);
                flag = true;
            }
        }
        else{
            conserve += " ";
            if(flag){
                pos.push_back(i-1);
                flag = false;
            }
        }
    }
    ofstream outfile("conserve_test5.txt");
    outfile<<x<<endl;
    outfile<<y<<endl;
    outfile<<z<<endl;
    outfile<<conserve<<endl;
    flag = false;
    for (int i = 0; i < pos.size(); i++) {
        if(!flag){
            outfile<<"("<<pos[i]<<", ";
            flag = true;
        }
        else{
            outfile<<pos[i]<<")\n";
            flag = false;
        }
    }
    if(flag) outfile<<x.length()-1<<")"<<endl;
    else outfile<<endl;
    outfile.close();
}