//
// Created by achavez on 6/28/18.
//

#include "readcsv.h"

float stringToFloat(const string &strf){
    return stof(strf);
}

vector<float> readline(const string &csvline){
    vector<float> vec;
    if(csvline.length() == 0) return vec;
    string pb = "";
    for (char i : csvline) {
        if(i != ',') pb += i;
        else {
            vec.push_back(stringToFloat(pb));
            pb = "";
        }
    }
    vec.push_back(stringToFloat(pb));
    return vec;
}

vector<vector< float> > readFromCSV(string filepath){
    ifstream csvfile(filepath);
    string csvline;
    vector<vector<float> > ans;
    while(!csvfile.eof()){
        // cout << "read" << endl;
        getline(csvfile, csvline);
        // cout << "csvline: " << csvline << endl;
        if(csvline.length() == 0) continue;
        if(csvline[csvline.length() - 1] == '\r')csvline.pop_back();
        ans.push_back(readline(csvline));
    }
    csvfile.close();
    return ans;
}