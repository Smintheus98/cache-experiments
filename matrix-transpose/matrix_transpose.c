#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RCTOIDX(row, col, n_cols) ((row) * (n_cols) + (col))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef int data_t;

//#define MT_NAIVE
#ifdef MT_NAIVE
#   include "algorithms/naive.h"
#elif defined( MT_NAIVE_LOOPSWAP )
#   include "algorithms/naive_swapped_loops.h"
//#elif defined( MT_TILED_SIMPLE )
//#   include "algorithms/tiled_simple.h"
#elif defined( MT_TILED_GENERIC)
#   include "algorithms/tiled_generic.h"
#else
    void matrix_transpose(data_t*, data_t*, size_t, int) { /* dummy function */ }
#   error "no algorithm selected! Compile with `-D<ALGORITHM>` with <ALGORITHM> being one of: MT_NAIVE, MT_NAIVE_LOOPSWAP, MT_TILED_SIMPLE, MT_TILED_GENERIC"
#endif


double time_diff(struct timespec start, struct timespec end) {
    time_t secs =  end.tv_sec  - start.tv_sec;
    time_t nsecs = end.tv_nsec - start.tv_nsec;
    return (secs * 1e9 + nsecs) * 1e-9;
}

int main(void) {
    // NOTE: for now only quadratic matrices are considered
    const int n = 4096;
    data_t * A, * A_trans;
    int loop = 10;
    int seed = 89677632;

    // allocate buffer
    A       = malloc( n * n * sizeof(data_t) ); // n x n
    A_trans = malloc( n * n * sizeof(data_t) ); // n x n

    // setup random data
    srand(seed);
    for (size_t k = 0; k < n * n; ++k)
        A[k] = rand();

    // measure execution time
#if defined(MT_TILED_SIMPLE) || defined(MT_TILED_GENERIC)
    for (int ts = 1; ts <= 256; ts *= 2) {
        printf ("Tile size: %i  ", ts);
#else
    {
        int ts;
#endif
        struct timespec t_start, t_end;
        clock_gettime(CLOCK_REALTIME, &t_start);
        {
            for (int i = 0; i < loop; ++i)
                matrix_transpose(A_trans, A, n, ts);
        }
        clock_gettime(CLOCK_REALTIME, &t_end);

        printf ("Run time: %fs\n", time_diff(t_start, t_end) / loop);
    }


    // check transpose
    bool correct = true;
    srand(seed);
    for (size_t r = 0; r < n; ++r)
        for (size_t c = 0; c < n; ++c)
            correct = correct && (A_trans[RCTOIDX(c, r, n)] == rand());
    printf("Result: %s\n", correct ? "correct" : "incorrect");

    return 0;
}
