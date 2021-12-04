//给三点坐标求第四点坐标
//求矩形的第四个点的函数 //已知A(a.x,a.y),B(b.x,b.y),C(c.x,c.y)，求D(dx,dy) 
double sqr(int x) {return x * x;}
Point get_4th(Point a, Point b, Point c) {
//ab表示AB^2,ac表示AC^2,BC表示BC^2 
    int ab = sqr( a.x - b.x ) + sqr( a.y - b.y ),
        ac = sqr( a.x - c.x ) + sqr( a.y - c.y ),
        bc = sqr( b.x - c.x ) + sqr( b.y - c.y );
    int dx, dy;
//用勾股定理的逆定理，判断谁是直角边,再根据矩形对边平行的性质，算出第四个点的坐标 
    if (ab + ac == bc) dx = b.x + c.x - a.x, dy = b.y + c.y - a.y;
    if (ab + bc == ac) dx = a.x + c.x - b.x, dy = a.y + c.y - b.y;
    if (ac + bc == ab) dx = a.x + b.x - c.x, dy = a.y + b.y - c.y;
    return Point(dx, dy);
}
//两圆相交面积
double AreaOfOverlap(Point c1, double r1, Point c2, double r2){
    double d = (c1 - c2).len();
    if(r1 + r2 < d + eps) return 0.0;
    if(d < fabs(r1 - r2) + eps){
        double r = min(r1, r2);
        return PI * r * r;
    }
    double x = (d * d + r1 * r1 - r2 * r2) / (2.0 * d);
    double p = (r1 + r2 + d) / 2.0;
    double t1 = acos(x / r1);
    double t2 = acos((d - x) / r2);
    double s1 = r1 * r1 * t1;
    double s2 = r2 * r2 * t2;
    double s3 = 2 * sqrt(p * (p - r1) * (p - r2) * (p - d));
    return s1 + s2 - s3;
}
//三点确定外接圆圆心坐标
Point Excenter(Point a, Point b, Point c){
    double a1 = b.x - a.x, b1 = b.y - a.y;
    double c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y;
    double c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
}