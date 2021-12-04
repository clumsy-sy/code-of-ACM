#include <bits/stdc++.h>
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