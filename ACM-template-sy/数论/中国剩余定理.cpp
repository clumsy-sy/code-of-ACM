ll CRT(int n, ll m[], ll Mi[]) {
    ll mul = 1, res = 0;
    for (int i = 1; i <= n; i ++) mul *= m[i];
    for (int i = 1; i <= n; i ++) {
        Mi[i] = mul / m[i];
        ll x = 0, y = 0;
        exgcd(Mi[i], m[i], x, y);
        res += r[i] * Mi[i] * (x < 0 ? x + m[i] : x);
    }
    return res % mul;
}

//判断是否有解

ll mod(ll a, ll b){ return ((a % b) + b) % b;}
int main(){
    int n;
    scanf("%d", &n);
    ll a1, m1, a2, m2, k1, k2;
    scanf("%lld%lld", &a1, &m1);
    for(int i = 1; i < n; i++){
        scanf("%lld%lld", &a2, &m2);
        ll d = exgcd(a1, -a2, k1, k2);
        if((m2 - m1) % d){ puts("-1"); return 0; } // 判断是否有解
        k1 = mod(k1 * (m2 - m1) / d, abs(a2 / d));
        m1 = k1 * a1 + m1;
        a1 = abs(a1 / d * a2);
    }
    printf("%lld\n", m1);
    return 0;
}