vector<Line> tangent(Circle c, point p) {
    vector<Line> z;
    double d = (p - c.c).dis();
    if (sign(d - c.r) == 0) {
        point i = (p - c.c)rot(PI / 2);
        z.push_back({p, p + i});
    } else if (d > c.r) {
        double o = acos(c.r / d);
        point i = (p - c.c).norm(), j = i.rot(o) * c.r, k = i.rot(-o) * c.r;
        z.push_back({c.c + j, p});
        z.push_back({c.c + k, p});
    }
    return z;
} // not tested
