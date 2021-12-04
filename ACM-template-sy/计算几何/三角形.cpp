// 三角形的重心
Point barycenter(Point A, Point B, Point C){
    return {(A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3};
}
// 三角形的外心
// DEPENDS r90c, V*V, d*V, V-V, V+V
// NOTE 给定圆上三点求圆，要先判断是否三点共线
Point circumcenter(Point A, Point B, Point C) {
    double a = A * A, b = B * B, c = C * C;
    double d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    return ((B - C) * a + (C - A) * b + (A - B) * c).r90c() * (1 / d);
}
// 三角形的内心
// DEPENDS len, d*V, V-V, V+V
Point incenter(Point A, Point B, Point C) {
    double a = (B - C).len(), b = (A - C).len(), c = (A - B).len();
    double d = a + b + c;
    return (A * a + B * b + C * c) * (1 / d);
}
// 三角形的垂心
// DEPENDS V*V, d*V, V-V, V^V, r90c
Point orthocenter(Point A, Point B, Point C) {
    double n = B * (A - C), m = A * (B - C);
    double d = (B - C) ^ (A - C);
    return ((C - B) * n - (C - A) * m).r90c() * (1 / d);
}