#include <iostream>
#include <chrono>
#include "readcsv.h"
#include "BuildGTreeCPU.h"
#include "cudaFun.h"

using namespace std::chrono;

void printvector(const vector<vector<float> > &vec){
    cout << "<-------------------------" << endl;
    for(const auto &i: vec){
        for(const auto &j: i){
            cout << j << "\t";
        }
        cout << endl;
    }
    cout << "-------------------------->" << endl;
}

void printArray(float* arr, long size){
    cout << "--------------------------arr" << endl;
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << '\t';
    }
    cout << endl;
    cout << "--------------------------arr<" << endl;
}

void printLArray(long* arr, long size){
    cout << "--------------------------arr" << endl;
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << '\t';
    }
    cout << endl;
    cout << "--------------------------arr<" << endl;
}

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;
    string filepath(argv[1]);
    int dim, fanout;
    long k, totalsize = 0, innodes;
    fanout = atoi(argv[2]);
    auto rec = readFromCSV(filepath);
    auto t1 = high_resolution_clock::now();
    // cout << "records size: " << rec.size() << endl;
    // return 0;
    // printvector(rec);
    sortLowX(rec);
    dim = (int)rec[0].size();
    k = rec.size();
    // printvector(rec);
    long totalnodes = buildGTreeUtil(rec, fanout,dim);
    // printvector(rec);
    innodes = totalnodes - k;
    float* arr;
    vectorToArray(rec, arr, dim, k, totalsize);
    // cout << "totalsize: " << totalsize << endl;
    // cout << "totalnodes: "  << totalnodes << endl;
    // cout << "innodes: " << innodes << endl;
    // printArray(arr, totalsize);
    // long* arra = NULL; long sizes;
    float* d_arr;
    allocateArray(arr, d_arr, totalsize);
    deleteDeviceArray(d_arr, totalsize);
    delete[] arr;
    auto t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Durations ms: " << (double)duration / 1000.0 << endl;
    return 0;
}