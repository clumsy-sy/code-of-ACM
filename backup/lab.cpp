#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long ll;

#define INF 0x3f3f3f3f
#define LN putchar('\n')

ll read() {
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
    
    return 0;
}