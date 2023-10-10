bool in_convex(const vector<point> &convex, point p, bool strict = true) {
    if (convex.empty())
        return false;
    int a = 1, b = convex.size() - 1, r = !strict;
    if (b < 2)
        return r && btw(p, convex[0], convex.back());
    if (ori(convex[0], convex[a], convex[b]) > 0) swap(a, b);
    if (ori(convex[0], convex[a], p) >= r || ori(convex[0], convex[b], p) <= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (ori(convex[0], convex[c], p) > 0 ? b : a) = c;
    }
    return ori(convex[a], convex[b], p) < r;
} // no tested
