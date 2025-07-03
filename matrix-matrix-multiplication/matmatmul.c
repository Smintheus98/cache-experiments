#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RCTOIDX(row, col, n_cols) ((row) * (n_cols) + (col))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef int data_t;

#ifdef MMM_NAIVE
#   include "algorithms/naive.h"
#elif defined( MMM_NAIVE_LOOPSWP )
#   include "algorithms/naive-loopswp.h"
#elif defined( MMM_TILED )
#   include "algorithms/tiled.h"
#else
    void matmatmul(data_t*, data_t*, data_t*, size_t, size_t, size_t, size_t) { /* dummy function */ }
#   error "no algorithm selected! Compile with `-D<ALGORITHM>` with <ALGORITHM> being one of: MMM_NAIVE, MVM_TILED"
#endif


double time_diff(struct timespec start, struct timespec end) {
    time_t secs =  end.tv_sec  - start.tv_sec;
    time_t nsecs = end.tv_nsec - start.tv_nsec;
    return (secs * 1e9 + nsecs) * 1e-9;
}

int main(void) {
    // NOTE: for now only quadratic matrices are considered
    const size_t n = 1024 /*4096*/ /*32768*/ ;
    data_t * A, * B, * C;
    int loop = 10;
    int seed = 89677632;

    // allocate buffer
    A = malloc( n * n * sizeof(data_t) ); // n x n
    B = malloc( n * n * sizeof(data_t) ); // n x n
    C = malloc( n * n * sizeof(data_t) ); // n x n

    // setup random data
    srand(seed);
    for (size_t k = 0; k < n * n; ++k) {
        A[k] = rand();
        B[k] = rand();
    }

    // measure execution time
#ifdef MMM_TILED
    for (size_t ts = 1; ts <= n; ts *= 2) {
        printf ("Tile size: %lu  ", ts);
#else
    {
        size_t ts;
#endif
        struct timespec t_start, t_end;
        clock_gettime(CLOCK_REALTIME, &t_start);
        {
            for (int i = 0; i < loop; ++i)
                matmatmul(C, A, B, n, n, n, ts);
        }
        clock_gettime(CLOCK_REALTIME, &t_end);

        printf ("Run time: %fs\n", time_diff(t_start, t_end) / loop);
    }


    // check matrix vector multiplication
    bool correct = true;
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            data_t val = (data_t) 0;
            for (size_t k = 0; k < n; ++k) {
                val += A[RCTOIDX(r, k, n)] * B[RCTOIDX(k, c, n)];
            }
            correct = correct && (C[RCTOIDX(r, c, n)] == val);
        }
    }
    printf("Result: %s\n", correct ? "correct" : "incorrect");

    return 0;
}
