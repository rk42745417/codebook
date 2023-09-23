ull f(ull x, ull k, ull m) {
    return (__uint128_t(x) * x + k) % m;
}
// does not work when n is prime
// return any non-trivial factor (NOT necessary be a prime)
ull pollard_rho(ull n) {
    if (!(n & 1)) return 2;
    mt19937_64 rnd(120821011);
    while (true) {
        ull y = 2, yy = y, x = rnd() % n, t = 1;
        for (ull sz = 2; t == 1; sz <<= 1, y = yy) {
            for (ull i = 0; t == 1 && i < sz; ++i) {
                yy = f(yy, x, n);
                t = __gcd(yy > y ? yy - y : y - yy, n);
            }
        }
        if (t != 1 && t != n) return t;
    }
}
