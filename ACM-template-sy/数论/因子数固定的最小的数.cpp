ull p[16] = {
    2,  3,  5,  7,  11, 13, 17, 19,
    23, 29, 31, 37, 41, 43, 47, 53}; //根据数据范围可以确定使用的素数最大为53
ull ans, n;
// depth: 当前在枚举第几个素数
// temp: 当前因子数量为 num的时候的数值
// num: 当前因子数
// up：上一个素数的幂，这次应该小于等于这个幂次
void dfs(ull depth, ull temp, ull num, ull up) {
    if (num > n || depth >= 16) return;     //边界条件
    if (num == n && ans > temp) { //取最小的ans
        ans = temp;
        return;
    }
    for (int i = 1; i <= up; i++) {
        if (temp * p[depth] > ans)
            break; //剪枝：如果加一个这个乘数的结果比ans要大，则必不是最佳方案
        //取一个该乘数，进行对下一个乘数的搜索
        dfs(depth + 1, temp = temp * p[depth], num * (i + 1), i); 
    }
}
int main() {
    scanf("%llu", &n); // 输入的 n 为因数个数
    ans = ~(ull)0;
    dfs(0, 1, 1, 64);
    printf("%llu\n", ans);
    return 0;
}