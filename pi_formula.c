#include "pi_formula.h"

// arctan
double compute_pi_formula0(size_t N)
{
    double pi = 0.0;
    double dt = 1.0 / N;                // dt = (b-a)/N, b = 1, a = 0
    for (size_t i = 0; i < N; i++) {
        double x = (double) i / N;      // x = ti = a+(b-a)*i/N = i/N
        pi += dt / (1.0 + x * x);       // integrate 1/(1+x^2), i = 0....N
    }
    return pi * 4.0;
}

// Lebiniz
double compute_pi_formula1(size_t N)
{
    double pi = 0.0;
    for (size_t i = 0; i < N; ++i) {
        double sign = (i % 2 == 1) ? 1 : -1;
        double dt = sign / (2 * i - 1);
        pi += dt;
    }
    return pi * 4.0;
}

// Wallis
double compute_pi_formula2(size_t N)
{
    double pi = 1.0;
    for (size_t i = 1; i <= N; ++i) {
        double a = i * 2.0 / (2 * i - 1);
        double b = i * 2.0 / (2 * i + 1);
        pi *= a * b;
    }
    return pi * 2.0;
}

// Nilakantha
double compute_pi_formula3(size_t N)
{
    double pi = 3.0;
    for (size_t i = 1; i <= N; ++i) {
        double numerator = 4.0 * ((i % 2) ? 1 : -1);
        double denominator = (2.0 * i) * (2 * i + 1) * (2 * i + 2);
        pi += numerator / denominator;
    }
    return pi;
}



// Chudnovsky
// Warning: if N is too big, then this function will return nan
double compute_pi_formula4(size_t N)
{
    double sum = 0.0;
    double C = 426880.0 * sqrt(10005);
    double factorial(int k) {
        double result = 1.0;
        for (size_t i = k; i > 1 ; --i)
            result *= i;
        return result;
    }

    for (size_t i = 0; i <= N; ++i) {
        double M = factorial(6 * i) / factorial(3 * i) / pow(factorial(i), 3);
        double L = (13591409 + 545140134 * i);
        double X = pow(-262537412640768000, i);
        sum += M * L / X;
    }
    return C / sum;
}


double compute_pi_formula(size_t formula_id, size_t N)
{
    static double (*formula[])(size_t) = {compute_pi_formula0, compute_pi_formula1, compute_pi_formula2, compute_pi_formula3, compute_pi_formula4};
    if (formula_id > MAX_FORMULA_ID || formula_id < 0) {
        return -1;
    }
    return formula[formula_id](N);
}

int binary_search(int lower, int upper, int (*judge)(int))
{
    int mid, decision;
    while (lower < upper) {
        mid = (upper + lower) / 2;
        decision = (*judge)(mid);
        if (decision > 0)
            lower = mid + 1;
        else if (decision < 0)
            upper = mid - 1;
        else
            return mid;
    }

    return lower;
}

#define abs(num) (num) > 0 ? (num) : -(num)

int convergence(double max_error, int formula_id)
{
    if (formula_id > MAX_FORMULA_ID || formula_id < 0) {
        return -1;
    }

    // judge function
    int judge(int n) {
        double pi = compute_pi_formula(formula_id, n);
        double error = abs(pi - M_PI);
        double error_diff = error - max_error;
        // printf("\tN: %d, error: %.10f, error_diff: %.10f\n", n, error, error_diff);
        return error_diff > 0 ? 1 : error_diff < 0 ? -1 : 0;
    }

    long long N = 1;
    while (judge(N) > 0)
        N *= 10;


    if (N == 1) return 1;
    return binary_search(N / 10 + 1, N, judge) + 1;
}