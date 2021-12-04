# 计算几何

## 基础准备
```cpp
const double eps = 1e-8; 
const double PI = acos(-1);
// 符号函数 (0 , -1, 1)
int sign(double x) { return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;}
// 比较函数(== 0, < -1, > 1)
int cmp(double x, double y) { return fabs(x - y) < eps ? 0 : x < y ? -1 : 1;}
// 弧度转角度 与 角度转弧度
double rad_to_deg (double x) { return 180 / PI * x;}
double deg_to_rad (double x) { return PI / 180 * x;}
// floor(x) 向下取整函数 ceil(x) 向上取整函数 round(x) 四舍五入函数
const Point O = {0, 0};                        // 原点
const Line Ox = {O, {1, 0}}, Oy = {O, {0, 1}}; // 坐标轴
const double PI = acos(-1), eps = 1e-9;
```
## 点与向量
```cpp
struct Point {     // 点
    double x, y;
    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    Point operator- (const Point& t) {return Point(x - t.x, y - t.y);}
    Point operator+ (const Point& t) {return Point(x + t.x, y + t.y);}
    Point operator* (double k) { return Point(k * x, k * y); } // 数乘
    Point operator/ (double k) { return Point(x / k, y / k); }
    double operator* (const Point& t) { return x * t.x + y * t.y; }// 点乘
    double operator^ (const Point& t) { return x * t.y - y * t.x; }// 叉乘
    Point r90a() { return Point(-y, x); } // 逆时针旋转90度
    Point r90c() { return Point(y, -x); } // 顺时针旋转90度
    Point rotate(double agl) {return Point(x * cos(agl) + y * sin(agl), -x * sin(agl) + y * cos(agl));} //弧度
    Point rotate(double agl, Point C) { return C + (*this - C).rotate(agl); }                     // DEPENDS ^1
    double len() { return sqrt(x * x + y * y); }
    double slope() { return y / x; } // 斜率,判不存在用paral_y
    Point norm() {return Point(x / this->len(), y / this->len());}
    Point pnorm() {return Point(x < 0 ? -1 : 1) / this->len()*(*this);}
    bool operator < ( const Point& t){ return x == t.x ? y < t.y : x < t.x; }
    bool operator==(const Point& t) { return cmp(x, t.x) == 0 && cmp(y, t.y) == 0;}
};
using Vec = Point; // 向量

double get_angle(Point a, Point b){ return acos(a * b / a.len() / b.len());} //求夹角(余弦弧度)
double area(Point a, Point b, Point c){return (b - a) ^ (c - a);} //求四边形面积(a为交点)
// 判断两向量的位置关系 (逆时针 1，顺时针 -1，重合（相反） 0)
int cmp_order(Point a, Point b) {double res = a ^ b;return sign(res);}
// 判断两向量夹角大小 (锐角 1， 钝角 -1， 直角 0， 重合 2，相反 -2)
int cmp_angle(Point a, Point b) {
    double res = a * b, res2 = a.len() * b.len();
    if (res == -res2) return -2;
    if (res == res2) return 2;
    return sign(res);
}
bool paral_x(Vec v) { return cmp(v.y, 0) == 0; }          // 向量是否与x轴平行
bool paral_y(Vec v) { return cmp(v.x, 0) == 0; }          // 向量是否与y轴平行
```

## 直线、线段与圆
```cpp
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
```

## 对称与交点
```cpp
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
```

## 三角形
三角形面积
两条边求叉积除二后的绝对值；
海伦公式：
$$
\begin{aligned}
&S = \sqrt{p(p - a)(p - b)(p - c)}, \ p = \dfrac{a + b + c}{2} \\
&S = \dfrac{ab\sin{c}}{2}
\end{aligned}
$$
```cpp
// 三角形的四心
// 三角形的重心
Point barycenter(Point A, Point B, Point C){
    return {(A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3};
}
// 三角形的外心
// DEPENDS r90c, V*V, d*V, V-V, V+V
// NOTE 给定圆上三点求圆，要先判断是否三点共线
Point circumcenter(Point A, Point B, Point C) {
    double a = A * A, b = B * B, c = C * C;
    double d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    return ((B - C) * a + (C - A) * b + (A - B) * c).r90c() * (1 / d);
}
// 三角形的内心
// DEPENDS len, d*V, V-V, V+V
Point incenter(Point A, Point B, Point C) {
    double a = (B - C).len(), b = (A - C).len(), c = (A - B).len();
    double d = a + b + c;
    return (A * a + B * b + C * c) * (1 / d);
}
// 三角形的垂心
// DEPENDS V*V, d*V, V-V, V^V, r90c
Point orthocenter(Point A, Point B, Point C) {
    double n = B * (A - C), m = A * (B - C);
    double d = (B - C) ^ (A - C);
    return ((C - B) * n - (C - A) * m).r90c() * (1 / d);
}
```

