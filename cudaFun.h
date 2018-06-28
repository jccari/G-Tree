//
// Created by achavez on 6/28/18.
//

#ifndef GTREE_CUDAFUN_H
#define GTREE_CUDAFUN_H

#include <cuda/cuda_runtime_api.h>

void allocateArray(float* h_arr, float* &d_arr, long totalsize);
void deallocateArray(float* &h_arr, float* d_arr, long totalsize);
void deleteDeviceArray(float *&d_arr, long totalsize);

#endif //GTREE_CUDAFUN_H
