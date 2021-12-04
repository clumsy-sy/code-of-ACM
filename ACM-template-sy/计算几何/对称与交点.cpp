// 对称，点和向量此处不同
// 关于点对称
Point reflect(Point A, Point P) { return {P.x * 2 - A.x, P.y * 2 - A.y}; }
Line reflect(Line l, Point P) { return {reflect(l.p, P), l.v}; }
Seg reflect(Seg l, Point P) { return {reflect(l.a, P), reflect(l.b, P)}; }
// 关于直线对称
// NOTE 向量和点在这里的表现不同，求向量关于某直线的对称向量需要用reflect_v
Point reflect(Point A, Line ax) { return reflect(A, pedal(A, ax)); } 
Vec reflect_v(Vec v, Line ax) { return reflect(v, ax) - reflect(Point(0, 0), ax); }
Line reflect(Line l, Line ax) { return {reflect(l.p, ax), reflect_v(l.v, ax)}; }
Seg reflect(Seg l, Line ax) { return {reflect(l.a, ax), reflect(l.b, ax)}; }
// 交点
// 直线与直线交点
vector<Point> inter(Line a, Line b) {
    double c = a.v ^ b.v;
    if (cmp(c, 0) == 0) return {};
    Vec v = Vec{a.p ^ (a.p + a.v), b.p ^ (b.p + b.v)} * 1 / c;
    return {{v * Vec{-b.v.x, a.v.x}, v * Vec{-b.v.y, a.v.y}}};
}
// 直线与圆交点
vector<Point> inter(Line l, Circle C) {
    Point P = pedal(C.O, l);
    double h = (P - C.O).len();
    if (cmp(h, C.r) > 0) return {};
    if (cmp(h, C.r) == 0) return {P};
    double d = sqrt(C.r * C.r - h * h);
    Vec vec = l.v * (d / l.v.len());
    return {P + vec, P - vec};
}
// 圆与圆的交点
vector<Point> inter(Circle C1, Circle C2) {
    Vec v1 = C2.O - C1.O, v2 = v1.r90c();
    double d = v1.len();
    if (cmp(d, C1.r + C2.r) > 0 || cmp(abs(C1.r - C2.r), d) > 0) return {};
    if (cmp(d, C1.r + C2.r) == 0 || cmp(d, abs(C1.r - C2.r)) == 0) return {C1.O + v1 * (C1.r / d)};
    double a = ((C1.r * C1.r - C2.r * C2.r) / d + d) / 2;
    double h = sqrt(C1.r * C1.r - a * a);
    Vec av = v1 * (a / v1.len()), hv = v2 * (h / v2.len());
    return {C1.O + av + hv, C1.O + av - hv};
}