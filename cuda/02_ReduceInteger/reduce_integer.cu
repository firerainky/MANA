#include "freshman.h"
#include <cuda_runtime.h>

int recursiveReduce(int *arr, size_t const size) {
    if (size == 1) { return arr[0]; }
    size_t stride = size / 2;
    for (size_t i = 0; i < stride; ++i) { arr[i] += arr[i + stride]; }
    if (size % 2 == 1) { arr[0] += arr[size - 1]; }
    return recursiveReduce(arr, stride);
}

__global__ void warmup(int *iarr, int *oarr, size_t n) {
    // Get the threadid, we are computing in current block
    unsigned int tid = threadIdx.x;
    unsigned int idx = tid + blockDim.x * blockIdx.x;
    if (idx >= n) return;

    // Get current block's first index
    int *larr = iarr + blockIdx.x * blockDim.x;

    // Compute the sum in each block seperately
    // Reduce sum with increasing stride
    for (int stride = 1; stride < blockDim.x; stride *= 2) {
        if ((tid % (2 * stride)) == 0)
            larr[tid] += tid + stride >= blockDim.x ? 0 : larr[tid + stride];
        __syncthreads();
    }
    if (tid == 0) oarr[blockIdx.x] = larr[0];
}

__global__ void reduceNeighbored(int *iarr, int *oarr) {
    unsigned int tid = threadIdx.x;

    int *larr = iarr + blockIdx.x * blockDim.x;

    for (int stride = 1; stride < blockDim.x; stride *= 2) {
        if ((tid % (2 * stride)) == 0)
            larr[tid] += tid + stride >= blockDim.x ? 0 : larr[tid + stride];
        __syncthreads();
    }
    if (tid == 0) oarr[blockIdx.x] = larr[0];
}

__global__ void reduceNeighboredLess(int *iarr, int *oarr) {
    unsigned int tid = threadIdx.x;

    int *larr = iarr + blockIdx.x * blockDim.x;
    for (int stride = 1; stride < blockDim.x; stride *= 2) {
        int index = 2 * stride * tid;
        if (index < blockDim.x) {
            larr[index] +=
                    index + stride >= blockDim.x ? 0 : larr[index + stride];
        }
        __syncthreads();
    }
    if (tid == 0) oarr[blockIdx.x] = larr[0];
}

__global__ void reduceInterLeaved(int *iarr, int *oarr, unsigned int n) {
    unsigned int tid = threadIdx.x;
    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;

    int *larr = iarr + blockIdx.x * blockDim.x;
    if (idx >= n) return;

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) larr[tid] += larr[tid + stride];
        __syncthreads();
    }

    if (tid == 0) oarr[blockIdx.x] = larr[0];
}

int main(int argc, char **argv) {
    initDevice(0);
    int size = 1 << 24;
    printf(" with array size %d \n", size);

    // Compute execution configuration
    int blockSize = 1024;
    if (argc > 1) { blockSize = atoi(argv[1]); }
    dim3 block(blockSize, 1);
    dim3 grid((size - 1) / block.x + 1, 1);
    printf(" grid %d block %d \n", grid.x, block.x);

    // Allocate host memory
    size_t bytes = size * sizeof(int);
    int *iarr_host = (int *) malloc(bytes);
    int *oarr_host = (int *) malloc(grid.x * sizeof(int));
    int *tmp = (int *) malloc(bytes);

    // Initialize the array
    initializeArr(iarr_host, size);

    memcpy(tmp, iarr_host, bytes);
    double iStart, iElaps;

    // Allocate device memory
    int *iarr_dev = NULL;
    int *oarr_dev = NULL;
    CHECK(cudaMalloc((void **) &iarr_dev, bytes));
    CHECK(cudaMalloc((void **) &oarr_dev, grid.x * sizeof(int)));

    // CPU reduction
    int cpu_sum = 0;
    iStart = cpuSecond();
    // for (int i = 0; i < size; ++i) { cpu_sum += tmp[i]; }
    // This recursive algorithm is much faster then for loop sum above
    // since it reduces sum times
    cpu_sum = recursiveReduce(tmp, size);
    iElaps = cpuSecond() - iStart;
    printf(" cpu reduce elapsed %lf ms cpu_sum: %d \n", iElaps, cpu_sum);

    int gpu_sum = 0;
    // Kernel 0: Warm up
    CHECK(cudaMemcpy(iarr_dev, iarr_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    warmup<<<grid, block>>>(iarr_dev, oarr_dev, size);
    CHECK(cudaDeviceSynchronize());
    CHECK(cudaMemcpy(oarr_host, oarr_dev, grid.x * sizeof(int),
                     cudaMemcpyDeviceToHost));
    gpu_sum = 0;
    for (int i = 0; i < grid.x; ++i) { gpu_sum += oarr_host[i]; }
    iElaps = cpuSecond() - iStart;
    printf(" gpu warmup elapsed %lf ms gpu_sum: %d <<<grid %d block "
           "%d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);

    // Kernel 1: Reduce neighbored (same as warm up above)
    // TODO: actually the max warp size is 32, and our code is not working for not 2^n block size which is greater than 32
    CHECK(cudaMemcpy(iarr_dev, iarr_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    warmup<<<grid, block>>>(iarr_dev, oarr_dev, size);
    CHECK(cudaDeviceSynchronize());
    CHECK(cudaMemcpy(oarr_host, oarr_dev, grid.x * sizeof(int),
                     cudaMemcpyDeviceToHost));
    gpu_sum = 0;
    for (int i = 0; i < grid.x; ++i) { gpu_sum += oarr_host[i]; }
    iElaps = cpuSecond() - iStart;
    printf(" gpu neighbored elapsed %lf ms gpu_sum: %d <<<grid %d block "
           "%d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);

    // Kernel 2: Reduce neighbored less
    CHECK(cudaMemcpy(iarr_dev, iarr_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    reduceNeighboredLess<<<grid, block>>>(iarr_dev, oarr_dev);
    CHECK(cudaDeviceSynchronize());
    CHECK(cudaMemcpy(oarr_host, oarr_dev, grid.x * sizeof(int),
                     cudaMemcpyDeviceToHost));
    gpu_sum = 0;
    for (int i = 0; i < grid.x; ++i) gpu_sum += oarr_host[i];
    iElaps = cpuSecond() - iStart;
    printf(" gpu neighbored less elapsed %lf ms gpu_sum: %d <<<grid %d block "
           "%d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);

    // Kernel 3: Reduce neighbored less
    CHECK(cudaMemcpy(iarr_dev, iarr_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    reduceInterLeaved<<<grid, block>>>(iarr_dev, oarr_dev, size);
    CHECK(cudaDeviceSynchronize());
    CHECK(cudaMemcpy(oarr_host, oarr_dev, grid.x * sizeof(int),
                     cudaMemcpyDeviceToHost));
    gpu_sum = 0;
    for (int i = 0; i < grid.x; ++i) gpu_sum += oarr_host[i];
    iElaps = cpuSecond() - iStart;
    printf(" gpu reduce inter leaved less elapsed %lf ms gpu_sum: %d <<<grid "
           "%d block "
           "%d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);
}