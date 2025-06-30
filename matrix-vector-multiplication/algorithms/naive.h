/**
 *  simple naive matrix-vector multiplication
 *  not particularly cache-efficient
 */

void matvecmul(data_t* out, data_t* mat, data_t* vec, size_t n_rows, size_t n_cols, size_t tile_size) {
    for (size_t r = 0; r < n_rows; ++r) {
        out[r] = 0;
        for (size_t c = 0; c < n_cols; ++c) {
            out[r] += mat[RCTOIDX(r, c, n_cols)] * vec[c];
        }
    }
}
