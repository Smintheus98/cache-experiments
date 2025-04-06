/**
 *  simple naive transpose with loops swapped
 *  not particularly cache-efficient
 */

void matrix_transpose(data_t* out, data_t* in, size_t n, size_t tile_size) {
    for (size_t c = 0; c < n; ++c) {
        for (size_t r = 0; r < n; ++r) {
            out[RCTOIDX(c, r, n)] = in[RCTOIDX(r, c, n)];
        }
    }
}
