struct Line {    // 直线（点向式）
    Point p; Vec v;
    Line (Point a, Point b) { p = a, v = b - a; }                 // 点向式
    Line (double k, double b) { p = Point(0, b), v = Vec(1, k); } // 斜截式
    Line (Point P, double k) { p = P, v = Vec(1, k); }            // 点斜式直线
    // Line (Seg l) { return {l.a, l.b - l.a}; }                  // 线段所在直线
    Line rotate(Line l, double rad, Point C = Point(0, 0)) { return Line(l.p.rotate(rad, C), l.v.rotate(rad));}
    Line operator+(Vec t) { return {p + t, v}; }          // 位移一个向量的距离
    void toString() {cout << "直线基点坐标为 " << p.x << " " << p.y << "  方向 ：" << v.x << " " <<  v.y << endl;}
};
struct Seg {       // 线段（存两个端点）
    Point a, b;
    Seg(Point a, Point b) : a(a), b(b) {}
    Seg rotate(Seg l, double rad, Point C = Point(0, 0)) { return Seg(l.a.rotate(rad, C), l.b.rotate(rad, C));}
    Seg operator+(Vec t) { return {a + t, b + t}; }      // 位移一个向量的距离
    bool operator==(const Seg& t) { return (a == t.a && b == t.b) || (a == t.b && b == t.a); }
    void toString() {cout << "两端点坐标为 ： " << a.x << " " << a.y << " ； " << b.x << " " <<  b.y << endl;}
};
struct Circle {    // 圆（存圆心和半径）
    Point O; double r;
    Circle(Point _O, double _r) : O(_O), r(_r) {}
};
//给定直线的横坐标求纵坐标  // NOTE 请确保直线不与y轴平行
double at_x(Line l, double x) { return l.p.y + (x - l.p.x) * l.v.y / l.v.x; }
// 给定直线的纵坐标求横坐标// NOTE 请确保直线不与x轴平行
double at_y(Line l, double y) { return l.p.x - (l.p.y - y) * l.v.x / l.v.y; }
// 点到直线的垂足
Point pedal(Point P, Line l) { return l.p - l.v * ((l.p - P) * l.v / (l.v * l.v)); }
// 过某点作直线的垂线
Line perp(Line l, Point P) { return {P, l.v.r90c()}; }
// 角平分线
Line bisec(Point P, Vec u, Vec v) { return {P, u.norm() + v.norm()}; }
// 线段中点
Point midp(Seg l) { return Point((l.a.x + l.b.x) / 2, (l.a.y + l.b.y) / 2); }
// 线段中垂线
Line perp(Seg l) { return {midp(l), (l.b - l.a).r90c()}; }
// 点是否在直线上
bool on(Point P, Line l) { return cmp((P.x - l.p.x) * l.v.y, (P.y - l.p.y) * l.v.x) == 0; }
// 点是否在线段上
bool on(Point P, Seg l) { return cmp((P - l.a).len() + (P - l.b).len(), (l.a - l.b).len()) == 0; }
// 两条直线是否重合
bool operator==(Line a, Line b) { return on(a.p, b) && on(a.p + a.v, b); }
// 直线与圆是否相切
bool tangency(Line l, Circle C) { return cmp(abs((C.O ^ l.v) - (l.p ^ l.v)), C.r * l.v.len()) == 0; }
// 圆与圆是否相切
bool tangency(Circle C1, Circle C2) { return cmp((C1.O - C2.O).len(), C1.r + C2.r) == 0; }
// 两点间的距离
double dis(Point A, Point B) { return (A - B).len(); }
// 点到直线的距离
double dis(Point P, Line l) { return abs((P ^ l.v) - (l.p ^ l.v)) / l.v.len(); }
//点P到线段AB距离
double dis_PtoSeg(Point p, Seg s){
    if(s.a == s.b) return (p - s.a).len();//AB重合
    Vec x = p - s.a, y = p - s.b, z = s.b - s.a;
    if(cmp(x * z, 0) == -1)return x.len();//P距离A更近
    if(cmp(y * z, 0) == -1)return y.len();//P距离B更近
    return abs( (x ^ z) / z.len());//面积除以底边长
}
// 平行直线间的距离(请确保两直线平行)
double dis(Line a, Line b) { return abs((a.p ^ a.v.pnorm()) - (b.p ^ b.v.pnorm())); }
//判断两线段是否相交
bool seg_intersection(Point a1, Point a2, Point b1, Point b2){
    double c1 = (a2 - a1) ^ (b1 - a1), c2 = (a2 - a1) ^ (b2 - a1);
    double c3 = (b2 - b1) ^ (a2 - b1), c4 = (b2 - b1) ^ (a1 - b1);
    return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;//不算端点
}
bool seg_intersection(Seg s1, Seg s2) {
    double c1 = (s1.b - s1.a) ^ (s2.a - s1.a), c2 = (s1.b - s1.a) ^ (s2.b - s1.a);
    double c3 = (s2.b - s2.a) ^ (s1.b - s2.a), c4 = (s2.b - s2.a) ^ (s1.a - s2.a);
    return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;// 算端点
}