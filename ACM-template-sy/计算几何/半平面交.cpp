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