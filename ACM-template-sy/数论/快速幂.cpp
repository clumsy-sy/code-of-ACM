ll qp(ll a, ll b, ll p) {
    ll ans = 1;
    while(b) {
        if(b & 1)ans = (ans * a) %p;
        a = (a * a)%p;
        b >>= 1;
    }
    return ans;
}