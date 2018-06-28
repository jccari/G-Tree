//
// Created by achavez on 6/28/18.
//

#ifndef GTREE_BUILDGTREECPU_H
#define GTREE_BUILDGTREECPU_H

#include <vector>
#include <iostream>
#include <cfloat>
#include <algorithm>
#include <cmath>

using namespace std;

bool sortLowxBoolean(const vector<float> &v1, const vector<float> &v2);
bool isInternalNode(int idx, int totalnodes, int leafnodes);
void sortLowX(vector<vector<float>> &nodes);
long buildGTreeUtil(vector<vector<float> > &nodes, int fanout, int dim);
void buildGTree(vector<vector<float> > &nodes, int fanout, int dim);
void buildFirstNodes(vector<vector<float> > &basenodes, int fanout, int dim);
void vectorToArray(vector<vector<float> > &nodes, float *&arr, int dim, long k, long &totalsize);
void children(long idx, long *&arr, int fanout, long totalnodes);
long parent(long i, int fanout);
long ini(long idx, long totalsize, long k, long fanout, int dim, long innodes, long totalnodes);
long fin(long idx, long totalsize, long k, long fanout, int dim, long innodes, long totalnodes);

#endif //GTREE_BUILDGTREECPU_H
