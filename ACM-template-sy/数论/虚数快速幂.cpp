ll n, mod = 998244353;
struct ty{
    ll x, y; //复数形如x+yi
    ty operator* (const ty &b){
        ty ans;
        ans.x = ((x * b.x % mod - y *b.y % mod) % mod + mod % mod);
        ans.y = (x *b.y % mod + y * b.x % mod) % mod;
        return ans;
    }
} a, b;
ll ksm1(ll  a,ll  b){
    ll ans = 1, t = a;
    while(b){
        if (b & 1) ans =ans * t% mod;
        t = t * t % mod;
        b>>=1;
    }
    return ans;
}

ll ksm2(ty a,ll b) {//此处不反回ty类型因为(1 + i) ^ n + (1 - i) ^ n 虚数都是奇次被抵消了;
    ty ans, t = a; ans.x = 1;  ans.y =0;
    while(b){
        if (b & 1) ans = ans * t;
        t = t * t;
        b>>=1;
    }
    return ans.x % mod;
}

int main(){
    a.x = 1, a.y = 1;
    b.x = 1, b.y = mod-1;
    cin >> n;
    ll ans = ((ksm1(2,n)+ ksm2(a, n)) % mod + ksm2(b, n) %mod) * ksm1(4, mod-2)/*乘法逆元*/ %mod;
    cout <<(ans+mod )%mod;
    return 0;
}