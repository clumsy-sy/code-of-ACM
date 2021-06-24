#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long ll;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')

ll rr() {
    ll s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    return s * w;
}

#pragma endregion

int main() {
    ll n = rr(), m = rr();
    _forz (k, n, 1) { // 倒数第 k 个
        ll pos = -1;
        _fora (i, k, n)
            pos = (pos + m) % i;
        if (k != 1)
            printf("No%lld: %lld\n", n + 1 - k, pos + 1);
        else
            printf("Last No is: %lld\n", pos + 1);
    }
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    printf("Hello \n");
    return 0;
}