## 小技巧
给三点坐标求第四点坐标
```cpp
//求矩形的第四个点的函数 //已知A(a.x,a.y),B(b.x,b.y),C(c.x,c.y)，求D(dx,dy) 
double sqr(int x) {return x * x;}
Point get_4th(Point a, Point b, Point c) {
//ab表示AB^2,ac表示AC^2,BC表示BC^2 
    int ab = sqr( a.x - b.x ) + sqr( a.y - b.y ),
        ac = sqr( a.x - c.x ) + sqr( a.y - c.y ),
        bc = sqr( b.x - c.x ) + sqr( b.y - c.y );
    int dx, dy;
//用勾股定理的逆定理，判断谁是直角边,再根据矩形对边平行的性质，算出第四个点的坐标 
    if (ab + ac == bc) dx = b.x + c.x - a.x, dy = b.y + c.y - a.y;
    if (ab + bc == ac) dx = a.x + c.x - b.x, dy = a.y + c.y - b.y;
    if (ac + bc == ab) dx = a.x + b.x - c.x, dy = a.y + b.y - c.y;
    return Point(dx, dy);
}
```
两圆相交面积
```cpp
double AreaOfOverlap(Point c1, double r1, Point c2, double r2){
    double d = (c1 - c2).len();
    if(r1 + r2 < d + eps) return 0.0;
    if(d < fabs(r1 - r2) + eps){
        double r = min(r1, r2);
        return PI * r * r;
    }
    double x = (d * d + r1 * r1 - r2 * r2) / (2.0 * d);
    double p = (r1 + r2 + d) / 2.0;
    double t1 = acos(x / r1);
    double t2 = acos((d - x) / r2);
    double s1 = r1 * r1 * t1;
    double s2 = r2 * r2 * t2;
    double s3 = 2 * sqrt(p * (p - r1) * (p - r2) * (p - d));
    return s1 + s2 - s3;
}
```
三点确定外接圆圆心坐标
```cpp
Point Excenter(Point a, Point b, Point c){
    double a1 = b.x - a.x, b1 = b.y - a.y;
    double c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y;
    double c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
}
```

## 多边形
任意凸多边形的外角和均为 $360\degree$
任意 $n$ 凸多边形内角和为 $(n - 2) 180 \degree$

### 判断点在多边形内
winding number 算法
```cpp
//判断点是否在多边形内，若点在多边形(内 : 1，外 ： 0，上 ： -1）
int isPointInPolygon(Point p, vector<Point> poly){
    int wn = 0;
    int n = poly.size();
    for(int i = 0; i < n; ++i){
        if(on(p, Seg(poly[i], poly[(i+1)%n]))) return -1;
        int k = sign((poly[(i+1)%n] - poly[i]) ^  (p - poly[i]));
        int d1 = sign(poly[i].y - p.y), d2 = sign(poly[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn ++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn --;
    }
    if(wn != 0) return 1;
    return 0;
}
bool judge(Point a,Point L,Point R){//判断AL是否在AR右边
    return sign((L-a) ^ (R-a)) > 0;//必须严格以内
}
//二分判断点是否在凸多边形内，若点在多边形(内 : 1，外 ： 0，上 ： -1）
int isPointInConvexPolygon(Point a, vector<Point> poly){
    int n = poly.size();//点按逆时针给出(一定要满足这个条件)
    if(judge(poly[0], a, poly[1]) || judge(poly[0], poly[n - 1], a))return 0;//在P[0_1]或P[0_n - 1]外
    if(on(a, Seg(poly[0], poly[1])) || on(a, Seg(poly[0], poly[n - 1])))return -1;//在P[0_1]或P[0_n-1]上
    int l = 1,r = n - 2;
    while(l < r){//二分找到一个位置pos使得P[0]_A在P[1_pos],P[1_(pos+1)]之间
        int mid = (l + r) >> 1;
        if(judge(poly[1], poly[mid], a))l = mid;
        else r = mid - 1;
    }
    if(judge(poly[l], a, poly[l + 1]))return 0;//在P[pos_(pos+1)]外
    if(on(a, Seg(poly[l], poly[l + 1])))return -1;//在P[pos_(pos+1)]上
    return 1;
}
//【判断多边形A与多边形B是否相离】 
int judge_PP(vector<Point> A, vector<Point> B){
    for(int i = 0; i < A.size(); ++ i) {
        for(int j = 0; j < B.size(); ++ j) {
            if(seg_intersection(Seg(A[i], A[(i + 1) % A.size()]), Seg(B[j], B[(j + 1) % B.size()])))return 0;//两线段相交
            if(isPointInConvexPolygon(A[i], B) || isPointInConvexPolygon(B[j], A))return 0; //点包含在内
        }
    }
    return 1;
}
```
若这个多边形为凸多边形，只需要判断点是否在所有边的左边即可（按逆时针顺序排列的顶点集）
**判断线段是否在任意多边形内**
1. 选段与多边形不相交
2. 两端点都在多边形内

