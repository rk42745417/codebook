template<typename T>
struct point {
    T x, y;
    point(): x(0), y(0) { }
    point(T a, T b): x(a), y(b) { }
    template<typename V>
    explicit point(point<V> p): x(p.x), y(p.y) { }
    point operator-(const point &b) const {
        return point(x - b.x, y - b.y);
    }
    point operator+(const point &b) const {
        return point(x + b.x, y + b.y);
    }
    point<ld> operator*(ld r) const {
        return point<ld>(x * r, y * r);
    }
    point<ld> operator/(ld r) const {
        return point<ld>(x / r, y / r);
    }
    point operator-() const { return point(-x, -y); }
    bool operator<(const point &b) const {
        return x == b.x ? y < b.y : x < b.x; }
    T dis2() const { return x * x + y * y; }
    ld dis() const { return sqrt(dis2()); }
    point perp() const { return point(-y, x); }
    point norm() const {
        ld d = dis();
        return *this / d;
    }
    point rot(double o) const {
        double c = cos(o), s = sin(o);
        return point(c * a.x - s * a.y, s * a.x + c * a.y);
    }
};
using ptld = point<ld>;
using ptll = point<ll>;
template<typename T>
T cross(const point<T> &a, const point<T> &b, const point<T> &c) {
    auto x = b - a, y = c - a;
    return x.x * y.y - y.x * x.y;
}
template<typename T>
T cross2(const point<T> &x, const point<T> &y) {
    return x.x * y.y - y.x * x.y;
}
template<typename T>
T dot(const point<T> &a, const point<T> &b, const point<T> &c) {
    auto x = b - a, y = c - a;
    return x.x * y.x + x.y * y.y;
}
template<typename T>
ld area(const point<T> &a, const point<T> &b, const point<T> &c) {
    return ld(cross(a, b, c)) / 2;
}
int sgn(ld v) {
    if (abs(v) < EPS)
        return 0;
    return v > 0 ? 1 : -1;
}
int sgn(ll v) { return (v > 0 ? 1 : (v < 0 ? -1 : 0)); }
template<typename T>
int ori(point<T> a, point<T> b, point<T> c) {
    return sgn(cross(a, b, c));
}
template<typename T>
bool collinearity(point<T> a, point<T> b, point<T> c) {
    return ori(a, b, c) == 0;
}
template<typename T>
bool btw(point<T> p, point<T> a, point<T> b) {
    return collinearity(p, a, b) && sgn(dot(p, a, b)) <= 0;
}
template<typename T>
point<ld> projection(point<T> p1, point<T> p2, point<T> p3) {
    return (p2 - p1) * dot(p1, p2, p3) / (p2 - p1).dis2();
}
template<typename T>
int quad(point<T> a) {
    if (a.x == 0 && a.y == 0) // change this for ld
        return -1;
    if (a.x > 0)
        return a.y > 0 || a.y == 0 ? 0 : 3;
    if (a.x < 0)
        return a.y > 0 ? 1 : 2;
    return a.y > 0 ? 1 : 3;
}
template<typename T>
bool cmp_by_polar(const point<T> &a, const point<T> &b) {
    // start from positive x-axis
    // Undefined if a or b is the origin
    if (quad(a) != quad(b))
        return quad(a) < quad(b);
    if (ori(point<T>(), a, b) == 0)
        return a.dis2() < b.dis2();
    return ori(point<T>(), a, b) > 0;
}
int arg_quad(ptll p) {
    return (p.y == 0) // use sgn for ptld
        ? (p.x < 0 ? 3 : 1) : (p.y < 0 ? 0 : 2);
}
template<typename T>
int arg_cmp(point<T> a, point<T> b) {
  // returns 0/+-1, starts from theta = -PI
  int qa = arg_quad(a), qb = arg_quad(b);
  if (qa != qb) return sgn(ll(qa - qb));
  return sgn(cross2(b, a));
}
using Line = pair<ptll, ptll>;
bool seg_intersect(Line a, Line b) {
    auto [p1, p2] = a;
    auto [p3, p4] = b;
    tie(p1, p2) = a;
    tie(p3, p4) = b;
    if (btw(p1, p3, p4) || btw(p2, p3, p4) || btw(p3, p1, p2) || btw(p4, p1, p2))
        return true;
    return ori(p1, p2, p3) * ori(p1, p2, p4) < 0 &&
        ori(p3, p4, p1) * ori(p3, p4, p2) < 0;
}
ptld intersect(Line a, Line b) {
    ptll p1, p2, p3, p4;
    tie(p1, p2) = a;
    tie(p3, p4) = b;
    ld a123 = cross(p1, p2, p3);
    ld a124 = cross(p1, p2, p4);
    return (p4 * a123 - p3 * a124) / (a123 - a124);
}
