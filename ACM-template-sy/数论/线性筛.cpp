int get_prime(int x) {
    for (int i = 2; i <= x; i++) {
        if (!st[i]) prime[cnt++] = i;
        for (int j = 0; prime[j] * i <= x; j++) {
            st[prime[j] * i] = true;
            if (i % prime[j] == 0) break;
        }
    }
    return cnt;
}