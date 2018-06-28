#include "cudaFun.h"
#include <cuda/cuda_runtime.h>
#include <malloc.h>

void allocateArray(float* h_arr, float* &d_arr, long totalsize){
    size_t sizecpy = totalsize * sizeof(float);
    cudaMalloc((void **) &d_arr, sizecpy);
    cudaMemcpy(d_arr, h_arr, sizecpy, cudaMemcpyHostToDevice);
}

void deallocateArray(float* &h_arr, float* d_arr, long totalsize){
    size_t sizecpy = totalsize * sizeof(float);
    h_arr = (float *)malloc(totalsize * sizeof(float));
    cudaMemcpy(h_arr, d_arr, sizecpy, cudaMemcpyDeviceToHost);
}

void deleteDeviceArray(float *&d_arr, long totalsize){
    cudaFree(d_arr);
}