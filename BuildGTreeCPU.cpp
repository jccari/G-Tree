//
// Created by achavez on 6/28/18.
//

#include "BuildGTreeCPU.h"

bool sortLowxBoolean(const vector<float> &v1, const vector<float> &v2){
    return v1[0] < v2[0];
}

void sortLowX(vector<vector<float>> &nodes){
    sort(nodes.begin(), nodes.end(), sortLowxBoolean);
}



long buildGTreeUtil(vector<vector<float> > &nodes, int fanout, int dim){
    long total = nodes.size();
    buildFirstNodes(nodes, fanout, dim);
    total += total / fanout;
    cout << nodes[nodes.size() - 1].size() << endl;
    while(nodes[nodes.size() - 1].size() > 2 * dim){
        total += nodes[nodes.size() - 1].size()/ (fanout * 2 * dim);
        buildGTree(nodes, fanout, dim);
    }
    return total;
}

void vectorToArray(vector<vector<float> > &nodes, float *&arr, int dim, long k, long &totalsize){
    totalsize = k * dim;
    // cout << "k*dim" << k*dim << endl;
    for (long j = k; j < nodes.size(); ++j) {
        totalsize += nodes[j].size();
    }
    arr = new float[totalsize];
    int pos = 0;
    for (long i = nodes.size() - 1; i > k - 1; --i) {
        for (float j : nodes[i]) {
            arr[pos] = j;
            ++pos;
        }
    }
    for (int l = 0; l < k; ++l) {
        for (int i = 0; i < dim; ++i) {
            arr[pos] = nodes[l][i];
            ++pos;
        }
    }
}

void children(long idx, long *&arr, int fanout, long totalnodes){
    arr = new long[fanout];
    for (int i = 0; i < fanout; ++i) {
        arr[i] = idx * fanout + i + 1;
        if(arr[i] >= totalnodes)arr[i] = -1;
    }
}

long parent(long i, int fanout){
    return (long)ceil((double)(i)/(double)(fanout)) - 1;
}

long ini(long idx, long totalsize, long k, long fanout, int dim, long innodes, long totalnodes){
    // cout << "innodes: " << innodes << endl;
    if(idx >= innodes){
        long offset = innodes * 2 * dim;
        offset += (idx - innodes) * dim;
        return offset;
    }
    else{
        return idx * 2 * dim;
    }
}

long fin(long idx, long totalsize, long k, long fanout, int dim, long innodes, long totalnodes){
    if(idx >= innodes){
        return ini(idx, totalsize, k, fanout, dim, innodes, totalnodes) + dim - 1;
    }
    else{
        return ini(idx, totalsize, k, fanout, dim, innodes, totalnodes) + 2 * dim - 1;
    }
}

bool isInternalNode(int idx, int totalnodes, int innodes){
    if(idx >= innodes)return false;
    else return true;
}

void buildGTree(vector<vector<float> > &nodes, int fanout, int dim){
    long ini, fin;
    vector<float>vec;
    for(long i = 0; i < nodes[nodes.size() - 1].size(); i += fanout * 2 * dim){
        ini = i;
        fin = i + fanout * 2 * dim - 1;
        float minimo = FLT_MAX, maximo = FLT_MIN;
        long padding = 2 * dim;
        for(long d = 0; d < dim; ++d){
            minimo = FLT_MAX, maximo = FLT_MIN;
            for(long j = ini + d * 2; j <= fin; j+=padding){
                // cout << j << " and " << j + 1 << endl;
                minimo = min(nodes[nodes.size() - 1][j], minimo);
                maximo = max(nodes[nodes.size() - 1][j + 1], maximo);
            }
            vec.push_back(minimo);
            vec.push_back(maximo);
        }
    }
    nodes.push_back(vec);
}


void buildFirstNodes(vector<vector<float> > &basenodes, int fanout, int dim){
    long k = basenodes.size();
    long ini, fin;
    vector<float>vec;
    float minimo, maximo;
    for (long i = 0; i < k; i += fanout) {
        ini = i;
        fin = i + fanout - 1;
        for (long j = 0; j < dim; ++j) {
            minimo = FLT_MAX;
            maximo = FLT_MIN;
            // cout << "minimo: " << minimo << endl;
            // cout << "maximo: " << maximo << endl;
            for (long l = ini; l <= fin; ++l) {
                minimo = min(minimo, basenodes[l][j]);
                maximo = max(maximo, basenodes[l][j]);

            }
            vec.push_back(minimo);
            vec.push_back(maximo);
        }
    }
    basenodes.push_back(vec);
}