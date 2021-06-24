#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>
#include <queue>
#include <stack>
#include <list>
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
