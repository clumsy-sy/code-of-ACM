//高斯消元,时间复杂度O(n ^ 3)
/*
高斯消元是求解线性方程组的一种做法。将线性方程组列为矩阵的形式
x1 + 2x2 - x3 = -6       
2x1 + x2 - 3x3 = -9
-x1 - x2 + 2x3 = 7
可以写成
1 2 -1 -6        
0 -3 -1 3
-1 -1 2 7
这么一个矩阵,然后利用初等行变换化为最简求每个变量的值 
 */
 //模板，给出像上述增广矩阵求每个变量的值
#include <bits/stdc++.h>
using namespace std;
const int M = 110;
const double eps = 1e-6; //防止浮点精度偏差
double a[M][M];
int n;
int gauss() {
    int r, c; // r是row（行），c是col（列）
    for (r = 0, c = 0; c < n; c++) {
        int idx = r;
        for (int i = r; i < n; i++) {
            if (fabs(a[idx][c]) < fabs(a[i][c]))
                idx = i; //寻找该列最大值（最大值可以使得答案精度较好）
        }
        if (fabs(a[idx][c]) < eps)
            continue; //如果最大值已经为0，则进入下一次循环（行不变，列++）
        for (int i = c; i <= n; i++)
            swap(a[idx][i], a[r][i]); //找出的开头最大列与原列交换
        for (int i = n; i >= c; i--)
            a[r][i] /= a[r][c]; //从行末向前更新，使得开头为1
        for (int i = r + 1; i < n; i++) {//更新该行下面的矩阵，使其靠近最简形矩阵
            if (fabs(a[i][c]) > eps) //如果该行的队头是0，则不执行；
                for (int j = n; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c]; //从后向前更新该行的值
        }
        r++; //完整的一次操作后， 行 ++
    }
    if (r < n){ //判断矩阵的秩，确定解的个数，如果r == n，矩阵有解
        for (int i = r; i < n; i++) {
            if (a[i][n] > eps)
                return 2; //判断是否存在 0 = ！0的情况
        }
        return 1; //否则无穷多解，相当于矩阵的秩 < n
    }
//从下往上，只对b i进行操作，因为最后b i的值便对应x直接输出
    for (int i = n - 1; i >= 0; i--) 
        for (int j = i + 1; j < n; j++)
            a[i][n] -= a[j][n] * a[i][j];
    return 0;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + 1; j++)
            cin >> a[i][j];
    int flag = gauss();
    if (flag == 1) {
        puts("Infinite group solutions");
    } else if (flag == 2) {
        puts("No solution");
    } else {
        for (int i = 0; i < n; i++)
            printf("%.2lf\n", a[i][n]);
    }
    return 0;
}

/*
高斯消元也可求解一类开关问题
所有开关的的开闭状态从一个指定状态变为src另一个指定状态dst的方法
改变一个开关j会改变另一个开关i的状态aij,可列出方程
a1,1 ^ x1 ^ a1,2 ^ x2 .... ^ a1n ^ xn = src1 ^ dst1
a2,1 ^ x1 ^ a2,2 ^ x2 .....^ a2n ^ xn = src2 ^ dst2 
a为已知系数，src和dst为已知系数，直接高斯消元求解可行种数
种数就是(1 << 自由元个数)
n小的话可以用状态压缩,大的话可以用bitset
 */
 //POJ1830
//有N个相同的开关，每个开关都与某些开关有着联系，每当你打开或者关闭某个开关的时候，其他的与此开关相关联的开关也会相应地发生变化，即这些相联系的开关的状态如果原来为开就变为关，如果为关就变为开。你的目标是经过若干次开关操作后使得最后N个开关达到一个特定的状态。对于任意一个开关，最多只能进行一次开关操作。你的任务是，计算有多少种可以达到指定状态的方法。（不计开关操作的顺序）
#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int n;
int a[N][N];
int gauss() {
    int r, c;
    for (r = 1, c = 1; c <= n; c++) {
        // 找主元
        int t = r;
        for (int i = r + 1; i <= n; i++)
            if (a[i][c])
                t = i;
        if (!a[t][c]) continue;
        // 交换
        for (int i = c; i <= n + 1; i++) swap(a[t][i], a[r][i]);
        // 消
        for (int i = r + 1; i <= n; i++)
            for (int j = n + 1; j >= c; j--)
                a[i][j] ^= a[i][c] & a[r][j];
        r++;
    }
    int res = 1;
    if (r < n + 1) {
        for (int i = r; i <= n; i++) {
            if (a[i][n + 1])
                return -1; // 出现了 0 == !0，无解
            res *= 2;
        }
    }
    return res;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(a, 0, sizeof a);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i][n + 1]);
        for (int i = 1; i <= n; i++) {
            int t;
            scanf("%d", &t);
            a[i][n + 1] ^= t;
            a[i][i] = 1;
        }
        int x, y;
        while (scanf("%d%d", &x, &y), x || y)
            a[y][x] = 1;
        int t = gauss();
        if (t == -1)
            puts("Oh,it's impossible~!!");
        else
            printf("%d\n", t);
    }
    return 0;
}