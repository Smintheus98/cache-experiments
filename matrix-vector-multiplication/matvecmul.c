#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RCTOIDX(row, col, n_cols) ((row) * (n_cols) + (col))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef int data_t;

//#define MT_NAIVE
#ifdef MVM_NAIVE
#   include "algorithms/naive.h"
#elif defined( MVM_TILED )
#   include "algorithms/tiled.h"
#else
    void matvecmul(data_t*, data_t*, data_t*, size_t, size_t, size_t) { /* dummy function */ }
#   error "no algorithm selected! Compile with `-D<ALGORITHM>` with <ALGORITHM> being one of: MVM_NAIVE, MVM_TILED"
#endif


double time_diff(struct timespec start, struct timespec end) {
    time_t secs =  end.tv_sec  - start.tv_sec;
    time_t nsecs = end.tv_nsec - start.tv_nsec;
    return (secs * 1e9 + nsecs) * 1e-9;
}

int main(void) {
    // NOTE: for now only quadratic matrices are considered
    const size_t n = 32768;
    data_t * A, * b, * res;
    int loop = 10;
    int seed = 89677632;

    // allocate buffer
    A   = malloc( n * n * sizeof(data_t) ); // n x n
    b   = malloc( n * sizeof(data_t) ); // n
    res = malloc( n * sizeof(data_t) ); // n

    // setup random data
    srand(seed);
    for (size_t k = 0; k < n * n; ++k)
        A[k] = rand();
    for (size_t k = 0; k < n; ++k)
        b[k] = rand();

    // measure execution time
#ifdef MVM_TILED
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
                matvecmul(res, A, b, n, n, ts);
        }
        clock_gettime(CLOCK_REALTIME, &t_end);

        printf ("Run time: %fs\n", time_diff(t_start, t_end) / loop);
    }


    // check matrix vector multiplication
    bool correct = true;
    srand(seed);
    for (size_t r = 0; r < n; ++r) {
        data_t val = (data_t) 0;
        for (size_t c = 0; c < n; ++c) {
            val += A[RCTOIDX(r, c, n)] * b[c];
        }
        correct = correct && (res[r] == val);
    }
    printf("Result: %s\n", correct ? "correct" : "incorrect");

    return 0;
}
