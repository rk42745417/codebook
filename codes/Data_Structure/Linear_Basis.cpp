template<int BITS>
struct linear_basis {
    array<uint64_t, BITS> basis;
    linear_basis() { basis.fill(0); }
    void insert(uint64_t x) {
        for (int i = BITS - 1; i >= 0; i--) if ((x >> i) & 1) {
            if (basis[i] == 0) {
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }
    bool valid(uint64_t x) {
        for (int i = BITS - 1; i >= 0; i--)
            if ((x >> i) & 1) x ^= basis[i];
        return x == 0;
    }
    uint64_t operator[](int i) { return basis[i]; }
}; // max xor sum: greedy from high bit
   // min xor sum: zero(if possible) or min_element

