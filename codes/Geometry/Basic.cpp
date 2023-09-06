struct point {
    ld x, y;
    point() { }
    point(ld a, ld b): x(a), y(b) { }
    point operator-(const point &b) const {
        return point(x - b.x, y - b.y);
    }
    point operator+(const point &b) const {
        return point(x + b.x, y + b.y);
    }
    point operator*(ld r) const {
        return point(x * r, y * r);
    }
    point operator/(ld r) const {
        return point(x / r, y / r);
    }
    bool operator<(const point &b) const {
        return x == b.x ? y < b.y : x < b.x; }
    ld dis2() { return x * x + y * y; }
    ld dis() { return sqrt(dis2()); }
    point perp() { return point(-y, x); }
    point norm() {
        ld d = dis();
        return point(x / d, y / d);
    }
};
ld cross(const point &a, const point &b, const point &c) {
    auto x = b - a, y = c - a;
    return x.x * y.y - y.x * x.y;
}
ld dot(const point &a, const point &b, const point &c) {
    auto x = b - a, y = c - a;
    return x.x * y.x + x.y * y.y;
}
ld area(const point &a, const point &b, const point &c) {
    return ld(cross(a, b, c)) / 2;
}
static inline bool eq(ld a, ld b) { return abs(a - b) < EPS; }
int sgn(ld v) {
    return v > 0 ? 1 : (v < 0 ? -1 : 0);
}
int ori(point a, point b, point c) {
    return sgn(cross(a, b, c));
}
bool collinearity(point a, point b, point c) {
    return ori(a, b, c) == 0;
}
bool btw(point p, point a, point b) {
    return collinearity(p, a, b) && sgn(dot(p, a, b)) <= 0;
}
point projection(point p1, point p2, point p3) {
    return (p2 - p1) * dot(p1, p2, p3) / (p2 - p1).dis2();
}
using Line = pair<point, point>;
bool seg_intersect(Line a, Line b) {
    point p1, p2, p3, p4;
    tie(p1, p2) = a;
    tie(p3, p4) = b;
    if (btw(p1, p3, p4) || btw(p2, p3, p4) || btw(p3, p1, p2) || btw(p4, p1, p2))
        return true;
    return ori(p1, p2, p3) * ori(p1, p2, p4) < 0 &&
        ori(p3, p4, p1) * ori(p3, p4, p2) < 0;
}
point intersect(Line a, Line b) {
    point p1, p2, p3, p4;
    tie(p1, p2) = a;
    tie(p3, p4) = b;
    ld a123 = cross(p1, p2, p3);
    ld a124 = cross(p1, p2, p4);
    return (p4 * a123 - p3 * a124) / (a123 - a124);
}
