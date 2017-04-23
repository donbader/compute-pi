#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"
#include "benchmark_helper.h"

int main(int argc, char const *argv[])
{


    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, threads, loop = 1000;
    double time;
    printf("%d\n", N);
    for (threads = 1; threads <= 1024; threads *= 2) {
        time = GET_TIME(
        for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, threads);
        }
               );
        printf("%.9f%c", time / loop, (threads == 1024) ? '\n' : ',');
    }
    return 0;
}