**计算多边形面积**

```cpp
double PolyArea(Point p[], int n) {
    double res = 0.0;
    for(int i = 0 ; i < n; i ++)
        res += p[i] ^ p[(i + 1) % n];
    return res / 2;
}
double PolyArea(Point p[], int n) {
    double res = 0.0;
    for(int i = 0 ; i < n - 1; i ++)
        res += (p[i] - p[0]) ^ (p[(i + 1) % n] - p[i]);
    return res / 2;
}
```

### Pick 定理
计算顶点都在格点上的多边形的面积公式, $a$ 表示多边形内的点数，$b$ 表示多边形边界上的点数， $S$ 表示多边形面积。
$$
2S = 2a + b - 2, \ S = a + \dfrac{b}{a} - 1
$$
给多边形顶点求内部有多少点
$$
a = S - \dfrac{b}{2} + 1
$$
## 凸包
### 二维凸包
```cpp
const int M = 1e5 + 7;
int sta[M], n; // 单调栈
bool st[M];    // 标记此点是否被选取
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    Point operator-(Point b){return Point(x - b.x, y - b.y);}
    bool operator<(Point b){return x < b.x;}
}p[M];
double cross(Point a, Point b) {return a.x * b.y - a.y * b.x;}
double distanc(Point a, Point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double solve(){
    int hh = 0; // 上凸壳
    for(int i = 1; i <= n; i ++) {
        // 通过叉积判断两个线段之间的位置关系
        while(hh >= 2 && cross(p[sta[hh]] - p[sta[hh - 1]], p[i] - p[sta[hh - 1]]) > 0) 
            st[sta[hh --]] = false;
        st[i] = true;
        sta[++ hh] = i; // 新入栈
    }
    // 下凸壳
    st[1] = false; // 1 这个点也需要更新
    for(int i = n; i; i --) {
        if(st[i]) continue; // 求下凸壳时不影响上凸壳
        while(hh >= 2 && cross(p[sta[hh]] - p[sta[hh - 1]], p[i] - p[sta[hh - 1]]) > 0)
            hh --;
        sta[++ hh] = i;
    }
    double ans = 0.0;
    for(int i = 2; i <= hh; i ++)
        ans += distanc(p[sta[i]], p[sta[i - 1]]);
    return ans;
}
int main() {
    n = read();
    for(int i = 1; i <= n; i ++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        p[i] = Point(x, y);
    }
    sort(p + 1, p + n + 1); // 双关键字排序
    printf("%.2lf\n", solve());
    return 0;
}
```
### 三维凸包
```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 210;
const double eps = 1e-12;
int n, m;
bool g[N][N];
double rand_eps() { return ((double)rand() / RAND_MAX - 0.5) * eps;}
struct Point {
    double x, y, z;
    void shake() { x += rand_eps(), y += rand_eps(), z += rand_eps();} // 扰动
    Point operator-(Point t) { return {x - t.x, y - t.y, z - t.z};}
    double operator^(Point t) { return x * t.x + y * t.y + z * t.z;}
    Point operator*(Point t) { return {y * t.z - t.y * z, z * t.x - x * t.z, x * t.y - y * t.x};}
    double len() { return sqrt(x * x + y * y + z * z);}
} q[N];
struct Plane {
    int v[3];
    Point norm(){ return (q[v[1]] - q[v[0]]) * (q[v[2]] - q[v[0]]);} // 法向量
    double area(){ return norm().len() / 2;} // 求面积
    bool above(Point a) { return ((a - q[v[0]]) ^ norm()) >= 0;}
} plane[N], np[N];
void get_convex_3d() {
    plane[m++] = {0, 1, 2};
    plane[m++] = {2, 1, 0};
    for (int i = 3; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            bool t = plane[j].above(q[i]);
            if (!t) np[cnt++] = plane[j];
            for (int k = 0; k < 3; k++)
                g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t;
        }
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 3; k++) {
                int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
                if (g[a][b] && !g[b][a])
                    np[cnt++] = {a, b, i};
            }
        m = cnt;
        for (int j = 0; j < m; j++)
            plane[j] = np[j];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z);
        q[i].shake();
    }
    get_convex_3d();
    double res = 0;
    for (int i = 0; i < m; i++)
        res += plane[i].area();
    printf("%lf\n", res);
    return 0;
}
```
### 动态凸包
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
ll n;
map<ll, ll> top, down;
bool check_top(ll x, ll y) {
    auto i = top.lower_bound(x);
    if (i == top.end()) return 0;
    if (i->first == x) return y <= i->second;
    if (i == top.begin()) return 0;
    auto j = i; j--;
    return (i->first - j->first) * (y - j->second) - (i->second - j->second) * (x - j->first) <=0;
}
bool check_down(ll x, ll y) {
    auto i = down.lower_bound(x);
    if (i == down.end()) return 0;
    if (i->first == x) return y >= i->second;
    if (i == down.begin()) return 0;
    auto j = i;
    j--;
    return (i->first - j->first) * (y - j->second) -(i->second - j->second) * (x - j->first) >= 0;
}
bool delete_top(map<ll,ll>::iterator i) {
    if (i == top.begin()) return 0;
    auto j = i, k = i;
    j--, k++;
    if (k == top.end()) return 0;
    if ((i->first - j->first) * (k->second - j->second) - (i->second - j->second) * (k->first - j->first) >= 0) {
        top.erase(i);
        return 1;
    }
    return 0;
}
bool delete_down(map<ll,ll>::iterator i) {
    if (i == down.begin()) return 0;
    auto j = i, k = i;
    j--, k++;
    if (k == down.end()) return 0;
    if ((i->first - j->first) * (k->second - j->second) - (i->second - j->second) * (k->first - j->first) <= 0) {
        down.erase(i);
        return 1;
    }
    return 0;
}
void insert_top(ll x, ll y) {
    if (check_top(x, y)) return;
    top[x] = y;
    auto i = top.find(x), j = i;
    if (i != top.begin()) {
        j--;
        while (delete_top(j++)) j--;
    }
    if (++j != top.end())
        while (delete_top(j--)) j++;
}
void insert_down(ll x, ll y) {
    if (check_down(x, y)) return;
    down[x] = y;
    auto i = down.find(x), j = i;
    if (i != down.begin()) {
        j--;
        while (delete_down(j++)) j--;
    }
    if (++j != down.end())
        while (delete_down(j--)) j++;
}
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        ll op , x , y ;
        scanf("%lld%lld%lld", &op, &x, &y);
        if (op == 1) {
            insert_top(x, y); //插入上凸包
            insert_down(x, y); //插入下凸包
        } else {
            if (check_top(x, y) && check_down(x, y))
                puts("YES");
            else
                puts("NO");
        }
    }
    return 0;
}
```

## 旋转卡壳
旋转卡壳思想配合凸包算法求解最远点对，也就是求凸包直径
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#define x first
#define y second

using namespace std;
typedef pair<int, int> PII;
const int N = 50010;
int n, stk[N], top;
PII q[N];
bool used[N];
PII operator-(PII a, PII b) { return {a.x - b.x, a.y - b.y}; }
int operator*(PII a, PII b) { return a.x * b.y - a.y * b.x; }
int area(PII a, PII b, PII c) { return (b - a) * (c - a); }
int get_dist(PII a, PII b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}
void get_convex() {
    sort(q, q + n);
    for (int i = 0; i < n; i++) {
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0) {
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[--top]] = false;
            else top--;
        }
        stk[top++] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i--) {
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
            top--;
        stk[top++] = i;
    }
    top--; // 首尾重复
}
// 旋转卡壳
int rotating_calipers() {
    if (top <= 2)
        return get_dist(q[0], q[n - 1]);
    int res = 0;
    for (int i = 0, j = 2; i < top; i++) {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (area(d, e, q[stk[j]]) < area(d, e, q[stk[j + 1]]))
            j = (j + 1) % top;
        res = max(res, max(get_dist(d, q[stk[j]]), get_dist(e, q[stk[j]])));
    }
    return res;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &q[i].x, &q[i].y);
    get_convex();
    printf("%d\n", rotating_calipers());
    return 0;
}
```
已知平面上不共线的一组点的坐标，求覆盖这组点的面积最小的矩形,输出矩形的面积和四个顶点的坐标。
```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#define x first
#define y second
using namespace std;
typedef pair<double, double> PDD;
const int N = 50010;
const double eps = 1e-12, INF = 1e20;
const double PI = acos(-1);
int n;
PDD q[N];
PDD ans[N];
double min_area = INF;
int stk[N], top;
bool used[N];
int sign(double x) { return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;}
int cmp(double x, double y) { return fabs(x - y) < eps ? 0 : x < y ? -1 : 1;}
PDD operator+(PDD a, PDD b) { return {a.x + b.x, a.y + b.y}; }
PDD operator-(PDD a, PDD b) { return {a.x - b.x, a.y - b.y}; }
PDD operator*(PDD a, double t) { return {a.x * t, a.y * t}; }
PDD operator/(PDD a, double t) { return {a.x / t, a.y / t}; }
double operator*(PDD a, PDD b) { return a.x * b.y - a.y * b.x; }
double operator&(PDD a, PDD b) { return a.x * b.x + a.y * b.y; }
double area(PDD a, PDD b, PDD c) { return (b - a) * (c - a); }
double get_len(PDD a) { return sqrt(a & a); }
double project(PDD a, PDD b, PDD c) { return ((b - a) & (c - a)) / get_len(b - a); }
PDD norm(PDD a) { return a / get_len(a); }
PDD rotate(PDD a, double b) { return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)}; }
void get_convex() {
    sort(q, q + n);
    for (int i = 0; i < n; i++) {
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            used[stk[--top]] = false;
        stk[top++] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i--) {
        if (used[i]) continue;
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            top--;
        stk[top++] = i;
    }
    reverse(stk, stk + top);
    top--;
}
void rotating_calipers() {
    for (int i = 0, a = 2, b = 1, c = 2; i < top; i++) {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (cmp(area(d, e, q[stk[a]]), area(d, e, q[stk[a + 1]])) < 0)
            a = (a + 1) % top;
        while (cmp(project(d, e, q[stk[b]]), project(d, e, q[stk[b + 1]])) < 0)
            b = (b + 1) % top;
        if (!i) c = a;
        while (cmp(project(d, e, q[stk[c]]), project(d, e, q[stk[c + 1]])) > 0)
            c = (c + 1) % top;
        auto x = q[stk[a]], y = q[stk[b]], z = q[stk[c]];
        auto h = area(d, e, x) / get_len(e - d);
        auto w = ((y - z) & (e - d)) / get_len(e - d);
        if (h * w < min_area) {
            min_area = h * w;
            ans[0] = d + norm(e - d) * project(d, e, y);
            ans[3] = d + norm(e - d) * project(d, e, z);
            auto u = norm(rotate(e - d, -PI / 2));
            ans[1] = ans[0] + u * h;
            ans[2] = ans[3] + u * h;
        }
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &q[i].x, &q[i].y);
    get_convex();
    rotating_calipers();
    int k = 0;
    for (int i = 1; i < 4; i++)
        if (cmp(ans[i].y, ans[k].y) < 0 ||!cmp(ans[i].y, ans[k].y) && cmp(ans[i].x, ans[k].x))
            k = i;
    printf("%.5lf\n", min_area);
    for (int i = 0; i < 4; i++, k++) {
        auto x = ans[k % 4].x, y = ans[k % 4].y;
        if (!sign(x)) x = 0;
        if (!sign(y)) y = 0;
        printf("%.5lf %.5lf\n", x, y);
    }
    return 0;
}
```

