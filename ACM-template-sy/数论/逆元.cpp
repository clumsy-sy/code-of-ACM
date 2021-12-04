//逆元 (a / b) % mod = a * inv(b) % mod
//拓展欧几里得定理求inv(b)
int mod = 1e9 + 7; 
int N;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(a == 0 && b == 0) return -1;
    if(b == 0){
        x = 1;y = 0;
        return a;
    }
    ll d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}
ll inv(ll a,ll n){
    ll x, y;
    ll d = exgcd(a,n,x,y);
    if(d == 1) return (x % n+ n) % n;
    else return -1;
}
//当mod为质数时，可以利用费马小定理，b的逆元为n ^ (mod - 2) % mod
//当我们需要求连续一段数在mod p下的逆元的时候，我们可以使用逆元的递推公式
//模板：求1到N的所有逆元
ll mod = 1e9 + 7; 
ll N, inv[maxn];
int main(){
    scanf("%lld%lld",&N,&mod);
    inv[1] = 1;
    for(int i = 2; i <= N; i ++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    return 0;
}

s[0] = 1;
for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
sv[n] = qpow(s[n], p - 2);
// 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
for (int i = n; i >= 1; --i) sv[i - 1] = sv[i] * a[i] % p;
for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % p;
