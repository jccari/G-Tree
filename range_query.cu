#include <stdio.h>
#define GPU_THREADS 	512 // check this
#define NUM_DIMS 		10
#define Intersect_Flags int
#define float 	float*

int fanout = 2;

//float -> is array of children nodes

__device__ // __global__ ?
bool check_intersection_leaf(int pos_node, float* query, float* nodes_tree, int innodes, totalnodes){
	bool intersect = false;
	int ini_children = ini(i, totalnodes, 0, fanout, NUM_DIMS, innodes, totalnodes);
	for (int i = 0; i < NUM_DIMS; ++i){
		if ( nodes_tree[ini_children + i] == query[i] )
			intersect = true
	}

	return intersect;
}

__device__ // __global__ ?
bool check_intersection_internal(int pos_node, float* query, float* nodes_tree, int innodes, totalnodes){
	bool intersect = false;
	int ini_children = ini(i, totalnodes, 0, fanout, NUM_DIMS, innodes, totalnodes);
	for (int i = 0; i < 2; ++i){
		if ( nodes_tree[ini_children] < query[0] && nodes_tree[ini_children+1] > query[1] )
			intersect = true
	}

	return intersect;
}


__device__
//void makeIntersections(float* query, float* offset, Intersect_Flags* intersect_flags, int i, int totalnodes){
void makeIntersections(float* query, long pos_offset, int &intersect_flag, int i, int numChildren, float* nodes_tree, bool isInternal, int innodes, int totalnodes){
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	//int row = threadIdx.y + blockIdx.y*blockDim.y;

	if (isInternal)
		if ( idx < numChildren && check_intersection_internal( pos_offset, query, nodes_tree, innodes, totalnodes))
			intersect_flag = 1;
		else intersect_flag = 0;
	else
		if ( idx < numChildren && check_intersection_leaf( pos_offset, query, nodes_tree, innodes, totalnodes))
			intersect_flag = 1;
		else intersect_flag = 0;

}

// definir 
	// fanout
	// dim -> NUM_DIMS
	// innodes

__global__
void intersectionKernel( float* query, float* offsets, int*& intersect_flags, int totalnodes, float* nodes_tree, int innodes){
	dim3 dimBlock( GPU_THREADS, 1, 1);
	dim3 dimGrid( ceil(numEntries/GPU_THREADS) , 1, 1);

	long* pos_children;
	children(i, pos_children, fanout, totalnodes);
	int num_children = (int) sizeof(pos_children)/ sizeof(long);
	//float* children = children();
	int ini_children = ini(i, totalnodes, 0, fanout, NUM_DIMS, innodes, totalnodes);
	int fin_children = fin(i, totalnodes, 0, fanout, NUM_DIMS, innodes, totalnodes);

	for (int i = 0; i < num_children; ++i){
		if ( isInternalNode(i) )
			makeIntersections<<< dimGrid, dimBlock>>> (query, pos_children[i], intersect_flags[i], i, num_children, nodes_tree, 1, innodes, totalnodes);
		else
			makeIntersections<<< dimGrid, dimBlock>>> (query, pos_children[i], intersect_flags[i], i, num_children, nodes_tree, 0, innodes, totalnodes);
			//makeIntersections<<< dimGrid, dimBlock>>> (query, offsets[i], intersect_flags[i], i, totalnodes);
	}
	
	//TODO: copy offsets[i]' childen to offsets
	for (int i = 0; i < num_children; ++i){
		offsets[i] = nodes_tree[ ini_children+i ];
	}
}


/*Eliminate entries that have not intersection with Q query*/
__host__
void compactKernel(float* offsets, int*& intersect_flags, int size){
	for (int i = 0; i < size; ++i){
		if( intersect_flags[i] == 0)
			offsets[i] = 0;

		intersect_flags[i] = 0;
	}
}

__global__
float* rangeQuery(float* root, float* query, float* nodes_tree ,int totalnodes, int innodes, int height){
	int* offsets = (int*) malloc( totalnodes*sizeof(int) );
	offsets[0] = 0; // inicializar con root que esta en la posicion 0

	int* d_offsets = (int*) malloc( sizeof(int) );
	//int numNodes = (int) sizeof(offsets)/ sizeof(float);
	int* intersect_flags = (int*) malloc( totalnodes*sizeof(int) ); // inicializar en -1

	cudaMalloc( (void**)& d_offsets, sizeof(int));
 	cudaMemcpy( d_offsets, &offsets, sizeof(int), cudaMemcpyHostToDevice) 

 	int size;
	for (int i = 0; i < height; ++i){
		intersectionKernel( query, offsets, intersect_flags, totalnodes, nodes_tree, innodes);
		size = (int) sizeof(intersect_flags)/sizeof(int);
		compactKernel( offsets, intersect_flags, size);
	}
}