## 最小圆覆盖
在一个二维平面上给定 N 个点，画出一个最小的能够包含所有点的圆。
随机增量法，也从凸包直径中点开始跑模拟退火
```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#define x first
#define y second
using namespace std;
typedef pair<double, double> PDD;
const int N = 100010;
const double eps = 1e-12;
const double PI = acos(-1);
int n;
PDD q[N];
struct Circle {
    PDD p;
    double r;
};
int sign(double x) { return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;}
int cmp(double x, double y) { return fabs(x - y) < eps ? 0 : x < y ? -1 : 1;}
PDD operator-(PDD a, PDD b) { return {a.x - b.x, a.y - b.y}; }
PDD operator+(PDD a, PDD b) { return {a.x + b.x, a.y + b.y}; }
PDD operator*(PDD a, double t) { return {a.x * t, a.y * t}; }
PDD operator/(PDD a, double t) { return {a.x / t, a.y / t}; }
double operator*(PDD a, PDD b) { return a.x * b.y - a.y * b.x; }
PDD rotate(PDD a, double b) { return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)}; }
double get_dist(PDD a, PDD b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w) {
    auto u = p - q;
    double t = w * u / (v * w);
    return p + v * t;
}
pair<PDD, PDD> get_line(PDD a, PDD b) {
    return {(a + b) / 2, rotate(b - a, PI / 2)};
}
Circle get_circle(PDD a, PDD b, PDD c) {
    auto u = get_line(a, b), v = get_line(a, c);
    auto p = get_line_intersection(u.x, u.y, v.x, v.y);
    return {p, get_dist(p, a)};
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &q[i].x, &q[i].y);
    random_shuffle(q, q + n); // 随机打乱
    Circle c({q[0], 0});
    for (int i = 1; i < n; i++)
        if (cmp(c.r, get_dist(c.p, q[i])) < 0) {
            c = {q[i], 0};
            for (int j = 0; j < i; j++)
                if (cmp(c.r, get_dist(c.p, q[j])) < 0) {
                    c = {(q[i] + q[j]) / 2, get_dist(q[i], q[j]) / 2};
                    for (int k = 0; k < j; k++)
                        if (cmp(c.r, get_dist(c.p, q[k])) < 0)
                            c = get_circle(q[i], q[j], q[k]);
                }
        }
    printf("%.10lf\n", c.r);
    printf("%.10lf %.10lf\n", c.p.x, c.p.y);
    return 0;
}
```

