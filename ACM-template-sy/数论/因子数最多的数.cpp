ull p[16] = {
    2,  3,  5,  7,  11, 13, 17, 19,
    23, 29, 31, 37, 41, 43, 47, 53}; //根据数据范围可以确定使用的素数最大为53
ull ans, n, ans_num;

void dfs(ull depth, ull temp, ull num, ull up) {
    if (depth >= 16 || temp > n)
        return;
    if (num > ans_num) { //更新答案
        ans = temp; ans_num = num;
    }
    if (num == ans_num && ans > temp)
        ans = temp; //更新答案
    for (int i = 1; i <= up; i++) {
        if (temp * p[depth] > n)
            break; //剪枝：如果加一个这个乘数的结果比ans要大，则必不是最佳方案
        dfs(depth + 1, temp *= p[depth], num * (i + 1),
            i); //取一个该乘数，进行对下一个乘数的搜索
    }
    return;
}
int main() {
    while (scanf("%llu", &n) != EOF) {
        ans_num = 0;
        dfs(0, 1, 1, 60);
        printf("%llu\n", ans);
    }
    return 0;
}