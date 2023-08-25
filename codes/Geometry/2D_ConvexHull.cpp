// returns a convex hull in counterclockwise order
// for a non-strict one, change cross >= to >
vector<point> convex_hull(vector<point> p) {
    sort(p.begin(), p.end());
    if (p[0] == p.back()) return {p[0]};
    int n = p.size(), t = 0;
    vector<point> h(n + 1);
    for (int _ = 2, s = 0; _--; s = --t, reverse(p.begin(), p.end()))
        for (point i : p) {
            while (t > s + 1 && cross(i, h[t-1], h[t-2])>=0)
                t--;
            h[t++] = i;
        }
    return h.resize(t), h;
} // not tested, but trust ckiseki!
