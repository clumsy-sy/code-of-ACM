#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <complex.h>

int ry_solve();


int main() {
    int t = clock();
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
