typedef pair<double, double> PDD;
const int M = 110;
PDD p[M];
int n;
double ans = 1e8; 
double rands(double l, double r){ //随机一个在（l， r）之间的小数
    return (double) rand() / RAND_MAX * (r - l) + l; // rand() / RAND_MAX（生成0，1之间的小数）；
}
double get_dist(PDD a, PDD b) { //求两点距离
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
double calc(PDD k) {//求某点到各各点之间的距离
    double res = 0;
    for(int i = 0; i < n; i ++)
        res += get_dist(k, p[i]);
    ans = min(ans, res);
    return res;
}
void simulate_anneal() {
    PDD point = {rands(0, 10000), rands(0, 10000)};
    double last = calc(point);
    for(double i = 1e4; i > 1e-4; i *= 0.99) {//范围 + 精度 + 退火系数（<=1, 越接近1越精确，但复杂度也越大）
    
        PDD np(rands(point.x - i, point.x + i), rands(point.y - i, point.y + i)); //随机一个范围内的点
        double now = calc(np);
        double dt = now - last;
        if (exp(-dt / i) > rands(0, 1)) {//物理公式，如果这个点比原来的点“差”，一定跳过这个点（范围缩小）
                                         //如果这个点比原来的点“好”，则有一定概率跳过这个点（范围缩小）
            point = np;
            last = now;
        }
    }//通过退火过程，不断缩小范围，最后找到最值（但也有可能找不到，或者找错了）
}

int main() {
    srand(time(0));               //随机函数种子（运气）
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = {x, y};
    }
    for(int i = 0; i <= 10; i ++)  //退火过程多做几遍，使得答案正确可能性大一点
        simulate_anneal();
    printf("%.0lf", ans);          //四舍五入
    return 0;
}