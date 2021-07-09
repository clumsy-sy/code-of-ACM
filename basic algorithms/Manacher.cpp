#include <bits/stdc++.h>

using namespace std;
const int N = 2e7 + 10;
int chaArr[N], pArr[N];
char s[N];

int maxLcsplength(char str[]) {
    int len = (int)(strlen(str) * 2 + 1); //记录下manacher字符串的长度
    if (len == 0)
        return 0; //空字符串直接返回0
    for (int i = 0, idx = 0; i < len; i++)
        chaArr[i] = (i & 1) == 0 ? '#' : str[idx++]; //将字符串数组manacher化
    // R是最右回文边界，C是R对应的最左回文中心，maxn是记录的最大回文半径
    int R = -1, C = -1, ans = 0;
    for (int i = 0; i < len; i++) {
        //第一步直接取得可能的最短的回文半径，当i>R时，最短的回文半径是1，反之，最短的回文半径可能是i对应的i'的回文半径或者i到R的距离
        pArr[i] = R > i ? min(R - i, pArr[2 * C - i]) : 1;
        //取最小值后开始从边界暴力匹配，匹配失败就直接退出
        while (i + pArr[i] < len && i - pArr[i] > -1) {
            if (chaArr[i + pArr[i]] == chaArr[i - pArr[i]])
                pArr[i]++;
            else
                break;
        }//观察此时R和C是否能够更新
        if (i + pArr[i] > R) {
            R = i + pArr[i];
            C = i;
        } //更新最大回文半径的值
        ans = max(ans, pArr[i]);
    }
    return ans - 1;
}

int main() {
    scanf("%s", s);
    printf("%d\n", maxLcsplength(s));
    return 0;
}
