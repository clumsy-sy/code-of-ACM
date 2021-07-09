#pragma region

#include <memory.h>
#include <stdio.h>

typedef long long ll;
#define _fora(i, a, n) for (ll i = a; i <= n; i++)
#define _forz(i, a, n) for (ll i = a; i >= n; i--)
#define LN putchar('\n')

ll rr() {
    ll s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        s = s * 10 + c - '0', c = getchar();
    return s * w;
}

#pragma endregion

// OIES A259180 Amicable pairs.
ll nn[] = {
    220,   284,   1184,  1210,  2620,  2924,  5020,  5564,  6232,  6368,
    10744, 10856, 12285, 14595, 17296, 18416, 63020, 76084, 66928, 66992,
};

ll lower_bound(ll l, ll r, ll val) {
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (nn[mid] > val)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main() {
    ll a = rr(), b = rr();
    ll sa = lower_bound(0, 19, a), sb = lower_bound(0, 19, b);
    sa = sa / 2, sb = sb / 2;
    if (nn[sa * 2] < a)
        sa++;
    if (nn[sb * 2 + 1] > b)
        sb--;
    for (ll i = sa; i <= sb; i++) {
        printf("%lld,%lld\n", nn[i * 2], nn[i * 2 + 1]);
    }
    return 0;
}