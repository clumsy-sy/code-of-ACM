vector<int> decantor(int x, int n) {
    x --;
    vector<int> num(n + 1, 0), res(n + 1);
    for (int i = 1; i <= n; i++) {
        int t = x / fac[n - i], j;
        for(j = 1; i <= n; j ++)
            if(!num[j]) {
                if(!t) break;
                t --;
            }
        res[i] = j;
        num[j] = 1;
        x %= fac[n - i];
    }
    return res; // res 的 [1 ~ n] 为答案
}