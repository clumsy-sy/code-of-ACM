#include <bits/stdc++.h>
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