## 半平面交
给很多多边形求面积并
```cpp
using namespace std;
const double INF = 1e12;
const double pi = acos(-1.0);
const double eps = 1e-8;
int sign(double x) { return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;}
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    Point operator+(Point B) {return Point(x + B.x, y + B.y);}
    Point operator-(Point B) {return Point(x - B.x, y - B.y);}
    Point operator*(double k) {return Point(x * k, y * k);}
};
typedef Point Vec;
double Cross(Vec A, Vec B) { return A.x * B.y - A.y * B.x; }//叉积
struct Line {
    Point p; Vec v;
    double ang;
    Line(Point p=Point(), Vec v=Point()) : p(p), v(v) {ang = atan2(v.y, v.x);}
    bool operator<(Line &L) {return ang < L.ang; }//用于极角排序
};
//点p在线L左边，即点p在线L在外面：
bool OnLeft(Line L, Point p) {return sign(Cross(L.v, p - L.p)) > 0;}
Point Cross_point(Line a, Line b) {//两直线交点
    Vec u = a.p - b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v * t;
}
vector<Point> HPI(vector<Line> L) {//求半平面交，返回图多边形
    int n = L.size();
    sort(L.begin(), L.end()); //将所有半平面按照极角排序。
    int first, last;    //指向双端队列的第一个和最后一个元素
    vector<Point> p(n); //两个相邻半平面的交点
    vector<Line> q(n);  //双端队列
    vector<Point> ans;  //半平面交形成的凸包
    q[first = last = 0] = L[0];
    for (int i = 1; i < n; i++) {
        //情况1：删除尾部的半平面
        while (first < last && !OnLeft(L[i], p[last - 1]))
            last--;
        //情况2：删除首部的半平面：
        while (first < last && !OnLeft(L[i], p[first]))
            first++;
        q[++last] = L[i]; //将当前的半平面加入双端队列尾部
        //极角相同的两个半平面，保留左边：
        if (fabs(Cross(q[last].v, q[last - 1].v)) < eps) {
            last--;
            if (OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        //计算队列尾部半平面交点：
        if (first < last) p[last - 1] = Cross_point(q[last - 1], q[last]);
    }
    //情况3：删除队列尾部的无用半平面
    while (first < last && !OnLeft(q[first], p[last - 1])) last--;
    if (last - first <= 1) return ans;    //空集
    p[last] = Cross_point(q[last], q[first]); //计算队列首尾部的交点。
    for (int i = first; i <= last; i++)
        ans.push_back(p[i]); //复制。
    return ans;              //返回凸多边形
}
double Polygon_area(vector<Point> p) {
    double area = 0;
    for (int i = 0; i < (int)p.size(); i++)
        area += Cross(p[i], p[(i + 1) % (int)p.size()]);
    return area / 2; //面积有正负，不能简单地取绝对值
}
int main() {
    int n, m;
    vector<Line> L; // 半平面
    cin >> n;
    while (n--) { //点坐标逆时针给出
        cin >> m;
        vector<Point> tmp; //点集
        for (int i = 0; i < m; i++) {
            double a, b;
            scanf("%lf%lf", &a, &b);
            tmp.push_back(Point(a, b));
        }
        for (int i = 0; i < m; i++) {
            L.push_back(Line(tmp[i], tmp[(i + 1) % m] - tmp[i]));
        }
    }
    vector<Point> ans = HPI(L); //得到凸多边形
    printf("%.3f", Polygon_area(ans));
    return 0;
}
```

