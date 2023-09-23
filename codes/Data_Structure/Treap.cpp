__gnu_cxx::sfmt19937 rnd(48763);
namespace Treap {
struct node {
    int size, pri;
    node *lc, *rc, *pa;
    node() : size(1), pri(rnd()), lc(0), rc(0), pa(0) {}
    void pull() {
        size = 1; pa = 0;
        if (lc) { size += lc->size; lc->pa = this; }
        if (rc) { size += rc->size; rc->pa = this; }
    }
};
int SZ(node *x) { return x ? x->size : 0; }
node *merge(node *L, node *R) {
    if (!L || !R) return L ? L : R;
    if (L->pri > R->pri)
        return L->rc = merge(L->rc, R), L->pull(), L;
    else
        return R->lc = merge(L, R->lc), R->pull(), R;
}
void splitBySize(node *o, int k, node *&L, node *&R) {
    if (!o) { L = R = 0; }
    else if (int s = SZ(o->lc) + 1; s <= k) {
        L = o, splitBySize(o->rc, k-s, L->rc, R);
        L->pull();
    }
    else {
        R = o, splitBySize(o->lc, k, L, R->lc);
        R->pull();
    }
}  // SZ(L) == k
int getRank(node *o) { // 1-base
    int r = SZ(o->lc) + 1;
    for (; o->pa; o = o->pa)
        if (o->pa->rc == o) r += SZ(o->pa->lc) + 1;
    return r;
}
} // namespace Treap, not tested
