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