## 自适应辛普森积分

对于一个定积分
$$
\int_{a}^{b} f(x) \mathrm{d}x = F(b) - F(a)
$$
但是如果原函数求导困难，可以使用二次函数逼近
$$
\int_{a}^{b} f(x) \mathrm{d}x \approx \dfrac{(b - a)}{6} (f(a) + 4 \times f(\dfrac{2}{a + b}) + f(b))
$$
主要用于求不规则的图形面积，以及简单函数求导（面积）
```cpp
double simpson(double l,double r){
	double mid = ( l + r ) / 2;
	return (r-l) * (f(l) + 4 * f(mid) + f(r)) / 6;
} // f 为被积函数
double asr(double l, double r, double s){
	double mid = ( l + r ) / 2;
	double L = simpson(l, mid), R = simpson(mid, r);
	if(fabs(s - L - R ) < eps) return L + R; // 根据设置的 eps 自适应拟合精度
	return asr(l, mid, L) + asr(mid, r, R);
}
printf("%.6lf\n", asr(l, r, simpson(l, r)));
```
难度主要在分析函数 $f(x)$ 上面

**二重自适应辛普森积分**
$$
\begin{aligned}
\int_{a}^{b}\int_{c}^{d} f(x, y) \mathrm{d}x\mathrm{d}y &= \int_{a}^{b}F_x(y) \mathrm{d}y \approx \dfrac{b - a}{6} (F_x(a) + 4F_x(\dfrac{a + b}{2}) + F_x(b))) \\
F_x(y) &= \int_{c}^{d} f(x, y) \mathrm{d}x \approx \dfrac{d - c}{6}(f(c, y) + 4f(\dfrac{d + c}{2}, y) + f(d, y))
\end{aligned}
$$

