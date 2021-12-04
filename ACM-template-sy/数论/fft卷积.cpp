const double PI = acos(-1.0);
const int MN = 4e6 + 10;
struct Comp {
    double x, y;
    Comp(double xx = 0, double yy = 0) {
        x = xx, y = yy;
    }
    Comp operator+(Comp c) {
        return Comp(x + c.x, y + c.y);
    }
    Comp operator-(Comp c) {
        return Comp(x - c.x, y - c.y);
    }
    Comp operator*(Comp c) {
        double tx = x * c.x - y * c.y;
        double ty = x * c.y + y * c.x;
        return Comp(tx, ty);
    }
};
Comp ff[MN];
int rev[MN];
void FFT(Comp *f, int n, int type) {
    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) {
            swap(f[i], f[rev[i]]);
        }
    }
    for (int h = 2; h <= n; h <<= 1) {
        Comp step(cos(2 * PI / h), sin(2 * PI * type / h));
        for (int j = 0; j < n; j += h) {
            Comp cur(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Comp f1 = f[k], f2 = f[k + h / 2];
                f[k] = f1 + cur * f2;
                f[k + h / 2] = f1 - cur * f2;
                cur = cur * step;
            }
        }
    }
    if (type == 1)
        return;
    for (int i = 0; i < n; i++)
        f[i].x /= n, f[i].y /= n;
}
int main() {
    int n = rr(), m = rr();
    for (int i = 0; i <= n; i++)
        ff[i].x = rr();
    for (int i = 0; i <= m; i++)
        ff[i].y = rr();
    int lim = 1, lim_2;
    while (lim <= n + m)
        lim <<= 1;
    lim_2 = lim >> 1;
    for (int i = 0; i < lim; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * lim_2);
    }
    FFT(ff, lim, 1);
    for (int i = 0; i <= lim; i++)
        ff[i] = ff[i] * ff[i];
    FFT(ff, lim, -1);
    for (int i = 0; i <= m + n; i++)
        printf("%d ", int(ff[i].y / 2 + 0.5));
    return 0;
}