double PolyArea(Point p[], int n) {
    double res = 0.0;
    for(int i = 0 ; i < n; i ++)
        res += p[i] ^ p[(i + 1) % n];
    return res / 2;
}
double PolyArea(Point p[], int n) {
    double res = 0.0;
    for(int i = 0 ; i < n - 1; i ++)
        res += (p[i] - p[0]) ^ (p[(i + 1) % n] - p[i]);
    return res / 2;
}