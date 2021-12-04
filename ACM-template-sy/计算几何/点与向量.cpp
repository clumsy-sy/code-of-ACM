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