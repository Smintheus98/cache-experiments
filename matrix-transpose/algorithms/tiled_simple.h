#include <assert.h>

/**
 *  tiled transpose
 *  supposed to be cache-efficient (it is!)
 *  only allows perfect tile decomposition (n % tile_size == 0)
 *
 *  NOTE:  this version is no longer used as its runtime is equivalent to the
 *         one of tiled-generic while the latter code is cleaner
 */

void matrix_transpose(data_t* out, data_t* in, size_t n, size_t tile_size) {
    assert(n % tile_size == 0);
    for (size_t tr = 0; tr < n / tile_size; ++tr) {
        for (size_t tc = 0; tc < n / tile_size; ++tc) {
            for (size_t loc_r = 0; loc_r < tile_size; ++loc_r) {
                size_t r = tr * tile_size + loc_r;
                for (size_t loc_c = 0; loc_c < tile_size; ++loc_c) {
                    size_t c = tc * tile_size + loc_c;
                    out[RCTOIDX(c, r, n)] = in[RCTOIDX(r, c, n)];
                }
            }
        }
    }
}
