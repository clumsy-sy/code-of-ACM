#include <bits/stdc++.h>
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