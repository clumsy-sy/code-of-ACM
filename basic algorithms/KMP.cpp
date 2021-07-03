#include <iostream>

using namespace std;
typedef long long ll;

const int N = 1e4 + 7;

int ne[N]; //转移值
char s[N], p[N];

int main() {
    int n, m;
    scanf("%d%s%d%s", &n, p + 1, &m, s + 1);// 下标从1开始

    for (int i = 2, j = 0; i <= n; i++) { //生成转移值数组
        while (j && p[i] != p[j + 1])
            j = ne[j];                    //如果重复中断
        if (p[i] == p[j + 1]) 
            j++;                          //如果字符串中前后重复
        ne[i] = j;                        //记录重复点位置，
    }

    for (int i = 1, j = 0; i <= m; i++) {
        while (j && s[i] != p[j + 1])
            j = ne[j];                    //如果匹配终端回到转移值得点重新开始匹配
        if (s[i] == p[j + 1])
            j++;                          //匹配过程
        if (j == n) {
            printf("%d\n", i - n + 1);    //输出下标(从 1 开始)
            j = ne[j];                    //转移点
        }
    }
    return 0;
}