```cpp
#include <iostream>
#include <stdlib.h>
using namespace std;
double f(double x, double y) {return x * x + y;}
double simpsonX2(double a, double b, double y) { // a,d为积分下、上限，y为被固定的y值
    double c = (b + a) / 2.0;
    return (f(a, y) + 4 * f(c, y) + f(b, y)) * (b - a) / 6.0; //对x的辛普森近似
}
double adspX2(double a, double b, double y, double eps, double S) { //对x的自适应辛普森递归
    double c = (b + a) / 2.0;
    double L = simpsonX2(a, c, y), R = simpsonX2(c, b, y);
    if (abs(L + R - S) <= 15.0 * eps)  return L + R + (L + R - S) / 15.0;
    return adspX2(a, c, y, eps / 2.0, L) + adspX2(c, b, y, eps / 2.0, R);
}
double inte2(double a, double b, double y, double eps) { //固定y后，对x的积分
    return adspX2(a, b, y, eps, simpsonX2(a, b, y));
}
double simpsonY2(double xa, double xb, double ya, double yb, double eps) {
    double yc = (ya + yb) / 2.0;
    return (inte2(xa, xb, ya, eps) + 4 * inte2(xa, xb, yc, eps) + inte2(xa, xb, yb, eps)) * (yb - ya) / 6.0; //对y的辛普森近似
}
double adspY2(double xa, double xb, double ya, double yb, double eps, double S) { //对y的自适应辛普森递归
    double L = simpsonY2(xa, xb, ya, (ya + yb) / 2, eps);
    double R = simpsonY2(xa, xb, (ya + yb) / 2, yb, eps);
    if (abs(L + R - S) <= 15.0 * eps) return L + R + (L + R - S) / 15.0;
    return adspY2(xa, xb, ya, (ya + yb) / 2.0, eps / 2.0, L) + adspY2(xa, xb, (ya + yb) / 2.0, yb, eps / 2.0, R);
}
double intergation2(double xa, double xb, double ya, double yb, double eps) { //求二重积分
    return adspY2(xa, xb, ya, yb, eps, simpsonY2(xa, xb, ya, yb, eps));
}
int main() {
    cout << intergation2(0, 1, 0, 1, 0.00001) << endl;
    return 0;
}
```

