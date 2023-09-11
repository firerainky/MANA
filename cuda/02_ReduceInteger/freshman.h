#ifndef FRESHMAN_H
#define FRESHMAN_H

#define CHECK(call)                                                            \
    {                                                                          \
        const cudaError_t error = call;                                        \
        if (error != cudaSuccess) {                                            \
            printf("ERROR: %s: %d,", __FILE__, __LINE__);                      \
            printf("code: %d, reason: %s\n", error,                            \
                   cudaGetErrorString(error));                                 \
            exit(1);                                                           \
        }                                                                      \
    }

#include <stdio.h>
#include <sys/time.h>

double cpuSecond() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) (tp.tv_usec * 1e-6));
}

void initializeArr(int *arr, size_t size) {
    time_t t;
    srand((unsigned) time(&t));
    for (size_t i = 0; i < size; ++i) { arr[i] = int(rand() & 0xff); }
}

void initDevice(int devNum) {
    int dev = devNum;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("Using device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));
}

#endif