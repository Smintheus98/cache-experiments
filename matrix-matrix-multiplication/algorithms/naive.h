
void matmatmul(data_t* C, data_t* A, data_t* B, size_t C_nrows, size_t C_ncols, size_t A_ncols, size_t) {
    for (size_t r = 0; r < C_nrows; ++r) {
        for (size_t c = 0; c < C_ncols; ++c) {
            C[RCTOIDX(r, c, C_ncols)] = (data_t) 0;
            for (size_t k = 0; k < A_ncols; ++k) {
                C[RCTOIDX(r, c, C_ncols)] += A[RCTOIDX(r, k, A_ncols)] * B[RCTOIDX(k, c, A_ncols)];
            }
        }
    }
}