**圆的面积并**
给很多圆求面积并集，扫描线进阶
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef pair<double, double> PDD;
const int N = 1010;
const double eps = 1e-8;
struct Circle{
    double x, y, r;
    Circle(double _x = 0.0, double _y = 0.0, double _r = 0.0) : x(_x), y(_y), r(_r) {}
} cir[N];
int n;
PDD lr[N * 2];
int sign(double x) { return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;}
int cmp(double x, double y) { return fabs(x - y) < eps ? 0 : x < y ? -1 : 1;}
double f(double x) {
    int idx = 0;
    for(int i = 0; i < n; i ++) {
        double dlt = fabs(cir[i].x - x);
        if(cir[i].r > dlt) {
            double h = sqrt(cir[i].r * cir[i].r - dlt * dlt);
            lr[idx ++] = {cir[i].y - h, cir[i].y + h};
        }
    }
    if(idx == 0) return 0; // 因为这个数组没清空过所以要判
    sort(lr, lr + idx);
    double tot = 0.0, st = lr[0].first, en = lr[0].second;
    for(int i = 1; i < idx; i ++) {
        if(lr[i].first < en)
            en = max(en, lr[i].second);
        else
            tot += en - st, st = lr[i].first, en = lr[i].second;
    }
    return tot + en - st;
}
double simposon(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
}
double asr(double l, double r, double s) {
    double mid = (l + r) / 2;
    double L = simposon(l, mid), R = simposon(mid, r);
    if(fabs(s - L - R) < eps) return L + R;
    return asr(l, mid, L) + asr(mid, r, R);
}
int main() {
    scanf("%d", &n);
    for(int i = 0 ; i <= n; i ++) {
        scanf("%lf%lf%lf", &cir[i].x, &cir[i].y, &cir[i].r);
    }
    double l = -2000, r = 2000;
    printf("%.3lf\n", asr(l, r, simposon(l, r)));
    return 0;
}
```

## 闵可夫斯基合
给两个凸包 $A$, $B$, $q$ 次询问， 每次给一个移动量 $w$ 来移动 $B$ 凸包，问 $A$ 与 $B$ 是否有交点
令 $a\in A, b \in B$, 则移动向量 $w$ 使得存在 $b + w = a$, 那么 $w$ 需要满足 $w = a - b$
构造闵可夫斯基合 $C = {a + (-b)}$，只要判断移动向量是否在凸包 $C$ 内。

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define ll long long
using namespace std;
const ll N = 1e5 + 10;
struct Point {
    ll x, y;
    Point operator-(Point A) { return (Point){x - A.x, y - A.y}; }
    Point operator+(Point A) { return (Point){x + A.x, y + A.y}; }
    ll operator*(Point A) const { return x * A.y - y * A.x; } // 叉积
    ll len() const { return x * x + y * y; }
} A[N], C1[N], C2[N], s1[N], s2[N], bs;
ll cmp1(const Point &A, const Point &B) { return A.y < B.y || (A.y == B.y && A.x < B.x);}
ll cmp2(const Point &A, const Point &B) { return A * B > 0 || (A * B == 0 && A.len() < B.len()); }
ll n, m, sta[N], top, q, tot;
void Convex(Point *A, ll &n) { // 求凸包
    sort(A + 1, A + n + 1, cmp1);
    bs = A[1];
    sta[top = 1] = 1;
    for (ll i = 1; i <= n; i++)
        A[i] = A[i] - bs;
    sort(A + 2, A + n + 1, cmp2);
    for (ll i = 2; i <= n; sta[++top] = i, i++)
        while (top >= 2 && (A[i] - A[sta[top - 1]]) * (A[sta[top]] - A[sta[top - 1]]) >= 0)
            top--;
    for (ll i = 1; i <= top; i++)
        A[i] = A[sta[i]] + bs;
    n = top;
    A[n + 1] = A[1];
}
void Minkowski() { // 闵可夫斯基合
    for (ll i = 1; i < n; i++) s1[i] = C1[i + 1] - C1[i];
    s1[n] = C1[1] - C1[n];
    for (ll i = 1; i < m; i++) s2[i] = C2[i + 1] - C2[i];
    s2[m] = C2[1] - C2[m];
    A[tot = 1] = C1[1] + C2[1];
    ll p1 = 1, p2 = 1;
    while (p1 <= n && p2 <= m) ++tot, A[tot] = A[tot - 1] + (s1[p1] * s2[p2] >= 0 ? s1[p1++] : s2[p2++]);
    while (p1 <= n) ++tot, A[tot] = A[tot - 1] + s1[p1++];
    while (p2 <= m) ++tot, A[tot] = A[tot - 1] + s2[p2++];
}
ll in(Point a) { // 判断点是否在凸包内
    if (a * A[1] > 0 || A[tot] * a > 0) return 0;
    ll ps = lower_bound(A + 1, A + tot + 1, a, cmp2) - A - 1;
    return (a - A[ps]) * (A[ps % tot + 1] - A[ps]) <= 0;
}
int main() {
    cin >> n >> m >> q;
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld", &C1[i].x, &C1[i].y);
    Convex(C1, n); // A 凸包
    for (ll i = 1; i <= m; i++) {
        scanf("%lld%lld", &C2[i].x, &C2[i].y);
        C2[i].x = -C2[i].x; // 反向存
        C2[i].y = -C2[i].y;
    }
    Convex(C2, m); // B 凸包
    Minkowski(); // 闵可夫斯基合
    Convex(A, tot); // 求闵可夫斯基合凸包
    bs = A[1];
    for (ll i = tot; i >= 1; i--) A[i] = A[i] - A[1];
    while (q--) {
        scanf("%lld%lld", &A[0].x, &A[0].y); 
        printf("%lld\n", in(A[0] - bs));// 判断输入量是否在闵可夫斯基合内
    }
    return 0;
}
```
