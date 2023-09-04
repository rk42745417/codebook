struct lichao { // maxn: range
    struct line {
        ll a, b;
        line(): a(0), b(0) { } // or LINF
        line(ll a, ll b): a(a), b(b) { }
        ll operator()(ll x) { return a * x + b; }
    } arr[maxn << 2];
    void insert(int l, int r, int id, line x) {
        int m = (l + r) >> 1;
        if(arr[id](m) < x(m))
            swap(arr[id], x);
        if(l == r - 1)
            return;
        if(arr[id].a < x.a)
            insert(m, r, id << 1 | 1, x);
        else
            insert(l, m, id << 1, x);
    } // change to > if query min
    void insert(ll a, ll b) { insert(0, maxn, 1, line(a, b)); }
    ll que(int l, int r, int id, int p) {
        if(l == r - 1)
            return arr[id](p);
        int m = (l + r) >> 1;
        if(p < m)
            return max(arr[id](p), que(l, m, id << 1, p));
        return max(arr[id](p), que(m, r, id << 1 | 1, p));
    } // chnage to min if query min
    ll que(int p) { return que(0, maxn, 1, p); }
} tree;

