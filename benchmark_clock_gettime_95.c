#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"
#include "benchmark_helper.h"

int main(int argc, char const *argv[])
{


    if (argc < 2) return -1;

    int N = atoi(argv[1]);

    // Baseline
    PRINT_TIME_95( "%.9f,",
                   compute_pi_baseline(N);
                 );

    // OpenMP with 2 threads
    PRINT_TIME_95( "%.9f,",
                   compute_pi_openmp(N, 2);
                 );

    // OpenMP SIMD 2 threads
    PRINT_TIME_95( "%.9f,",
                   compute_pi_omp_simd(N, 2);
                 );

    // AVX SIMD
    PRINT_TIME_95( "%.9f,",
                   compute_pi_avx(N);
                 );

    // AVX SIMD + Loop unrolling
    PRINT_TIME_95( "%.9f,",
                   compute_pi_avx_unroll(N);
                 );

    // OpenCL
    init_opencl(N, 1);
    PRINT_TIME_95( "%.9f\n",
                   compute_pi_opencl(N, 1);
                 );
    release_opencl();



    return 0;
}
