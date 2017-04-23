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

    // Baseline
    GET_TIME("Baseline: %lf,\n",
    for (i = 0; i < loop; i++) {
    compute_pi_baseline(N);
    }
            );


    // OpenMP with 2 threads
    GET_TIME("OpenMP(2): %lf,\n",
    for (i = 0; i < loop; i++) {
    compute_pi_openmp(N, 2);
    }
            );


    GET_TIME("OMP SIMD(2): %lf\n",
    for (i = 0; i < loop; i++) {
    compute_pi_omp_simd(N, 2);
    }
            );

    // AVX SIMD
    GET_TIME("AVX SIMD: %lf,\n",
    for (i = 0; i < loop; i++) {
    compute_pi_avx(N);
    }
            );

    // AVX SIMD + Loop unrolling
    GET_TIME("AVX SIMD + unrolling: %lf,\n",
    for (i = 0; i < loop; i++) {
    compute_pi_avx_unroll(N);
    }
            );

    // AVX SIMD + Loop unrolling
    init_opencl(N, 1);
    GET_TIME("OpenCL: %lf,\n",
    for (i = 0; i < loop; i++) {
    compute_pi_opencl(N, 1);
    }
            );
    release_opencl();




    return 0;
}
