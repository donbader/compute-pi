#include "pi_formula.h"

int main(int argc, char** argv)
{
    double max_error = atof(argv[1]);
    // if input > 1, then max_error = 10^(-max_error)
    max_error = max_error > 1 ? pow(10, -max_error) : max_error;

    printf("%d,%d,%d,%d,%d\n", convergence(max_error, 0)
           , convergence(max_error, 1)
           , convergence(max_error, 2)
           , convergence(max_error, 3)
           , convergence(max_error, 4));

    return 0;
}