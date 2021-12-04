//卢卡斯定理,计算C(n,m) % p, 当n，m很大(1e18)且p比较小(1e5)的情况
//C(n, m) % p  =  C(n / p, m / p) * C(n%p, m%p) % p
ll qp(ll a, ll b, ll mod) {
    ll res = 1, tmp = a % mod;
    while (b) {
        if (b & 1) res = (res * tmp) % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }
    return res;
}
ll C(ll a, ll b, ll p) { // 求组合数基础方法 O(n)
    if (b > a) return 0;
    ll res = 1;
    for (ll i = 1, j = a; i <= b; i++, j--) {
        res = (ll)res * j % p;
        res = (ll)res * qp(i, p - 2, p) % p;
    }
    return res;
}
ll lucas(ll a, ll b, ll p) {
    if (a < p && b < p) return C(a, b, p);
    return (ll)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}
//例题 hdu5446
/*
给你三个数n, m, k
第二行是k个数，p1,p2,p3...pk
所有p的值不相同且p都是质数
求C(n, m) % (p1*p2*p3*...*pk)的值
范围：1≤m≤n≤1e18，1≤k≤10，pi≤1e5，保证p1*p2*p3*...*pk≤1e18
我们知道题目要求C(n, m) % (p1*p2*p3*...*pk)的值
其实这个就是中国剩余定理最后算出结果后的最后一步求余
那C(n, m)相当于以前我们需要用中国剩余定理求的值
然而C(n, m)太大，我们只好先算出
C(n, m) % p1 = r1
C(n, m) % p2 = r2
C(n, m) % p3 = r3
.
C(n, m) % pk = rk
用Lucas，这些r1,r2,r3...rk可以算出来
然后又是用中国剩余定理求答案
 */
const int maxn = 110;
const int maxp = 1e5 + 10;
const int INF = 0x3f3f3f3f;
ll N,M,K;
ll F[maxp],Finv[maxp],inv[maxp];
void init(ll MOD){
    inv[1] = 1;
    for(int i = 2; i < maxp; i ++){
        inv[i] = (MOD - MOD / i) * 1ll * inv[MOD % i] % MOD; 
    }
    F[0] = Finv[0] = 1;
    for(int i = 1; i < maxp; i ++){
        F[i] = F[i - 1] * 1ll * i % MOD;
        Finv[i] = Finv[i - 1] * 1ll * inv[i] % MOD;
    }
}
ll quick_power(ll a,ll b,ll p){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d){
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}
ll Inv(ll t, ll p){//如果不存在，返回-1 
    ll d, x, y;
    ex_gcd(t, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}
ll fact(int n, ll p){//n的阶乘求余p 
    ll ret = 1;
     for (int i = 1; i <= n ; i ++) ret = ret * i % p ;
    return ret ;
}
ll comb(int n,int m,ll p){
    if(m < 0 || m > n) return 0;
    return fact(n,p) * Inv(fact(m,p),p) % p * Inv(fact(n - m,p),p) % p;
}
ll Lucas(ll n,ll m,ll p){
    return m?Lucas(n / p,m / p,p) * comb(n % p,m % p,p) % p : 1;
}

ll mul(ll a,ll b,ll p){
    ll ans = 0;
    while(b){
        if(b & 1) ans = (ans + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ans;
}
ll china(int n,ll *a,ll *m){
    ll M = 1,ret = 0;
    for(int i = 1; i <= n; i ++) M *= m[i];
    for(int i = 1; i <= n; i ++){
        ll w = M / m[i];
        ret = (ret + mul(w * Inv(w,m[i]),a[i],M)) % M;
    }
    return (ret + M) % M;
}
ll a[maxn],b[maxn];
int main(){
    int T; Sca(T);
    while(T--){
        scanf("%lld%lld%lld",&N,&M,&K);
        for(int i = 1; i <= K ; i ++){
            Scl(a[i]); 
            b[i] = Lucas(N,M,a[i]);
        }    
        Prl(china(K,b,a));
    }
    return 0;
}