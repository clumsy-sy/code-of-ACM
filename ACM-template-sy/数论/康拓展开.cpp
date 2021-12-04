//如果要求当前全排列是第几个排列，则需要把数字 + 1
ll cantor(int a[], int n) {
    ll res = 0; // 树状数组优化
    for(int i = n; i >= 1; i --) {
        int smaller = sum(a[i]); // 在当前位之后小于其的个数
        add(a[i], 1);            // 改为 大于 则逆序
        res = (res + fac[n - i] * smaller % mod) % mod;
    }  // fac[] 为预处理的阶乘数组
    return (res + 1) % mod;
}
