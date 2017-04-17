#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_FORMULA_ID 4
/* formula===========================*/

// arctan
double compute_pi_formula0(size_t N);
// Lebiniz
double compute_pi_formula1(size_t N);
// Wallis
double compute_pi_formula2(size_t N);
// Nilakantha
double compute_pi_formula3(size_t N);
// Chudnovsky
double compute_pi_formula4(size_t N);

/* helper================================================================*/

/*The helper function to do the binary search
    args:
        - lower: the lower bound
        - upper: the upper bound
        - *judge: the function pointer for deciding the range, (-1, 0, 1)
    return:
        - N: the terminal number
*/
int binary_search(int lower, int upper, int (*judge)(int));

/*The helper function to do the convergence of computing pi
    args:
        - max_error: maximum error rate
        - formula_id: the id of formula (0 ~ 4)
    return:
        - N: the times it runs to acheive the goal
*/
int convergence(double max_error, int formula_id);