ll f[2010][2010];
void Cinit() {
    for (int i = 0; i <= 2000; i++) {
        for (int j = 0; j <= i; j++) {
            if (!j) f[i][j] = 1;
            else f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % mod;
        }
    }
}