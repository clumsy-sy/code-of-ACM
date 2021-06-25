#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>
#include <ctime>

int ry_solve();


int main() {
    auto t = clock();
#ifdef RYLOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ry_solve();

#ifdef RYLOCAL
    printf("\n[run] %lf ms\n", (clock() - t)*1000.0/CLOCKS_PER_SEC);
#endif
    return 0;
}

#define main ry_solve
// Head File End
