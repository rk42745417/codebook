// 0-based, [l, r)
// Remember to call init
struct tag {
    // Construct identity element
    tag() { }
    // apply tag
    tag& operator+=(const tag &b) {
        return *this;
    }
};
struct node {
    // Construct identity element
    node() { }
    // Merge two nodes
    node operator+(const node &b) const {
        node res = node();
        return res;
    }
    // Apply tag to this node
    void operator()(const tag &t) {
    }
};
template<typename N, typename T>
struct lazy_segtree {
    N arr[maxn << 1];
    T tag[maxn];
    int n;
    void init(const vector<N> &a) {
        n = a.size();
        for (int i = 0; i < n; i++)
            arr[i + n] = a[i], tag[i] = T();
        for (int i = n - 1; i; i--)
            arr[i] = arr[i << 1] + arr[i << 1 | 1];
    }
    void upd(int p, T v) {
        if (p < n)
            tag[p] += v;
        arr[p](v);
    }
    void pull(int p) {
        for (p >>= 1; p; p >>= 1) {
            arr[p] = arr[p << 1] + arr[p << 1 | 1];
            arr[p](tag[p]);
        }
    }
    void push(int p) {
        for (int h = __lg(p); h; h--) {
            int i = p >> h;
            upd(i << 1, tag[i]);
            upd(i << 1 | 1, tag[i]);
            tag[i] = T();
        }
    }
    void edt(int l, int r, T v) {
        int tl = l + n, tr = r + n - 1;
        push(tl); push(tr);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                upd(l++, v);
            if (r & 1)
                upd(--r, v);
        }
        pull(tl); pull(tr);
    }
    N que(int l, int r) {
        N resl = N(), resr = N();
        int tl = l + n, tr = r + n - 1;
        push(tl); push(tr);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = resl + arr[l++];
            if (r & 1)
                resr = arr[--r] + resr;
        }
        return resl + resr;
    }
};
