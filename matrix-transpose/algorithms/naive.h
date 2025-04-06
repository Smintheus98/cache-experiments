/**
 *  simple naive transpose
 *  not particularly cache-efficient
 */

void matrix_transpose(data_t* out, data_t* in, size_t n, size_t tile_size) {
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            out[RCTOIDX(c, r, n)] = in[RCTOIDX(r, c, n)];
        }
    }
}
