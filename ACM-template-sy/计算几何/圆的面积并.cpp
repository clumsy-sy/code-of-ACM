#include <bits/stdc++.h>
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