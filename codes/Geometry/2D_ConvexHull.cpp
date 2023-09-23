// returns a convex hull in counterclockwise order
// for a non-strict one, change cross >= to >
// Be careful of n <= 2
vector<point> convex_hull(vector<point> p) {
    sort(p.begin(), p.end());
    if (p[0] == p.back()) return { p[0] };
    int s = 1, t = 0;
    vector<point> h(p.size() + 1);
    for (int _ = 2; _--; s = t--, reverse(p.begin(), p.end()))
        for (point i : p) {
            while (t > s && ori(i, h[t - 1], h[t - 2]) >= 0)
                t--;
            h[t++] = i;
        }
    return h.resize(t), h;
}
