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