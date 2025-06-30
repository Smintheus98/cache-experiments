# matrix-vector-multiplication

The matrix-vector multiplication is hard to optimize for cache-efficiency, since the two vectors (input and result) require opposite access-patterns which eitherway induces cachemisses.
That way at least the naive (and easy to implement) approach performs best.

<!-- TODO: table of algortihms and runtime -->
