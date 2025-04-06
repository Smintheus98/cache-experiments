/**
 *  tiled transpose optimized and generalized
 *  cache-efficient
 *  also allows non-perfect tile decomposition
 */

void matrix_transpose(data_t* out, data_t* in, size_t n, size_t tile_size) {
    for (size_t tr = 0; tr < n; tr += tile_size) {
        for (size_t tc = 0; tc < n; tc += tile_size) {
            for (size_t r = tr; r < MIN(n, tr+tile_size); ++r) {
                for (size_t c = tc; c < MIN(n, tc+tile_size); ++c) {
                    out[RCTOIDX(c, r, n)] = in[RCTOIDX(r, c, n)];
                }
            }
        }
    }
}
