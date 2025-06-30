/**
 *  tiled matrix-vector multiplication
 *  not really more cache-efficient than the naive approach
 */

void matvecmul(data_t* out, data_t* mat, data_t* vec, size_t n_rows, size_t n_cols, size_t tile_size) {
    for (size_t tr = 0; tr < n_rows; tr += tile_size) {
        for (size_t tc = 0; tc < n_cols; tc += tile_size) {
            for (size_t r = tr; r < MIN(n_rows, tr+tile_size); ++r) {
                if (tc == 0) {
                    // NOTE: apparently an initial memset is slower than this manual initialization
                    out[r] = 0;
                }
                for (size_t c = tc; c < MIN(n_cols, tc+tile_size); ++c) {
                    out[r] += mat[RCTOIDX(r, c, n_cols)] * vec[c];
                }
            }
        }
    }
}
