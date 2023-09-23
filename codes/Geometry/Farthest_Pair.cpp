// p is CCW convex hull w/o colinear points
void farthest_pair(vecotr<point> p) {
    int n = p.size(), pos = 1; lld ans = 0;
    for (int i = 0; i < n; i++) {
        P e = p[(i + 1) % n] - p[i];
        while (cross(e, p[(pos + 1) % n] - p[i]) >
                cross(e, p[pos] - p[i]))
            pos = (pos + 1) % n;
        for (int j: {i, (i + 1) % n})
            ans = max(ans, norm(p[pos] - p[j]));
    } // tested @ AOJ CGL_4_B
}
