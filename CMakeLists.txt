cmake_minimum_required(VERSION 3.10)
project(GTree)

find_package(CUDA 9.1 REQUIRED)

set(
        CUDA_NVCC_FLAGS
        ${CUDA_NVCC_FLAGS};
        -ccbin /usr/bin/cuda-g++
)

set(CMAKE_CXX_STANDARD 11)

file( GLOB  cu  *.cu)

cuda_add_executable(GTree main.cpp readcsv.cpp readcsv.h BuildGTreeCPU.cpp BuildGTreeCPU.h cudaFun.h cudaFun.cu)