#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"
#include "benchmark_helper.h"

int main(int argc, char const *argv[])
{
    if (argc < 4) return -1;
    unsigned lower = atoi(argv[1]), step = atoi(argv[2]), upper = atoi(argv[3]);
    unsigned loop = 25;
    for (unsigned threads = 1; threads <= 1024; threads *= 2) {
        double time_sum = 0.0;
        printf("%u,", threads);
        for (unsigned N = lower; N <= upper; N += step) {
            double time = GET_TIME(
                              for (unsigned i = 0; i < loop; i++) compute_pi_omp_simd(N, threads);
                          );
            time_sum += time / loop;
        }
        time_sum /= (upper - lower) / step;
        printf("%.9f\n", time_sum);
    }
    return 0;
}
