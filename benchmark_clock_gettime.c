#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"
#include "benchmark_helper.h"

int main(int argc, char const *argv[])
{


    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 25;
    double time;

    // Baseline
    time = GET_TIME(
               for (i = 0; i < loop; i++) compute_pi_baseline(N);
           );
    printf("%.9f,", time / loop);

    // OpenMP with 2 threads
    time = GET_TIME(
               for (i = 0; i < loop; i++) compute_pi_openmp(N, 2);
           );
    printf("%.9f,", time / loop);


    // OpenMP SIMD 2 threads
    time = GET_TIME(
               for (i = 0; i < loop; i++) compute_pi_omp_simd(N, 2);
           );
    printf("%.9f,", time / loop);


    // AVX SIMD
    time = GET_TIME(
               for (i = 0; i < loop; i++) compute_pi_avx(N);
           );
    printf("%.9f,", time / loop);

    // AVX SIMD + Loop unrolling
    time = GET_TIME(
               for (i = 0; i < loop; i++) compute_pi_avx_unroll(N);
           );
    printf("%.9f,", time / loop);

    // OpenCL
    init_opencl(N, 1);
    time = GET_TIME(
               for (i = 0; i < loop; i++) compute_pi_opencl(N, 1);
           );
    printf("%.9f\n", time / loop);
    release_opencl();

    return 0;
}
