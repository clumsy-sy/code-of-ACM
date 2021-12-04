#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const int M = 1e5 + 7;
struct Point {
    ld x, y;
    int id;
    Point(const ld &x = 0, const ld &y = 0) :x(x), y(y){}
    Point operator-(const Point& b){return Point(x - b.x, y - b.y);}
    ld get_length() {return sqrt(x * x + y * y);}
}p[M];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = Point(x, y);
    }

    sort(p + 1, p + n + 1, [&](auto p1, auto p2) {
        return atan2(p1.y, p1.x) < atan2(p2.y, p2.x);
    });
    for (int i = 1; i <= n; ++i)cout << '(' << p[i].x << ',' << p[i].y << ',' << atan2(p[i].y, p[i].x) <<')' << endl;
    return 0;
}
ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
int qua(Point p) { return (p.y < 0) << 1 | (p.x < 0) ^ (p.y < 0);}    // 求象限(0, 1, 2, 3)
bool cmp(Point a, Point b) { // cmp 写法
    return qua(a) < qua(b) || qua(a) == qua(b) && (cross(a, b) > 0.0);
}
bool cmp2(const Point &a, const Point &b)//先按象限排序，再按极角排序，再按远近排序 
{
    if (a.y == 0 && b.y == 0 && a.x*b.x <= 0)return a.x>b.x;
    if (a.y == 0 && a.x >= 0 && b.y != 0)return true;
    if (b.y == 0 && b.x >= 0 && a.y != 0)return false;
    if (b.y*a.y <= 0)return a.y>b.y;
    return cross(a,b) > 0 || (cross(a,b) == 0 && a.y > b.y);
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = Point(x, y);
    }
    Point c = Point(0, 0); // 原点（可更改）
    sort(p + 1, p + n + 1, [&](auto v1, auto v2) {
        return qua(v1 - c) < qua(v2 - c) || qua(v1 - c) == qua(v2 - c) && (cross(v1 - c, v2 - c) > 0.0);
    });
    for (int i = 1; i <= n; ++i)cout << '(' << p[i].x << ',' << p[i].y <<')' << endl;
    return 0;
}