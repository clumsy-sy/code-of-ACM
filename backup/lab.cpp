#pragma region
#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
#define dbg(x) printf("%lld ", (x));
#define LN putchar('\n')
#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)
inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
#pragma endregion

int main() {
    ll n = rr(), m = rr();
    _forz (k, n, 1) { // 倒数第 k 个
        ll pos = -1;
        _fora (i, k, n)
            pos = (pos + m) % i
        if (k != 1)
            printf("No%lld: %lld\n", n + 1 - k, pos + 1);
        else
            printf("Last No is: %lld\n", pos + 1);
    }
    return 0;
}