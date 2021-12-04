const int MAXN = 2e5 + 3;
ll fac[MAXN], inv[MAXN]; // 阶乘 阶乘的逆元
ll qp(ll a, ll b, ll mod) {
    ll res = 1, tmp = a % mod;
    while (b) {
        if (b & 1) res = (res * tmp) % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }
    return res;
}
void init(ll mod) {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fac[i] = fac[i - 1] * i % mod;
    inv[MAXN - 1] = qp(fac[MAXN - 1], mod - 2, mod);
    for (int i = MAXN - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
}
ll C(ll a, ll b) {
    if (b > a) return 0;
    if (b == 0) return 1;
    return fac[a] * inv[b] % mod * inv[a - b] % mod;
}