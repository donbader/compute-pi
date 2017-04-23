#include <stdio.h>
#include <string.h>
#include "benchmark_helper.h"
#include "pi_formula.h"


int main(int argc, char const *argv[])
{
    FILE* file = fopen("./result_formula_iter_times.csv", "r");
    unsigned long long times_array[7][6];
    if (!file) {
        return -1;
    }
    // read file
    char line[64];
    size_t h = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        size_t w = 0;
        while (token != NULL) {
            times_array[h][w] = atoi(token);
            token = strtok(NULL, ",");
            ++w;
        }
        ++h;
    }
    fclose(file);

    // Print time
    for (int i = 1; i <= 7; ++i) {
        printf("%d,", i);
        for (int id = 0; id <= MAX_FORMULA_ID; ++id) {
            char* format = (id != MAX_FORMULA_ID) ? "%lf," : "%lf\n";
            PRINT_TIME(format,
                       compute_pi_formula(id, times_array[i - 1][id + 1]);
                      );
        }
    }


    return 0;
}