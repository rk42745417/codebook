vector <Line> tangent(Circle c1, Circle c2, int sign1) {
    // sign1 = 1 for outer tang, -1 for inter tang
    vector <Line> ret;
    double d_sq = abs2(c1.c - c2.c);
    if (sgn(d_sq) == 0) return ret;
    double d = sqrt(d_sq);
    point v = (c2.c - c1.c) / d;
    double c = (c1.r - sign1 * c2.r) / d;
    if (c * c > 1) return ret;
    double h = sqrt(max(0.0, 1.0 - c * c));
    for (int sign2 = 1; sign2 >= -1; sign2 -= 2) {
        point n = point(v.x * c - sign2 * h * v.y, v.y * c + sign2 * h * v.x);
        point p1 = c1.c + n * c1.r;
        point p2 = c2.c + n * (c2.r * sign1);
        if (sign(p1.x - p2.x) == 0 && sign(p1.y - p2.y) == 0)
            p2 = p1 + (c2.c - c1.c).perp();
        ret.push_back({p1, p2});
    }
    return ret;
} // not tested
