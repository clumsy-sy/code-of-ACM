ll qmul(ll a, ll b, ll p) {
    ll ans = 0;
    while(b){
        if(b&1) ans = (ans + a) % p;
        a = a * 2 % p;
        b >>= 1;
    }
    return ans;
}