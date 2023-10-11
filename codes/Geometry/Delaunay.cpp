/* please ensure input points are unique */
/* A triangulation such that no points will strictly
   inside circumcircle of any triangle.
   find(root, p) : return a triangle contain given point
add_point : add a point into triangulation
Region of triangle u: iterate each u.e[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3]
Voronoi diagram: for each triangle in `res`,
the bisector of all its edges will split the region. */
#define L(i) ((i) == 0 ? 2 : (i) - 1)
#define R(i) ((i) == 2 ? 0 : (i) + 1)
#define F3 for (int i = 0; i < 3; i++)
bool in_cc(const array<ptll, 3> &p, ptll q) {
    __int128 det = 0;
    F3 det += __int128(p[i].dis2() - q.dis2()) * cross2(p[R(i)] - q, p[L(i)] - q);
    return det > 0;
}
struct Tri;
struct E {
    Tri *t; int side; E() : t(0), side(0) { }
    E(Tri *t_, int side_) : t(t_), side(side_){ }
};
struct Tri {
    bool vis;
    array<ptll, 3> p;
    array<Tri*, 3> ch;
    array<E, 3> e;
    Tri(ptll a = ptll(), ptll b = ptll(), ptll c = ptll()) : vis(0), p{a,b,c}, ch{} {}
    bool has_chd() const { return ch[0] != nullptr; }
    bool contains(ptll q) const {
        F3 if (ori(p[i], p[R(i)], q) < 0) return false;
        return true;
    }
} pool[maxn * 10], *it;
void link(E a, E b) {
    if (a.t) a.t->e[a.side] = b;
    if (b.t) b.t->e[b.side] = a;
}
const int C = 100 * 1007 * 1007;
struct Trigs {
    Tri *root;
    Trigs() { // should at least contain all points
        root =  // C = 100*MAXC^2 or just MAXC?
            new(it++) Tri(ptll(-C, -C), ptll(C * 2, -C), ptll(-C, C * 2));
    }
    void add_point(ptll p) { add_point(find(p, root), p); }
    static Tri* find(ptll p, Tri *r) {
        while (r->has_chd()) for (Tri *c: r->ch)
            if (c && c->contains(p)) { r = c; break; }
        return r;
    }
    void add_point(Tri *r, ptll p) {
        array<Tri*, 3> t; /* split into 3 triangles */
        F3 t[i] = new (it++) Tri(r->p[i], r->p[R(i)], p);
        F3 link(E(t[i], 0), E(t[R(i)], 1));
        F3 link(E(t[i], 2), r->e[L(i)]);
        r->ch = t;
        F3 flip(t[i], 2);
    }
    void flip(Tri* A, int a) {
        auto [B, b] = A->e[a]; /* flip edge between A,B */
        if (!B || !in_cc(A->p, B->p[b])) return;
        Tri *X = new(it++) Tri(A->p[R(a)], B->p[b], A->p[a]);
        Tri *Y = new(it++) Tri(B->p[R(b)], A->p[a], B->p[b]);
        link(E(X, 0), E(Y, 0));
        link(E(X, 1), A->e[L(a)]);
        link(E(X, 2), B->e[R(b)]);
        link(E(Y, 1), B->e[L(b)]);
        link(E(Y, 2), A->e[R(a)]);
        A->ch = B->ch = {X, Y, nullptr};
        flip(X, 1); flip(X, 2); flip(Y, 1); flip(Y, 2);
    }
};
vector<Tri*> res;
void go(Tri *now) { // store all tri into res
    if (now->vis) return;
    now->vis = true;
    if (!now->has_chd()) res.push_back(now);
    for (Tri *c : now->ch) if (c) go(c);
}
vector<Directed_Line> frame;
vector<vector<ptld>> build_voronoi_cells(const vector<ptll> &p, const vector<Tri*> &res); // Only need for voronoi
// !!! The order is shuffled !!!
vector<vector<ptld>> build(vector<ptll> &ps) {
    it = pool; res.clear();
    shuffle(ps.begin(), ps.end(), mt19937(487638763));
    Trigs tr; for (point p : ps) tr.add_point(p);
    go(tr.root); // use `res` afterwards
    return build_voronoi_cells(ps, res); // Only needed for voronoi
    // res is the result otherwise
}
