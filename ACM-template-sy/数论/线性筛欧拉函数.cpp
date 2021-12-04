void get_euler(int n) {
    euler[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            prime[idx++] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; prime[j] * i <= n; j ++) {
            int t = prime[j] * i;
            st[t] = 1;
            if (i % prime[j] == 0) {
                euler[t] = euler[i] * prime[j];
                break;
            }
            euler[t] = euler[i] * euler[prime[j]];
        }
    }
}