/* mod | g | maxn possible values:
998244353 | 3 | 8388608
1004535809 | 3 | 2097152
2013265921 | 31 | 134217728 */
template <int mod, int G, int maxn>
struct NTT {
    ll mpow(ll a, ll b) {
        ll res = 1;
        for (; b; b >>= 1, a = a * a % mod)
            if (b & 1)
                res = res * a % mod;
        return res;
    }
    static_assert(maxn == (maxn & -maxn));
    int roots[maxn];
    NTT() {
        ll r = mpow(G, (mod - 1) / maxn);
        for (int i = maxn >> 1; i; i >>= 1) {
            roots[i] = 1;
            for (int j = 1; j < i; j++)
                roots[i + j] = roots[i + j - 1] * r % mod;
            r = r * r % mod;
        }
    }
    // n = f.size() must be 2^k, and 0 <= f[i] < mod
    // n >= the size after convolution
    // practical:
    //  int sz = 1;
    //  while(sz < n + m - 1) sz <<= 1;
    void operator()(vector<ll> &f, int n, bool inv = false) {
        for (int i = 0, j = 0; i < n; i++) {
            if (i < j) swap(f[i], f[j]);
            for (int k = n >> 1; (j ^= k) < k; k >>= 1) { }
        }
        for (int s = 1; s < n; s *= 2) {
            for (int i = 0; i < n; i += s * 2) {
                for (int j = 0; j < s; j++) {
                    ll a = f[i + j];
                    ll b = f[i + j + s] * roots[s + j] % mod;
                    f[i + j] = (a + b) % mod;
                    f[i + j + s] = (a - b + mod) % mod;
                }
            }
        }
        if (inv) {
            int invn = mpow(n, mod - 2);
            for (int i = 0; i < n; i++)
                f[i] = f[i] * invn % mod;
            reverse(f.begin() + 1, f.end());
        }
    }
};
