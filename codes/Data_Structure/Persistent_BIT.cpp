// Remember to call init
struct fenwicktree {
    vector<int> arr[maxn], sum[maxn];
    void init() {
        for (int i = 0; i < maxn; i++) {
            arr[i].push_back(0);
            sum[i].push_back(0);
        }
    }
    // edit must be called with non-increasing t
    void edt(int p, int v, int t) {
        for (; p < maxn; p += p & -p) {
            arr[p].push_back(t);
            sum[p].push_back(sum[p].back() + v);
        }
    }
    inline int get(int i, int t) {
        return sum[i][(upper_bound(arr[i].begin(), arr[i].end(), t) - arr[i].begin()) - 1];
    }
    int que(int l, int r, int t) {
        if (r < l || l == 0)
            return 0;
        int res = 0;
        for (; r; r -= r & -r)
            res += get(r, t);
        for (l--; l; l -= l & -l)
            res -= get(l, t);
        return res;
    }
    // return the last p s.t. bit[dw..up][1..p] < v
    // maxn - 1 if v > sum and 0 if v = 0
    int bin(int v, int dw, int up) {
        int res = 0, p = 0;
        for (int i = 1 << 20; i; i>>= 1) {
            int g = get(p | i, up) - get(p | i, dw - 1);
            if ((p | i) < maxn && res + g < v) {
                res += g;
                p |= i;
            }
        }
        return p;
    }
} bit;
