#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"
#include "benchmark_helper.h"

int main(int argc, char const *argv[])
{


    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 1000;
    double time;
    printf("%d,", N);
    for (int chunks = 1; chunks <= 512; chunks *= 2) {
        init_opencl(N, chunks);
        time = GET_TIME(
        for (i = 0; i < loop; i++) {
        compute_pi_opencl(N, chunks);
        }
               );
        printf("%.9f%c", time / loop, (chunks == 512) ? '\n' : ',');
    }
    release_opencl();

    return 0;
}
