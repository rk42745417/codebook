// O(NlogN), undefined if the result has area INF (not enclosed)
struct Directed_Line {
    ptll st, ed, dir;
    Directed_Line(ptll s, ptll e) : st(s), ed(e), dir(e - s) {}
};
using LN = const Directed_Line &;
ptld intersect(LN A, LN B) {
    ld t = cross2(B.st - A.st, B.dir) / ld(cross2(A.dir, B.dir));
    return ptld(A.st) + A.dir * t; // C^3 / C^2
}
int sgn(__int128 v) { return (v > 0 ? 1 : (v < 0 ? -1 : 0)); }
bool cov(LN l, LN A, LN B) {
    __int128 u = cross2(B.st - A.st, B.dir);
    __int128 v = cross2(A.dir, B.dir);
    // ori(l.st, l.ed, A.st + A.dir*(u/v)) <= 0?
    __int128 x = (A.dir).x * u + (A.st - l.st).x * v;
    __int128 y = (A.dir).y * u + (A.st - l.st).y * v;
    return sgn(x * (l.dir).y - y * (l.dir).x) * sgn(v) >= 0;
} // x, y are C^3
bool operator<(LN a, LN b) {
    if (int c = arg_cmp(a.dir, b.dir)) return c == -1;
    return ori(a.st, a.ed, b.st) < 0;
}
// cross(pt-line.st, line.dir)<=0 <-> pt in half plane
// the half plane is the LHS when going from st to ed
vector<ptld> HPI(vector<Directed_Line> &q) {
    sort(q.begin(), q.end());
    int n = (int)q.size(), l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        if (i && !arg_cmp(q[i].dir, q[i - 1].dir)) continue;
        while (l < r && cov(q[i], q[r-1], q[r])) --r;
        while (l < r && cov(q[i], q[l], q[l + 1])) ++l;
        q[++r] = q[i];
    }
    while (l < r && cov(q[l], q[r-1], q[r])) --r;
    while (l < r && cov(q[r], q[l], q[l+1])) ++l;
    n = r - l + 1; // q[l .. r] are the lines
    if (n <= 1 || !arg_cmp(q[l].dir, q[r].dir)) return { };
    vector<ptld> pt(n);
    for (int i = 0; i < n; i++)
        pt[i] = intersect(q[i + l], q[(i + 1) % n + l]);
    return pt;
}
