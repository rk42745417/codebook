struct Circle {
    point c;
    double r;
};

// Calculate intersection between given circle and line
vector<point> inter_circle_line(Circle cir, Line l) {
    const auto &[c, r] = cir;
    const auto &[a, b] = l;
    point p = a + (b - a) * dot(a, b, c) / (b - a).dis2();
    double s = cross(a, b, c), h2 = r * r - s * s / (b - a).dis2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    point h = (b - a) / (b - a).dis() * sqrt(h2);
    return {p - h, p + h};
} // no tested

// return p4 is strictly in circumcircle of tri(p1,p2,p3)
inline ll sqr(ll x) { return x * x; }
bool in_cc(const point& p1, const point& p2, const point& p3, const point& p4) {
    ll u11 = p1.x - p4.x; ll u12 = p1.y - p4.y;
    ll u21 = p2.x - p4.x; ll u22 = p2.y - p4.y;
    ll u31 = p3.x - p4.x; ll u32 = p3.y - p4.y;
    ll u13 = sqr(p1.x) - sqr(p4.x) + sqr(p1.y) - sqr(p4.y);
    ll u23 = sqr(p2.x) - sqr(p4.x) + sqr(p2.y) - sqr(p4.y);
    ll u33 = sqr(p3.x) - sqr(p4.x) + sqr(p3.y) - sqr(p4.y);
    __int128 det = (__int128)-u13 * u22 * u31 + (__int128)u12 * u23 * u31 + (__int128)u13 * u21 * u32 - (__int128)u11 * u23 * u32 - (__int128)u12 * u21 * u33 + (__int128)u11 * u22 * u33;
    return det > EPS;
} // not tested

// Return the area of intersection of poly and circle
double _area(point pa, point pb, double r) {
    if (pa.dis2() < pb.dis2())
        swap(pa, pb);
    if (pb.dis() < EPS)
        return 0;
    double S, h, theta;
    double a = pb.dis(), b = pa.dis(), c = (pb - pa).dis();
    double cosB = dot2(pb, pb - pa) / a / c, B = acos(cosB);
    double cosC = dot2(pa, pb) / a / b, C = acos(cosC);
    if (a > r) {
        S = (C / 2) * r * r;
        h = a * b * sin(C) / c;
        if (h < r && B < PI / 2)
            S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
    }
    else if (b > r) {
        theta = PI - B - asin(sin(B) / r * a);
        S = 0.5 * a * r * sin(theta) + (C - theta) / 2 * r * r;
    }
    else S = 0.5 * sin(C) * a * b;
    return S;
}
double area_poly_circle(const vector<point> poly, const Circle c) {
    const auto &[O, r] = c;
    double S = 0;
    for (int i = 0; i < poly.size(); ++i)
        S +=_area(poly[i] - O, poly[(i + 1) % poly.size()] - O, r) * ori(O, poly[i], poly[(i + 1) % poly.size()]);
    return abs(S);
} // not tested

// Return intersection of two circles in p1 and p2
bool CCinter(Circle &a, Circle &b, point &p1, point &p2) {
    point o1 = a.O, o2 = b.O;
    double r1 = a.r, r2 = b.r, d2 = (o1 - o2).dis2(), d = sqrt(d2);
    if (d < max(r1, r2) - min(r1, r2) || d > r1 + r2) return 0;
    point u = (o1 + o2) * 0.5 + (o1 - o2) * ((r2 * r2 - r1 * r1) / (2 * d2));
    double A = sqrt((r1 + r2 + d) * (r1 - r2 + d) * (r1 + r2 - d) * (-r1 + r2 + d));
    point v = point(o1.Y - o2.Y, -o1.X + o2.X) * A / (2 * d2);
    p1 = u + v, p2 = u - v;
    return 1;
} // not tested
