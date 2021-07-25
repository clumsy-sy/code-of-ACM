#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
// 2, 7, 61||2,325,9375,28178,450775,9780504,1795265022
//但这几个数本身需要特判
ll qp(ll n, ll x, l mod) {
    ll res = 1;
    while (x) {
        if (x & 1)
            res = res * n % mod;
        n = n * n % mod;
        x >>= 1;
    }
    return res;
}

bool millerRabbin(ll n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    ll a = n - 1, b = 0;
    while (a % 2 == 0)
        a /= 2, b ++;
    ll test_time = 10; //可以使用特定底数
    for (int i = 1, j; i <= test_time; i ++) {//fermat判断
        ll x = rand() % (n - 2) + 2, v = qp(x, a, n);
        if (v == 1)  continue;
        for (j = 0; j < b; ++j) {//二次探测定理
            if (v == n - 1) break;
            v = v * v % n;
        }
        if (j >= b) return false;
    }
    return true;
}
